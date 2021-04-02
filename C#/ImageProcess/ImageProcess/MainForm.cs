
/*
 * Mark off what items are complete (e.g. x, done, checkmark, etc), and put 
 * a P if partially complete. If 'P' include how to test what is working for 
 * partial credit below the checklist line.

Total available points:  100

_DONE_	25	Tutorial completed (if not, what was the last section completed)
_DONE_	10	My Favorite Color
_DONE_	5	Horizontal Gradient Image
_DONE_	5	Vertical Gradient Image
_DONE_	10	Diagonal Gradient Image
_DONE_	5	Horizontal Line
_DONE_	5	Vertical Wider Line
_DONE_	10	Diagonal Line
_DONE_	10	Monochrome Image Filter
_DONE_	15	Median Filter
_100__	Total (please add the points and include the total here)

The grade you compute is the starting point for course staff, who reserve the 
right to change the grade if they disagree with your assessment and to deduct 
points for other issues they may encounter, such as errors in the submission 
process, naming issues, etc. * 
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

namespace ImageProcess
{
    public partial class MainForm : Form
    {
        enum ModelType { None, Generate, Process}; //mode for menu enabling

        Image model;
        ImageEditor editor;


        public MainForm()
        {
            InitializeComponent();
            DoubleBuffered = true; //stop flicker

            SetMenuOptionEnable(ModelType.None);
        }

        //main Paint function
        protected override void OnPaint(PaintEventArgs e)
        {
            if (model == null)
                return;

            model.OnPaint(e);
        }

        //redraw on resize
        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            Invalidate();
        }


        //
        //forward mouse calls
        //

        protected override void OnMouseDown(MouseEventArgs e)
        {
            if (model == null)
                return;

            base.OnMouseDown(e);
            editor.MousePress(model, e.X, e.Y);
            Invalidate();
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            if (model == null)
                return;

            base.OnMouseUp(e);
            editor.MouseRelease();
            Invalidate();
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            if (model == null)
                return;

            base.OnMouseMove(e);
            editor.MouseMove(model, e.X, e.Y);
            Invalidate();
        }


        //
        //forward menu calls-------------------------------------------------------------------------
        //
        private void newMenu_Click(object sender, EventArgs e)
        {
            editor = new ImageGenerate();
            model = new Image(menuStrip1.Height);
            ImageGenerate.FillBlack(model);
            SetMenuOptionEnable(ModelType.Generate);
            Invalidate();
        }

        private void drawMenu_Click(object sender, EventArgs e)
        {
            editor.SetMode(ImageEditor.MODE.Draw);

            drawMenu.Checked = editor.MouseMode == ImageEditor.MODE.Draw;
         
            Invalidate();
        }

        private void copyMenu_Click(object sender, EventArgs e)
        {
            model.Reset();

            Invalidate();
        }

        private void negativeMenu_Click(object sender, EventArgs e)
        {
            editor.SetMode(ImageEditor.MODE.None);
            ImageProcess.OnFilterNegative(model);
            drawMenu.Checked = editor.MouseMode == ImageEditor.MODE.Draw;

            Invalidate();
        }

        private void thresholdMenu_Click(object sender, EventArgs e)
        {
            editor.SetMode(ImageEditor.MODE.Threshold);
            drawMenu.Checked = editor.MouseMode == ImageEditor.MODE.Draw;
        }

        private void warpMenu_Click(object sender, EventArgs e)
        {
            editor.SetMode(ImageEditor.MODE.Warp);
            drawMenu.Checked = editor.MouseMode == ImageEditor.MODE.Draw;
        }

        private void warpBilinearMenu_Click(object sender, EventArgs e)
        {
            editor.SetMode(ImageEditor.MODE.WarpNearest);
            drawMenu.Checked = editor.MouseMode == ImageEditor.MODE.Draw;
        }

        private void fillWhiteMenu_Click(object sender, EventArgs e)
        {
            ImageGenerate.FillWhite(model);
        }

        private void openTestMenu_Click(object sender, EventArgs e)
        {
            model = new Image(menuStrip1.Height);
            model.OnOpenDocument(null);
            editor = new ImageProcess();
            SetMenuOptionEnable(ModelType.Process);
            Invalidate();
        }

        private void openMenu_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                model = new Image(menuStrip1.Height);
                model.OnOpenDocument(openFileDialog1.FileName);
                editor = new ImageProcess();
                SetMenuOptionEnable(ModelType.Process);
                Invalidate();
            }
        }

        private void closeMenu_Click(object sender, EventArgs e)
        {
            model.Close();
            model = null;
            SetMenuOptionEnable(ModelType.None);
            Invalidate();
        }

        private void exitMenu_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void saveMenu_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                model.OnSaveDocument(saveFileDialog1.FileName, saveFileDialog1.FilterIndex);
            }
        }

        private void SetMenuOptionEnable(ModelType mode)
        {
            bool on = true;
            switch(mode)
            {
                case ModelType.None:
                    on = false;
                    fillWhiteMenu.Enabled = on;
                    copyMenu.Enabled = on;
                    negativeMenu.Enabled = on;
                    thresholdMenu.Enabled = on;
                    warpMenu.Enabled = on;
                    warpBilinearMenu.Enabled = on;
                    drawMenu.Enabled = on;
                    drawMenu.Checked = false;
                    break;
                case ModelType.Generate:
                    drawMenu.Enabled = true;

                    fillWhiteMenu.Enabled = on;
                    copyMenu.Enabled = !on;
                    negativeMenu.Enabled = !on;
                    thresholdMenu.Enabled = !on;
                    warpMenu.Enabled = !on;
                    warpBilinearMenu.Enabled = !on;
                    
                    break;
                case ModelType.Process:
                    drawMenu.Enabled = true;

                    on = !on;
                    fillWhiteMenu.Enabled = on;
                    copyMenu.Enabled = !on;
                    negativeMenu.Enabled = !on;
                    thresholdMenu.Enabled = !on;
                    warpMenu.Enabled = !on;
                    warpBilinearMenu.Enabled = !on;
                    break;
            }    
        }

        private void FillGreenOption_Click(object sender, EventArgs e)
        {
            ImageGenerate.FillGreen(model);
            Invalidate();
        }

        private void DimMenuOption_Click(object sender, EventArgs e)
        {
            ImageProcess.OnFilterDim(model);
            Invalidate();
        }

        private void TintMenuOption_Click(object sender, EventArgs e)
        {
            ImageProcess.OnFilterTint(model);
            Invalidate();
        }

        private void LowpassFilter_Click(object sender, EventArgs e)
        {
            ImageProcess.OnFilterLowpass(model);
            Invalidate();
        }

        private void FillSeaGreenMenuOption_Click(object sender, EventArgs e)
        {
            ImageGenerate.FillSeaGreen(model);
            Invalidate();
        }

        private void horizontalGradient_Click(object sender, EventArgs e)
        {
            ImageGenerate.HorizontalGradient(model);
            Invalidate();
        }

        private void verticalBlueGradient_Click(object sender, EventArgs e)
        {
            ImageGenerate.VerticalGradient(model);
            Invalidate();
        }

        private void DiagonalGradient_Click(object sender, EventArgs e)
        {
            ImageGenerate.DiagonalGradient(model);
            Invalidate();
        }

        private void HorizontalLine_Click(object sender, EventArgs e)
        {
            ImageGenerate.HorizontalLine(model);
            Invalidate();
        }

        private void VerticalLine_Click(object sender, EventArgs e)
        {
            ImageGenerate.VerticalLine(model);
            Invalidate();
        }

        private void DiagonalLine_Click(object sender, EventArgs e)
        {
            ImageGenerate.DiagonalLine(model); 
            Invalidate();
        }

        private void MonochromeFilter_Click(object sender, EventArgs e)
        {
            ImageProcess.OnFilterMonochrom(model);
            Invalidate();
        }

        private void MedianMenuOption_Click(object sender, EventArgs e)
        {
            ImageProcess.OnFilterMedian(model);
            Invalidate();
        }
    }
}
