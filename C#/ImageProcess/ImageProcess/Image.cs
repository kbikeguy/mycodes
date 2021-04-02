using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ImageProcess
{
    public class Image
    {
        protected enum MODE
        {
            ORIGINAL, POST
        }
        private int offset;
        private Bitmap baseImage;
        private Bitmap postImage;
        private MODE mode = MODE.ORIGINAL;

        public Bitmap BaseImage { get => baseImage;  }
        public Bitmap PostImage { get => postImage; }
        public int Offset { get => offset; }

        /// <summary>
        /// yOffset should be the menu bar height
        /// </summary>
        /// <param name="yOffest"></param>
        public Image(int yOffest)
        {
            offset = yOffest;
            baseImage = new Bitmap(600, 400);
        }

        /// <summary>
        /// reset to base image
        /// </summary>
        public void Reset()
        {
            postImage = new Bitmap(baseImage);
        }

        /// <summary>
        ///  open file if given, otherwise default image from resources
        /// </summary>
        /// <param name="path">path to open</param>
        /// <returns></returns>
        public bool OnOpenDocument(string path = null)
        {
            //open file if given, other wise open default
            try
            {
                if (path == null)
                    baseImage = new Bitmap(Properties.Resources.Stickman);
                else
                    baseImage = new Bitmap(path);

                postImage = new Bitmap(baseImage); //copy bitmap

                mode = MODE.POST;
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message, "Error");
                return false;
            }

            return true;
        }


        //save base is the mode is the original (generate), and save the edited one if 
        // if the most is post process (process)
        public bool OnSaveDocument(string path, int index)
        {
            if (mode == MODE.ORIGINAL)
            {
                return OnSave(path, index, baseImage);
            }
            else if (mode == MODE.POST)
            {
                return OnSave(path, index, postImage);
            }
            return false;
        }


        public void OnPaint(PaintEventArgs e)
        {
            Graphics g = e.Graphics;

            //color the background
            Brush b = new SolidBrush(Color.DarkGray);
            g.FillRectangle(b, e.ClipRectangle);

            if (mode == MODE.ORIGINAL)
            {
                //draw only the original
                g.DrawImage(baseImage, 0, offset);
            }
            else if (mode == MODE.POST)
            {
                //draw BOTH the original and post processed image
                if (baseImage == null)
                    return;

                g.DrawImage(baseImage, 0, offset, baseImage.Width, baseImage.Height);
                g.DrawImage(postImage, baseImage.Width + 2, offset, postImage.Width, postImage.Height);

                //
                // Draw a bar between the two images
                //
                Pen black = new Pen(Color.Black);
                black.Width = 3;

                g.DrawLine(black, new PointF(baseImage.Width, offset), new PointF(baseImage.Width, baseImage.Height + offset));
            }
        }

        /// <summary>
        /// function to save a image. Supports, jpeg, gif, png, and bmp
        /// </summary>
        /// <param name="path">location to save</param>
        /// <param name="index">index (format type) from file dialog</param>
        /// <param name="image">image to save</param>
        /// <returns></returns>
        public bool OnSave(string path, int index, Bitmap image)
        {
            try
            {
                switch (index)
                {
                    case 1:
                        image.Save(path, ImageFormat.Jpeg);
                        break;
                    case 2:
                        image.Save(path, ImageFormat.Gif);
                        break;
                    case 3:
                        image.Save(path, ImageFormat.Png);
                        break;
                    case 4:
                        image.Save(path, ImageFormat.Bmp);
                        break;

                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message, "Error");
                return false;
            }

            return true;
        }

        public void Close()
        {
            baseImage = null;
            postImage = null;
        }
    }
}
