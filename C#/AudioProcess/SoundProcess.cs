using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AudioProcess
{
    class SoundProcess
    {
        public SoundProcess()
        {
        }

        /// <summary>
        /// this method reverses the array of samples using Array.reverse(sample_array)
        /// </summary>
        /// <param name="sound"></param>
        public void Backwards(Sound sound)
        {
            if (sound == null)
            {
                MessageBox.Show("Need a sound loaded first", "Process Error");
                return;
            }

            Array.Reverse(sound.Samples);
        }

        /// <summary>
        /// this method speeds up the audio by removing all of the odd indexed
        /// values within the sample array
        /// </summary>
        /// <param name="sound"></param>
        public void Fast(Sound sound)
        {
            if (sound == null)
            {
                MessageBox.Show("Need a sound loaded first", "Process Error");
                return;
            }


            //pull needed sound file encoding parameters
            int n = sound.Samples.Length;

            //setup progress bar
            ProgressBar progress = new ProgressBar();
            progress.Runworker();

            //store # channels
            int channels = sound.Format.Channels;

            //init new float list to be converted to array later
            List<float> slowSamples = new List<float>();

            //add in the averages
            for (int i = 0; i < sound.Samples.Length; i += channels * 2)
            {

                for(int c = 0; c < channels; c++)
                    slowSamples.Add(sound.Samples[i + c]);

                progress.UpdateProgress((double)i / n);
            }

            sound.Samples = slowSamples.ToArray();
        }

        /// <summary>
        /// this method slows down the audio by adding a new sample in between
        /// all existing samples that is the average of the sample on the left
        /// and right. for instance if the list was [100, 90, 70, 20], the new
        /// list will be [100, 95, 90, 80, 70, 45, 20]
        /// </summary>
        /// <param name="sound"></param>
        public void Slow(Sound sound)
        {
            if (sound == null)
            {
                MessageBox.Show("Need a sound loaded first", "Process Error");
                return;
            }


            //pull needed sound file encoding parameters
            int n = sound.Samples.Length;            

            //setup progress bar
            ProgressBar progress = new ProgressBar();
            progress.Runworker();

            //store # channels
            int channels = sound.Format.Channels;

            //init new float list to be converted to array later
            List<float> slowSamples = new List<float>();
                     
            //add in the averages
            for (int i = 0; i < sound.Samples.Length - channels; i += channels)
            {
                if (channels == 2)
                {                    
                    float avg = (sound.Samples[i] + sound.Samples[i + channels]) / 2;
                    slowSamples.Add(sound.Samples[i]);
                    slowSamples.Add(sound.Samples[i]);
                    slowSamples.Add(avg);
                    slowSamples.Add(avg);                    
                }

                else
                {
                    float avg = (sound.Samples[i] + sound.Samples[i + 1]) / 2;
                    slowSamples.Add(sound.Samples[i]);
                    slowSamples.Add(avg);
                }

                progress.UpdateProgress((double)i / n);
            }
            
            sound.Samples = slowSamples.ToArray();
        }

        /// <summary>
        /// this method adds a tremolo effect by multiplying each index by an
        /// amplitude that is calculated with the equation a = 1 + d * sin(f * 2 * pi * t)
        /// where a is the amplitude, d is the depth(in this case 0.2), f is 
        /// the tremelo frequency(in this case 4), and t is the current time
        /// </summary>
        /// <param name="sound"></param>
        public void Tremolo(Sound sound)
        {
            if (sound == null)
            {
                MessageBox.Show("Need a sound loaded first", "Process Error");
                return;
            }

            //pull needed sound file encoding parameters
            int n = sound.Samples.Length;

            // Keep track of time
            float time = 0;

            //setup progress bar
            ProgressBar progress = new ProgressBar();
            progress.Runworker();

            //store # channels
            int channels = sound.Format.Channels;          

            //set tremolo vals  
            float d = 0.2f;
            float f = 4f;

            //multiple each index in the audio samples array by the tremolo amplitude
            for (int i = 0; i < sound.Samples.Length; i += channels, time += 1.0f / sound.Format.SampleRate)
            {
                float tremolo = (float)(1 + d * Math.Sin(f * 2 * Math.PI * time));
               
                for (int c = 0; c < channels; c++)
                {
                    if (float.IsInfinity(sound.Samples[i + c] * tremolo))
                        sound.Samples[i + c] = float.MaxValue;
                    else
                        sound.Samples[i + c] = sound.Samples[i + c] * tremolo;
                }


                progress.UpdateProgress((double)i / n);
            }
        }   

        /// <summary>
        /// this method scales the volume of the audio from 0% to 200% during the first 
        /// 1.5 seconds, holds it at 200%, and then scales it from 200% to 0% 
        /// during the last 1.5 seconds. If the audio sample is less than 3 seconds
        /// long, the method returns without doing anything
        /// </summary>
        /// <param name="sound"></param>
        public void RampInOut(Sound sound)
        {
            if (sound == null)
            {
                MessageBox.Show("Need a sound loaded first", "Process Error");
                return;
            }

            if (sound.Duration < 3)
            {
                MessageBox.Show("Need a sample at least 3 seconds long", "Process Error");
                return;
            }

            //pull needed sound file encoding parameters
            int n = sound.Samples.Length;

            // Keep track of time
            float time = 0;

            //setup progress bar
            ProgressBar progress = new ProgressBar();
            progress.Runworker();

            //store # channels
            int channels = sound.Format.Channels;

            //set duration
            float duration = sound.Duration;

            for (int i = 0; i < sound.Samples.Length; i += channels, time += 1.0f / sound.Format.SampleRate)
            {
                float ramp = 2.0f;
                if (time <= 1.5)
                {
                    ramp = time / 0.75f;
                }
                else if (time >= duration - 1.5)
                {
                    ramp = (duration - time) / 0.75f;
                }


                for (int c = 0; c < channels; c++)
                {
                    if (float.IsInfinity(sound.Samples[i + c] * ramp))
                        sound.Samples[i + c] = float.MaxValue;
                    else
                        sound.Samples[i + c] = sound.Samples[i + c] * ramp;
                }
                    

                progress.UpdateProgress((double)i / n);
            }
        }

        /// <summary>
        /// this method scales the volume of the audio from 0% to 100% during the first 
        /// 0.5 seconds. If the audio sample is less than 0.5 seconds
        /// long, the method returns without doing anything
        /// </summary>
        /// <param name="sound"></param>
        public void Ramp(Sound sound)
        {
            if (sound == null)
            {
                MessageBox.Show("Need a sound loaded first", "Process Error");
                return;
            }
            if (sound.Duration < 0.5)
            {
                MessageBox.Show("Need a sample at least 0.5 seconds long", "Process Error");
                return;
            }

            //pull needed sound file encoding parameters
            int n = sound.Samples.Length;

            // Keep track of time
            float time = 0;

            //setup progress bar
            ProgressBar progress = new ProgressBar();
            progress.Runworker();

            //store # channels
            int channels = sound.Format.Channels;
            for (int i = 0; i < sound.Samples.Length; i += channels, time += 1.0f / sound.Format.SampleRate)
            {
                float ramp;
                if (time < 0.5)
                {
                    ramp = time / 0.5f;
                }
                else
                {
                    ramp = 1;
                }

                for (int c = 0; c < channels; c++)
                    sound.Samples[i + c] = sound.Samples[i + c] * ramp;

                progress.UpdateProgress((double)i / n);
            }
        }

        /// <summary>
        /// Increases or descrease the volume of a sound
        /// </summary>
        /// <param name="sound">the sound to change</param>
        /// <param name="volume">the new amplitude multiplier</param>
        public void OnProcessVolume(Sound sound, float volume)
        {
            if (sound == null)
            {
                MessageBox.Show("Need a sound loaded first", "Process Error");
                return;
            }


            //pull needed sound file encoding parameters
            int n = sound.Samples.Length;

            //setup progress bar
            ProgressBar progress = new ProgressBar();
            progress.Runworker();

            for (int i = 0; i < n; i++)
            {
                sound.Samples[i] = sound.Samples[i] * volume;

                progress.UpdateProgress( (double)i / n);
            }
        }
    }
}
