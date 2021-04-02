﻿/*
Mark off what items are complete (e.g. x, done, checkmark, etc), and put a P if 
partially complete. If 'P' include how to test what is working for partial 
credit below the checklist line.

Total available points:  100

___X___	30	Tutorial completed (if not, what was the last section completed)
_______ 5   CSC 692 ONLY What happened: <i am not 692> 
___X___	5	234 Menu Option
___X___	5	357 Menu Option
___X___	10	All Harmonics Option
___X___	5	Odd Harmonics Option
___X___	10	Ramp In/Out
___X___	10	Tremolo
___X___	10	Half Speed
___X___	10	Backwards
___X___  5   Did you hear it? (Completion points)
			NASA Statement about Roswell: This was the closest i heard to the statement
			Joran van der Sloot: no i didnt
			Nancy Pelosi: I think i did
__100___    Total (please add the points and include the total here)


The grade you compute is the starting point for course staff, who reserve the 
right to change the grade if they disagree with your assessment and to deduct 
points for other issues they may encounter, such as errors in the submission 
process, naming issues, etc. 
 */


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using NAudio.Wave;
using NAudio.Wave.SampleProviders;

namespace AudioProcess
{
 

    public partial class MainForm : Form
    {

        private Sound sound = null;
        private String lastFile = null;
        private SoundView soundRendering = new SoundView();
        private SoundGenerate gen = new SoundGenerate();
        private SoundProcess process = new SoundProcess();

        public MainForm()
        {
            InitializeComponent();
           
            //define the area to display the sound waves
            Rectangle drawArea = ClientRectangle;
            drawArea.Y = menuStrip1.Height;
            soundRendering.DrawArea = drawArea;
            soundRendering.SamplesPerPeak = vScrollBar.Value;
            saveItem.Enabled = false;

            DoubleBuffered = true;
        }

        #region Callbacks
        protected override void OnPaint(PaintEventArgs e)
        {
            if (sound == null)
                return;

            soundRendering.OnPaint(e.Graphics);
        }

        protected override void OnResize(EventArgs e)
        {
            
            base.OnResize(e);

            Rectangle drawArea = ClientRectangle;
            drawArea.Y = menuStrip1.Height;
            soundRendering.DrawArea = drawArea;

            Invalidate();
        }
        #endregion

        #region Menu Handlers
        private void closeItem_Click(object sender, EventArgs e)
        {
            sound = null;
            Invalidate();

        }

        private void darkModeItem_Click(object sender, EventArgs e)
        {
            soundRendering.MakeDarkFormat();
            Invalidate();
        }

        private void exitItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            soundRendering.SetOffsetFromPercent((double)e.NewValue / (hScrollBar.Maximum - hScrollBar.Minimum));

            Invalidate();
        }

        private void lightModeItem_Click(object sender, EventArgs e)
        {
            soundRendering.MakeLightFormat();
            Invalidate();
        }

        private void newMenu_Click(object sender, EventArgs e)
        {
            NewSound dlg = new NewSound();
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                sound = new Sound();
                sound.Format = WaveFormat.CreateIeeeFloatWaveFormat(dlg.SampleRate, dlg.Channels);
                sound.Samples = new float[(int)(dlg.SampleRate * dlg.Channels * dlg.Seconds)];
                soundRendering.Sound = sound;
            }
           dlg.Dispose();

            Invalidate();
        }

        private void openDefaultItem_Click(object sender, EventArgs e)
        {
            sound = new Sound();
            sound.Open(Properties.Resources.nasa);

            soundRendering.Sound = sound;
            Invalidate();
        }

        private void openItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                sound = new Sound();
                sound.Open(openFileDialog.FileName);
                soundRendering.Sound = sound;
                Invalidate();
            }
            openFileDialog.Dispose();
        }

        private void pauseItem_Click(object sender, EventArgs e)
        {
            if (sound != null)
                sound.Pause();
        }

        private void playItem_Click(object sender, EventArgs e)
        {
            if (sound != null)
                sound.BasicPlay();
        }

        private void saveAsItem_Click(object sender, EventArgs e)
        {
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                sound.SaveAs(saveFileDialog.FileName, saveFileDialog.FilterIndex);
                if (lastFile != null)
                {
                    saveItem.Enabled = true;
                    lastFile = saveFileDialog.FileName;
                }
            }
            saveFileDialog.Dispose();
        }

        private void saveItem_Click(object sender, EventArgs e)
        {
            if (lastFile != null)
                sound.Save();
            else
                MessageBox.Show("No prior file saved", "Error");
        }

        private void sineItem_Click(object sender, EventArgs e)
        {
            gen.MakeSine(sound);
            Invalidate();
        }

        private void stopItem_Click(object sender, EventArgs e)
        {
            if (sound != null)
                sound.Stop();
        }

        private void vScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            soundRendering.SamplesPerPeak = e.NewValue;
            Invalidate();
        }

        private void sineParamsItem_Click(object sender, EventArgs e)
        {
            gen.MakeParamSine();
        }


        #endregion

        private void volumeAdjustItem_Click(object sender, EventArgs e)
        {
            Volume_Adjust dlg = new Volume_Adjust();
            if(dlg.ShowDialog() == DialogResult.OK)
            {
                process.OnProcessVolume(sound, dlg.Adjust);
                Invalidate();
            }
            
        }

        private void SineWaves_Click(object sender, EventArgs e)
        {
            gen.MakeSineAdditive(sound);
            Invalidate();
        }

        private void Sine234_Click(object sender, EventArgs e)
        {
            gen.Make234Sine(sound);
            Invalidate();
        }

        private void Sine357_Click(object sender, EventArgs e)
        {
            gen.Make357Sine(sound);
            Invalidate();
        }

        private void AllHarmonics_Click(object sender, EventArgs e)
        {
            gen.MakeAllHarmonics(sound);
            Invalidate();
        }

        private void AllOddHarmonics_Click(object sender, EventArgs e)
        {
            gen.MakeOddHarmonics(sound);
            Invalidate();
        }

        private void OnRamp_Click(object sender, EventArgs e)
        {
            process.Ramp(sound);
            Invalidate();
        }

        private void RampInOut_Click(object sender, EventArgs e)
        {
            process.RampInOut(sound);
            Invalidate();
        }

        private void Tremolo_Click(object sender, EventArgs e)
        {
            process.Tremolo(sound);
            Invalidate();
        }

        private void Slow_Click(object sender, EventArgs e)
        {
            process.Slow(sound);
            Invalidate();
        }

        private void Fast_Click(object sender, EventArgs e)
        {
            process.Fast(sound);
            Invalidate();
        }

        private void Backwards_Click(object sender, EventArgs e)
        {
            process.Backwards(sound);
            Invalidate();
        }
    }
}
