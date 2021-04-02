using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows;
using System.Windows.Forms;
using System.Windows.Media;

namespace ImageProcess
{
    public class ImageProcess :ImageEditor
    {
        // stickman filter stuff
        private Bitmap stickman;
        private Vector delta;
        private Vector gamma;
        private bool nearest = false;
        private int clickCnt =0;


        public override void SetMode(MODE m) 
        { 
            switch(m)
            {
                case MODE.Threshold:
                    mouseMode = MODE.Threshold;
                    break;
                case MODE.Draw:
                    mouseMode = MODE.Draw;
                    break;
                case MODE.Move:
                    break;
                case MODE.None:
                    break;
                case MODE.Warp:
                    clickCnt = 0;
                    nearest = false;
                    mouseMode = MODE.Warp;
                    break;
                case MODE.WarpNearest:
                    clickCnt = 0;
                    nearest = true;
                    mouseMode = MODE.Warp;
                    break;
            }
        }


        //
        //Filter Functions-----------------------------------------------------------------
        //

        /// <summary>
        /// this method sets each pixel to its ajacent median
        /// </summary>
        /// <param name="image"></param>
        public static void OnFilterMedian(Image image)
        {
            //reset the filtered image and make the same size as the input image
            image.Reset();
            int range = 1;
            Color pixel;
            int[] listR = new int[9];
            int[] listG = new int[9];
            int[] listB = new int[9];

            //loop over pixels
            for (int r = 0; r < image.PostImage.Height; r++)
            {
                for (int c = 0; c < image.PostImage.Width; c++)
                {
                    //set color arrays itterator
                    int itt = 0;
                    //loop over square around this pixel, watching bounteries
                    for (int i = -range; i <= range; i++)
                    {
                        //ensure not to go above or below the image
                        if ((r + i) >= 0 && (r + i) < image.PostImage.Height)
                        {
                            for (int j = -range; j <= range; j++)
                            {
                                //ensure not to go left or right of the image
                                if ((j + c) >= 0 && (j + c) < image.PostImage.Width)
                                {
                                    //record the channels
                                    pixel = image.BaseImage.GetPixel(c + j, r + i);
                                    listR[itt] = pixel.R;
                                    listG[itt] = pixel.G;
                                    listB[itt] = pixel.B;
                                    //incrament index for itterator
                                    itt++;
                                }
                                
                            }

                        }
                    }

                    //find median value and set
                    Array.Sort(listR);
                    Array.Sort(listG);
                    Array.Sort(listB);

                    pixel = Color.FromArgb(listR[4], listG[4], listB[4]);
                    image.PostImage.SetPixel(c, r, pixel);
                }
            }
        }


        public static void OnFilterMonochrom(Image image)
        {
            image.Reset();

            for (int r = 0; r < image.BaseImage.Height; r++)
            {
                for (int c = 0; c < image.BaseImage.Width; c++)
                {
                    Color pixel = image.BaseImage.GetPixel(c, r);
                    int avg = ClampColorElem((pixel.R + pixel.G + pixel.B) / 3.0);
                    pixel = Color.FromArgb(avg, avg, avg);
                    image.PostImage.SetPixel(c, r, pixel);

                }
            }
        }

        public static void OnFilterLowpass(Image image)
        {
            //reset the filtered image and make the same size as the input image
            image.Reset();
            int range = 1;

            //loop over pixels
            for (int r = 0; r < image.PostImage.Height; r++)
            {
                for (int c = 0; c < image.PostImage.Width; c++ )
                {
                    Color pixel = Color.Black;
                    int tallyR = 0;
                    int tallyG = 0;
                    int tallyB = 0;

                    //loop over square around this pixel, watching bounteries
                    for (int i = -range; i <= range; i++)
                    {
                        //ensure not to go above or below the image
                        if ((r + i) >= 0 && (r + i) < image.PostImage.Height)
                        {
                            for (int j = -range; j <= range; j++)
                            {
                                //ensure not to go left or right of the image
                                if ((j + c) >= 0 && (j + c) < image.PostImage.Width)
                                {
                                    //tally the channels
                                    pixel = image.BaseImage.GetPixel(c+j, r+i);
                                    tallyR += pixel.R;
                                    tallyG += pixel.G;
                                    tallyB += pixel.B;
                                }
                            }
                        }
                    }

                    //average values and set
                    int square = 2 * range + 1;
                    square *= square;
                    pixel = Color.FromArgb(tallyR / square, tallyG / square, tallyB/ square);
                    image.PostImage.SetPixel(c, r, pixel);
                }
            }
        }

