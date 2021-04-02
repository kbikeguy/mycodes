using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AudioProcess
{
    public struct SineParams
    {
        public float freq1;
        public float freq2;
        public float sampleRate;
        public float amplitude;
    }
    class SoundGenerate
    {


        private SineParams sineParams;

        public SoundGenerate()
        {
            sineParams.freq1 = 440.0f;
            sineParams.freq2 = 440.0f;
            sineParams.amplitude = 1f;
        }

        public void MakeParamSine()
        {
            Generic_Sine dlg = new Generic_Sine(sineParams);
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                sineParams = dlg.SineParams;
            }
        }

        /// <summary>
        /// this method adds all of the odd harmonics from 3 to the Nyquist frequency
        /// to the fundimental frequency in each index in a sinewave generator
        /// </summary>
        /// <param name="sound"></param>
        public void MakeOddHarmonics(Sound sound)
        {
            if (sound == null)
            {
                MessageBox.Show("Need a sound loaded first", "Generation Error");
                return;
            }

            //pull needed sound file encoding parameters
            int sampleRate = sound.Format.SampleRate;
            int channels = sound.Format.Channels;
            float duration = sound.Duration - 1.0f / sampleRate;
            int Nyquist = sampleRate / 2;

            //setup progress bar
            ProgressBar progress = new ProgressBar();
            progress.Runworker();

            //make the sine wave
            int index = 0;
            for (double time = 0.0; time < duration; time += 1.0 / sampleRate)
            {
                //make the value at this frame
                float val = (float)(sineParams.amplitude * Math.Sin(time * 2 * Math.PI * sineParams.freq1));

                //add in all harmonics
                for (int harmonic = 3; harmonic <= Nyquist; harmonic += 2)
                {
                    val += (float)((sineParams.amplitude / harmonic) * Math.Sin(time * 2 * Math.PI * sineParams.freq1 * harmonic));
                }


                //fill all channels with the value
                for (int c = 0; c < channels; c++)
                {
                    sound.Samples[index + c] = val;
                }

                index += channels;

                progress.UpdateProgress(time / duration);
            }
        }

        /// <summary>
        /// this method adds all of the harmonics from 2 to the Nyquist frequency
        /// to the fundimental frequency in each index in a sinewave generator
        /// </summary>
        /// <param name="sound"></param>
        public void MakeAllHarmonics(Sound sound)
        {
            if (sound == null)
            {
                MessageBox.Show("Need a sound loaded first", "Generation Error");
                return;
            }

            //pull needed sound file encoding parameters
            int sampleRate = sound.Format.SampleRate;
            int channels = sound.Format.Channels;
            float duration = sound.Duration - 1.0f / sampleRate;
            int Nyquist = sampleRate / 2;

            //setup progress bar
            ProgressBar progress = new ProgressBar();
            progress.Runworker();

            //make the sine wave
            int index = 0;
            for (double time = 0.0; time < duration; time += 1.0 / sampleRate)
            {
                //make the value at this frame
                float val = (float)(sineParams.amplitude * Math.Sin(time * 2 * Math.PI * sineParams.freq1));

                //add in all harmonics
                for (int harmonic = 2; harmonic <= Nyquist; harmonic++)
                {
                    val += (float)((sineParams.amplitude / harmonic ) * Math.Sin(time * 2 * Math.PI * sineParams.freq1 * harmonic));
                }
                

                //fill all channels with the value
                for (int c = 0; c < channels; c++)
                {
                    sound.Samples[index + c] = val;
                }

                index += channels;

                progress.UpdateProgress(time / duration);
            }
        }

        /// <summary>
        /// this method adds the 3rd, 5th, and 7th harmonics to the fundimental 
        /// frequency in each index in a sinewave generator
        /// </summary>
        /// <param name="sound"></param>
        public void Make357Sine(Sound sound)
        {
            if (sound == null)
            {
                MessageBox.Show("Need a sound loaded first", "Generation Error");
                return;
            }

            //pull needed sound file encoding parameters
            int sampleRate = sound.Format.SampleRate;
            int channels = sound.Format.Channels;
            float duration = sound.Duration - 1.0f / sampleRate;

            //setup progress bar
            ProgressBar progress = new ProgressBar();
            progress.Runworker();

            //make the sine wave
            int index = 0;
            for (double time = 0.0; time < duration; time += 1.0 / sampleRate)
            {
                //make the value at this frame
                float val = (float)(sineParams.amplitude * Math.Sin(time * 2 * Math.PI * sineParams.freq1));

                //add in 3rd, 5th, and 7th harmonics
                val += (float)((sineParams.amplitude / 3) * Math.Sin(time * 2 * Math.PI * sineParams.freq1 * 3));
                val += (float)((sineParams.amplitude / 5) * Math.Sin(time * 2 * Math.PI * sineParams.freq1 * 5));
                val += (float)((sineParams.amplitude / 7) * Math.Sin(time * 2 * Math.PI * sineParams.freq1 * 7));

                //fill all channels with the value
                for (int c = 0; c < channels; c++)
                {
                    sound.Samples[index + c] = val;
                }

                index += channels;

                progress.UpdateProgress(time / duration);
            }
        }

        /// <summary>
        /// this method adds the 2nd, 3rd, and 4th harmonics to the fundimental 
        /// frequency in each index in a sinewave generator
        /// </summary>
        /// <param name="sound"></param>
        public void Make234Sine(Sound sound)
        {
            if (sound == null)
            {
                MessageBox.Show("Need a sound loaded first", "Generation Error");
                return;
            }

            //pull needed sound file encoding parameters
            int sampleRate = sound.Format.SampleRate;
            int channels = sound.Format.Channels;
            float duration = sound.Duration - 1.0f / sampleRate;

            //setup progress bar
            ProgressBar progress = new ProgressBar();
            progress.Runworker();

            //make the sine wave
            int index = 0;
            for (double time = 0.0; time < duration; time += 1.0 / sampleRate)
            {
                //make the value at this frame
                float val = (float)(sineParams.amplitude * Math.Sin(time * 2 * Math.PI * sineParams.freq1));

                //add in 2nd, 3rd, and 4th harmonics
                val += (float)((sineParams.amplitude / 2) * Math.Sin(time * 2 * Math.PI * sineParams.freq1 * 2));
                val += (float)((sineParams.amplitude / 3) * Math.Sin(time * 2 * Math.PI * sineParams.freq1 * 3));
                val += (float)((sineParams.amplitude / 4) * Math.Sin(time * 2 * Math.PI * sineParams.freq1 * 4));

                //fill all channels with the value
                for (int c = 0; c < channels; c++)
                {
                    sound.Samples[index + c] =  val;
                }

                index += channels;

                progress.UpdateProgress(time / duration);
            }
        }

        /// <summary>
        /// Example procedure that generates a 2 channel sine wave.
        /// The sine wave frequency for channel 1 is set by freq1
        /// The sine wave frequency for channel 2 is set by freq2
        /// </summary>
        /// <param name="sound">The Sound to fill</param>
        public void MakeSineAdditive(Sound sound)
        {

            if (sound == null)
            {
                MessageBox.Show("Need a sound loaded first", "Generation Error");
                return;
            }

            //pull needed sound file encoding parameters
            int sampleRate = sound.Format.SampleRate;
            int channels = sound.Format.Channels;
            float duration = sound.Duration - 1.0f / sampleRate;

            //setup progress bar
            ProgressBar progress = new ProgressBar();
            progress.Runworker();

            //make the sine wave
            int index = 0;
            for (double time = 0.0; time < duration; time += 1.0 / sampleRate)
            {
                //make the value at this frame
                float val = (float)(sineParams.amplitude * Math.Sin(time * 2 * Math.PI * sineParams.freq1));
                float val2 = (float)(sineParams.amplitude * Math.Sin(time * 2 * Math.PI * sineParams.freq2));
                sound.Samples[index] = val;

                //sanity check for stereo
                if (channels == 2)
                    sound.Samples[index + 1] = val2;

                index += channels;

                progress.UpdateProgress(time / duration);
            }
        }

        /// <summary>
        /// Example procedure that generates a sine wave.
        /// The sine wave frequency is set by freq1
        /// </summary>
        /// <param name="sound">The Sound to fill</param>
        public void MakeSine(Sound sound)
        {

            if (sound == null)
            {
                MessageBox.Show("Need a sound loaded first", "Generation Error");
                return;
            }

            //pull needed sound file encoding parameters
            int sampleRate = sound.Format.SampleRate;
            int channels = sound.Format.Channels;
            float duration = sound.Duration - 1.0f / sampleRate;

            //setup progress bar
            ProgressBar progress = new ProgressBar();
            progress.Runworker();

            //make the sine wave
            int index = 0;
            for (double time = 0.0; time < duration; time += 1.0 / sampleRate)
            {
                //make the value at this frame
                float val = (float)(sineParams.amplitude * Math.Sin(time * 2 * Math.PI * sineParams.freq1));

                //fill all channels with the value
                for (int c = 0; c < channels; c++)
                {
                    sound.Samples[index + c] = val;
                }

                index += channels;

                progress.UpdateProgress(time / duration);
            }
        }

    }
}