        /// <summary>
        /// This filter dims the image by scaling each pixal value by 0.33
        /// </summary>
        /// <param name="image">the imave to be dimmed</param>
        public static void OnFilterDim(Image image)
        {
            //reset the image and make the same size as the input image
            image.Reset();

            for (int r = 0; r < image.PostImage.Height; r++)
            {
                for (int c = 0; c < image.PostImage.Width; c++)
                {
                    Color temp = image.BaseImage.GetPixel(c, r);
                    temp = ColorMultiply(0.33, temp);
                    image.PostImage.SetPixel(c, r, temp);
                }
            }
        }

        ///<summary>
        /// This filter will apply a green tint by decreasing the image
        /// intensity of the blue and red colors
        /// </summary>
        /// <param name="image"> The image to be processed </param>
        public static void OnFilterTint(Image image)
        {
            //reset the filtered image and make the same size as the input image
            image.Reset();

            for(int r = 0; r < image.PostImage.Height; r++)
            {
                for(int c = 0; c < image.PostImage.Width; c++)
                {
                    Color temp = image.BaseImage.GetPixel(c, r);
                    temp = Color.FromArgb(
                        ClampColorElem(0.33 * temp.R),
                        ClampColorElem(temp.G),
                        ClampColorElem(0.66 * temp.B));
                    image.PostImage.SetPixel(c, r, temp);
                }
            }
        }


        /// <summary>
        /// Example filter that computes a negative image.
        /// </summary>
        /// <param name="image"></param>
        public static void OnFilterNegative(Image image)
        {
            // Make the output image the same size as the input image
            image.Reset();

            for (int r = 0; r < image.BaseImage.Height; r++)
            {
                for (int c = 0; c < image.BaseImage.Width; c++)
                {
                    Color temp = image.BaseImage.GetPixel(c, r);
                    temp = Color.FromArgb(255 - temp.R,
                                          255 - temp.G,
                                          255 - temp.B);
                    image.PostImage.SetPixel(c, r, temp);
                }
            }
        }


        /// <summary>
        /// This is an example filter that looks at a specific location
        //  and determines a gray scale value we can use as a threshold.
        //  We'll then use that threshold to convert the image into a 
        ///  bi-level image (black and white only).
        /// </summary>
        /// <param name="image"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        public static void FilterThreshold(Image image, int x, int y)
        {
            if (x > image.BaseImage.Width || y > image.BaseImage.Height)
                return;

            // What is the monochrome value at location x,y in the
            // input image, not the filtered image!
            Color temp = image.BaseImage.GetPixel(x, y);
            int threshgray = (int)((temp.R + temp.G + temp.B) / 3);

            // Now do the image threshold
            // Make the output image the same size as the input image
            image.Reset();

            for (int r = 0; r < image.BaseImage.Height; r++)
            {
                for (int c = 0; c < image.BaseImage.Width; c++)
                {
                    // What is the gray value at this location?
                    temp = image.BaseImage.GetPixel(c, r);
                    int pixelgray = (int)((temp.R + temp.G + temp.B) / 3);

                    if (pixelgray >= threshgray)
                    {

                        // Set the pixel to white
                        image.PostImage.SetPixel(c, r, Color.White);
                    }
                    else
                    {
                        // Set the pixel to black
                        image.PostImage.SetPixel(c, r, Color.Black);
                    }

                }

            }

        }

        /// <summary>
        /// This function implements an image warping example that moves
        ///   an default image onto two specified points on the image.
        /// </summary>
        /// <param name="image"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        void FilterWarp(Image image, int x, int y)
        {
            // 
            // Step -1:  Ensure we have an image to warp onto our output.
            //

            if (stickman == null)
            {
                stickman = new Bitmap(Properties.Resources.Stickman);
            }

            // If the template image is empty, do nothing
            if (stickman.Height <= 0 || stickman.Width <= 0)
                return;

            // If out of bounds, do nothing
            //if (x < 0 || y < 0 || image.Width < x || image.Height < y)
            //    return;

            //
            // Step 0:  Handle the alternate mouse click feature.
            //

            // This handles the alternate mouse click feature
            // The first mouse click is just indicated on the
            // image, the second initiates the warping.
            if ((clickCnt & 1) == 1)
            {
                image.Reset();

                delta.X = x;
                delta.Y = y;

                // Draw a dot on the image
                for (int i = -1; i <= 1; i++)
                    for (int j = -1; j <= 1; j++)
                        if (x > 0 && y > 0 && image.BaseImage.Width > x && image.BaseImage.Height > y)
                            image.PostImage.SetPixel((int)(delta.X + i), (int)(delta.Y + j), Color.Red);
                return;
            }

            gamma.X = x;
            gamma.Y = y;

            // Draw a dot on the image
            for (int i = -1; i <= 1; i++)
                for (int j = -1; j <= 1; j++)
                    if (x > 0 && y > 0 && image.BaseImage.Width > x && image.BaseImage.Height > y)
                        image.PostImage.SetPixel((int)(gamma.X + i), (int)(gamma.Y + j), Color.Cyan);

            int w = stickman.Width;
            int h = stickman.Height;

            // 
            // Now we are actually going to do the warping work.
            //

            // These are the alignment points in the warp image
            // The destination points are delta and gamma
            Vector alpha = new Vector(w / 2, 0);
            Vector beta = new Vector(w / 2, h);

            // These are the corners of the warp image
            System.Windows.Point tl = new System.Windows.Point(0, h);
            System.Windows.Point tr = new System.Windows.Point(w, h);
            System.Windows.Point bl = new System.Windows.Point(0, 0);
            System.Windows.Point br = new System.Windows.Point(w, 0);

            //
            // Step 1:  Build a matrix that translates points in the source 
            // image to points in the destination image.  
            //

            // Translate the point we are going to rotate around to the origin
            Matrix m1 = new Matrix
            {
                OffsetX = -alpha.X,
                OffsetY = -alpha.Y
            };

            // Rotate -90 degrees
            Matrix r1 = Matrix.Identity;
            r1.M11 = 0;
            r1.M21 = 1;
            r1.M12 = -1;
            r1.M22 = 0;

            // Rotate onto the delta to gamma vector.
            Vector v = gamma - delta;
            v.Normalize();
            Matrix r2 = new Matrix
            {
                M11 = v.X,
                M21 = -v.Y,
                M12 = v.Y,
                M22 = v.X
            };

            // Scale image to the size of the output location.
            Matrix s = new Matrix();
            double scale = (gamma - delta).Length / (beta - alpha).Length;
            s.Scale(scale, scale);

            // Translate to the destination
            Matrix m2 = new Matrix
            {
                OffsetX = delta.X,
                OffsetY = delta.Y
            };

            // Multiply all of these matrices together.
            Matrix src_to_dest = m1 * r1 * r2 * s * m2;

            //
            // Step 2:  Create an inverse version of that matrix.
            //
            Matrix dest_to_src = src_to_dest;
            dest_to_src.Invert();

            // 
            // Step 3:  Determine the bounding box in the destination image for
            // the stickman image.  
            //
            System.Windows.Point itl = src_to_dest.Transform(tl);
            System.Windows.Point itr = src_to_dest.Transform(tr);
            System.Windows.Point ibl = src_to_dest.Transform(bl);
            System.Windows.Point ibr = src_to_dest.Transform(br);
            double minx = Min4(itl.X, itr.X, ibl.X, ibr.X);
            double maxx = Max4(itl.X, itr.X, ibl.X, ibr.X);
            double miny = Min4(itl.Y, itr.Y, ibl.Y, ibr.Y);
            double maxy = Max4(itl.Y, itr.Y, ibl.Y, ibr.Y);

            // Make sure the bounding box is in the image
            if (minx < 0)
                minx = 0;

            if (maxx >= image.PostImage.Width)
                maxx = image.PostImage.Width - 1;

            if (miny < 0)
                miny = 0;

            if (maxy >= image.PostImage.Height)
                maxy = image.PostImage.Height - 1;

            // 
            // Step 4:  Loop over the pixels in the bounding box, determining 
            // their color in the source image.  We use op to indicate pixel 
            // locations in the output image and ip to indicate locations in the
            // input image.
            //

            for (int y2 = (int)(miny + .5); y2 <= (int)(maxy + .5); y2++)
            {
                for (int x2 = (int)(minx + .5); x2 <= (int)(maxx + .5); x2++)
                {
                    // This is the equivalent point in the source image (stickman)
                    // This is the equivalent point in the source image 
                    double x1 = dest_to_src.M11 * x2 + dest_to_src.M21 * y2 + dest_to_src.OffsetX;
                    double y1 = dest_to_src.M12 * x2 + dest_to_src.M22 * y2 + dest_to_src.OffsetY;

                    int ix = (int)(x1);
                    double ixf = x1 - ix;      // Fractional part
                    int iy = (int)(y1);
                    double iyf = y1 - iy;

                    // Notice that I only use pixels that are going to be 
                    // within the stickman image and have pixels all of the
                    // way around.  This is so our bilinear interpolation
                    // will have neighbors on all sides!  That's why we
                    // have w-1 and h-1 here:
                    if (ix >= 0 && ix < w - 1 &&
                        iy >= 0 && iy < h - 1)
                    {
                        // This is a test for the color white, which is what I'll 
                        // consider to be transparent.  We only use colors that are
                        // not the pure white color.
                        if (!(stickman.GetPixel(ix, iy).A< 5 || ColorEqual(stickman.GetPixel(ix, iy), Color.White)))
                        {
                            if (nearest)
                            {
                                image.PostImage.SetPixel(x2, y2, stickman.GetPixel(ix, iy));
                            }
                            else
                            {
                                // Bilinear interpolation version
                                Color upLeft = stickman.GetPixel(ix, iy);
                                Color lowLeft = stickman.GetPixel(ix, iy + 1);
                                Color upRight = stickman.GetPixel(ix + 1, iy);
                                Color lowRight = stickman.GetPixel(ix + 1, iy + 1);
                                Color temp = ColorMultiply((1.0 - ixf) * (1.0 - iyf), upLeft);
                                temp = ColorAdd(temp, ColorMultiply((1.0 - ixf) * iyf, lowLeft));
                                temp = ColorAdd(temp, ColorMultiply(ixf * (1.0 - iyf), upRight));
                                temp = ColorAdd(temp, ColorMultiply(ixf * iyf, lowRight));

                                image.PostImage.SetPixel(x2, y2, temp);
                            }
                        }
                    }
                }
            }
        }



        //
        //Mouse Handlers--------------------------------------------------------------------
        //

        //
        /// <summary>
        /// This function is called when the mouse is pressed over the base
        /// image.  The x,y coordinate is in the image.
        /// </summary>
        /// <param name="image"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        public override void MousePress(Image image, int x, int y)
        {
            // We count the mouse clicks
            clickCnt++;
            y -= image.Offset;

            if (x < 0 || y < 0)
                return;

            switch (mouseMode)
            {
                case MODE.Draw:
                    if (x < image.PostImage.Width && y < image.PostImage.Height)
                        image.PostImage.SetPixel(x, y, Color.Green);
                    mouseMode = MODE.Move;
                    break;

                case MODE.Threshold:
                    FilterThreshold(image, x, y);
                    break;

                case MODE.Warp:
                    FilterWarp(image, x, y);
                    break;
            }
        }


        /// <summary>
        /// This function is called when the mouse is moved over the base
        /// image.  The x,y coordinate is in the image.
        /// </summary>
        /// <param name="image"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        public override void MouseMove(Image image, int x, int y)
        {

            y -= image.Offset;
            if (x < 0 || y < 0)
                return;

            switch (mouseMode)
            {
                case MODE.Move:
                    if (x < image.PostImage.Width && y < image.PostImage.Height)
                        image.PostImage.SetPixel(x, y, Color.Green);
                    break;
            }
        }

        //
        // Name :         MouseRelease()
        // Description :  Reset mouse to wait for next mose pres
        //
        public override void MouseRelease()
        {
            // We count the mouse clicks
            if(mouseMode == MODE.Move)
                mouseMode = MODE.Draw;
        }


        //
        //helper functions------------------------------------------------------------
        //


         //
        //helper functions------------------------------------------------------------
        //


        //
        // Name :         ColorMultiply(double val, Color c)
        // Description :  Multiplys a scalar onto an Color.
        //
        private static Color ColorMultiply(double val, Color c)
        {
            return Color.FromArgb(
                    ClampColorElem(val * c.R),
                    ClampColorElem(val * c.G),
                    ClampColorElem(val * c.B));
        }

        //
        // Name :         ClampColorElem(double val)
        // Description :  Clamps a vales to be between 0 and 255.
        //
        private static int ClampColorElem(double val)
        {
            return (int)Math.Max(Math.Min(val, 255), 0);
        }

        //
        // Name :         ColorAddColor(Color a, Color b)
        // Description :  Adds to colors together
        //
        private static Color ColorAdd(Color a, Color b)
        {
            return Color.FromArgb(
                    ClampColorElem(a.R + b.R),
                    ClampColorElem(a.G + b.G),
                    ClampColorElem(a.B + b.B));
        }

        //
        // Name :         ColorEqual(Color a, Color b)
        // Description :  Check if two colors are equal
        //
        private static bool ColorEqual(Color a, Color b)
        {
            return a.R == b.R && a.G == b.G && a.B == b.B;
        }

        // These functions are needed to simplify mins and maxes...
        private static double Min4(double a, double b, double c, double d)
        {
            double r = a;
            if (b < r)
                r = b;
            if (c < r)
                r = c;
            if (d < r)
                r = d;
            return r;
        }

        private static double Max4(double a, double b, double c, double d)
        {
            double r = a;
            if (b > r)
                r = b;
            if (c > r)
                r = c;
            if (d > r)
                r = d;
            return r;
        }


    }
}
