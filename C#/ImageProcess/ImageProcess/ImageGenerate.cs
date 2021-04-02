using System;
using System.Drawing;

namespace ImageProcess
{
    public class ImageGenerate : ImageEditor
    {

        public override void SetMode(MODE m) {
            switch (m)
            {
                case MODE.None:
                    mouseMode = MODE.None;
                    break;
                case MODE.Threshold:
                    break;
                case MODE.Draw:
                    mouseMode = MODE.Draw;
                    break;
                case MODE.Move:
                    break;
                case MODE.Warp:
                    break;
                case MODE.WarpNearest:
                    break;
            }
        }

        //
        //helper functions-------------------------------------------
        //

        /// <summary>
        /// this method find the intercept of two points given their slope
        /// </summary>
        /// <param name="p"> the point </param>
        /// <param name="start"> the bottom left corner of the image </param>
        /// <param name="m2"> the slope of p2 </param>
        /// <returns> intercept </returns>
        private static Point FindLineIntercept2(Point p1, Point p2, double m2, Point p0)
        {
            //the value to store the intercept
            Point intercept = new Point();
            if (p1.X == p0.X && p1.Y == p2.Y)
                intercept.Y = 0;
            //find the slope for p1
            //value = (p2.X - p0.X)(p1.Y - p0.Y) - (p1.X - p0.X)(p2.Y - p0.Y)
            double val = (p2.X - p0.X) * (p1.Y - p0.Y) - (p1.X - p0.X) * (p2.Y - p0.Y);
            double m1;
            
            //above line
            if (val > 0)
                m1 = -m2;
            else if (val < 0)
                m1 = Math.Tan((180 - Math.Atan(m2)*(180 / Math.PI)) * (Math.PI / 180));
            else
               return p1;

            intercept.X = (int)Math.Round(((m2 * p2.X - m1 * p1.X) - (p2.Y - p1.Y)) / (m2 - m1));

            //𝑦=𝑚1(h-𝑥1) +y1
            intercept.Y = (int)Math.Round(m1 * (intercept.X - p1.X) + p1.Y);

            return intercept;
        }


        /// <summary>
        /// this method takes in a point p, and a line given by its end points start and end
        /// it calulates where the orthogonal intercept will be on the line from the point
        /// </summary>
        /// <param name="p"> the point </param>
        /// <param name="start"> the start of the line </param>
        /// <param name="end"> the end of the line </param>
        /// <returns> the intercept point </returns>
        private static Point FindLineIntercept(Point p, Point start, Point end)
        {
            Point intercept = new Point();
            //y2 = end.Y
            //x2 = end.X
            //y1 = start.Y
            //x1 = start.X
            //y3 = p.Y
            //x3 = p.X

            double denominator = ((end.Y - start.Y) * (end.Y - start.Y) + (end.X - start.X) * (end.X - start.X));
            double k = ((end.Y - start.Y) * (p.X - start.X) - (end.X - start.X) * (p.Y - start.Y)) / denominator;
            intercept.X = (int)Math.Round(p.X - k * (end.Y - start.Y));
            intercept.Y = (int)Math.Round(p.Y + k * (end.X - start.X));

            return intercept;
        }

        /// <summary>
        /// Clamps a vales to be between 0 and 255.
        /// </summary>
        /// <param name="val"></param>
        /// <returns></returns>
        private static int ClampColorElem(double val)
        {
            return (int)Math.Max(Math.Min(val, 255), 0);
        }

        private static double Dist2Points(Point p1, Point p2)
        {
            int distX = p1.X - p2.X;
            int distY = p1.Y - p2.Y;
            distX *= distX;
            distY *= distY;
            double result = Math.Sqrt(distX + distY);
            
            return result;
        }
        private static double MinDist(Point a, Point b, Point p)
        {
            //y = 399/599x - 399
            double ab_DOT_bp;
            double ab_DOT_ap;
            double dist = 0, x, y;

            //build vectors
            Point ab = new Point();
            ab.X = b.X - a.X;
            ab.Y = b.Y - a.Y;

            Point bp = new Point();
            bp.X = p.X - b.X;
            bp.Y = p.Y - b.Y;

            Point ap = new Point();
            ap.X = p.X - a.X;
            ap.Y = p.Y - a.Y;

            //dot products
            ab_DOT_bp = ab.X * bp.X + ab.Y * bp.Y;
            ab_DOT_ap = ab.X * ap.X + ab.Y * ap.Y;

            if (ab_DOT_bp > 0)
            {
                x = p.X - b.X;
                y = p.Y - b.Y;
                dist = Math.Sqrt(x * x + y * y);
            }
            
            else if(ab_DOT_ap < 0)
            {
                x = p.X - a.X;
                y = p.Y = a.Y;
                dist = Math.Sqrt(x * x + y * y);
            }

            else
            {
                dist = Math.Sqrt(ab.X * ab.X + ab.Y * ab.Y);
                dist = Math.Abs(ab.X * ap.Y - ab.Y * ap.Y) / dist;
            }

            return dist;
        }
        static double minDistance(Point A, Point B, Point E)
        {

            // vector AB 
            Point AB = new Point();
            AB.X = B.X - A.X;
            AB.Y = B.Y - A.Y;

            // vector BP 
            Point BE = new Point();
            BE.X = E.X - B.X;
            BE.Y = E.Y - B.Y;

            // vector AP 
            Point AE = new Point();
            AE.X = E.X - A.X;
            AE.Y = E.Y - A.Y;

            // Variables to store dot product 
            double AB_BE, AB_AE;

            // Calculating the dot product 
            AB_BE = (AB.X * BE.X + AB.Y * BE.Y);
            AB_AE = (AB.X * AE.X + AB.Y * AE.Y);

            // Minimum distance from 
            // point E to the line segment 
            double reqAns = 0;

            // Case 1 
            if (AB_BE > 0)
            {

                // Finding the magnitude 
                double y = E.Y - B.Y;
                double x = E.X - B.X;
                reqAns = Math.Sqrt(x * x + y * y);
            }

            // Case 2 
            else if (AB_AE < 0)
            {
                double y = E.Y - A.Y;
                double x = E.X - A.X;
                reqAns = Math.Sqrt(x * x + y * y);
            }

            // Case 3 
            else
            {

                // Finding the perpendicular distance 
                double x1 = AB.X;
                double y1 = AB.Y;
                double x2 = AE.X;
                double y2 = AE.Y;
                double mod = Math.Sqrt(x1 * x1 + y1 * y1);
                reqAns = Math.Abs(x1 * y2 - y1 * x2) / mod;
            }
            return reqAns;
        }


        //
        //basic generation functions-------------------------------------------
        //

        ///<summary>
        ///this class function fills the image with a diagonal gradient with 
        ///Green as the top-right pixel and Red as the bottom-left pixel
        /// </summary>
        /// <param name="image">the image to fill</param>
        public static void DiagonalGradient(Image image)
        {
            //set up variables
            int height = image.BaseImage.Height;
            int width = image.BaseImage.Width;
            Point topRight = new Point();
            Point botLeft = new Point();
            Point curPixel = new Point(0, 0);
            Point intercept = new Point();
            Point intercept2 = new Point();
            topRight.X = width - 1;
            topRight.Y = 0;
            botLeft.X = 0;
            botLeft.Y = height - 1;
            double denomitor = Dist2Points(topRight, botLeft);
            double trialDenomitor = Math.Sqrt(width * width + height * height);
            Color green = Color.Green;  //(255, 0, 128, 0)
            Color red = Color.Red;      //(255, 255, 0, 0)
            Color pixel = new Color();
            double slope = (double)(topRight.Y - botLeft.Y) / (topRight.X - botLeft.X);
            //itterate the image
            for (int r = 0; r < height; r++)
            {
                for (int c = 0; c < width; c++)
                {
                    //assign current pixel index
                    curPixel.X = c;
                    curPixel.Y = r;
                    
                    //find the orthogonal projection point on the line from the current pixel
                    //intercept = FindLineIntercept(curPixel, topRight, botLeft);

                    //find the symetrical projection point on the line from the current pixel
                    intercept = FindLineIntercept2(curPixel, botLeft, slope, topRight);

                    double numerator = Dist2Points(botLeft, intercept);
                    double shade = (numerator / denomitor);
                    pixel = Color.FromArgb(
                        ClampColorElem(255 - 255 * shade),
                        ClampColorElem(255 * shade),
                        ClampColorElem(0));

                    if (r == 0 && c == width - 1)
                        image.BaseImage.SetPixel(c, r, pixel);

                    else if (r == height - 1 && c == 0)
                        image.BaseImage.SetPixel(c, r, pixel);

                    image.BaseImage.SetPixel(c, r, pixel);
                    
                }
            }
            //image.BaseImage.RotateFlip(RotateFlipType.Rotate180FlipNone);
        }

        /// <summary>
        /// this method draws a diagonal line from (100, 100) to (400, 200)
        /// </summary>
        /// <param name="image"></param>
        public static void DiagonalLine(Image image)
        {
            int r;

            for (int c = 100; c < 201; c++)
            {
                r = Math.Min(399, c * 3 - 200);
                image.BaseImage.SetPixel(r, c, Color.Yellow);
            }
        }

        /// <summary>
        /// this method draws i vertical line 2 pixels wide starting at col 100
        /// </summary>
        /// <param name="image"></param>
        public static void VerticalLine(Image image)
        {
            int c = 100;

            for (int r = 0; r < image.BaseImage.Height; r++)
            {
                image.BaseImage.SetPixel(c, r, Color.Yellow);
                image.BaseImage.SetPixel(c + 1, r, Color.Yellow);
            }
        }

        /// <summary>
        /// this method draws a horizontal line at row 100
        /// </summary>
        /// <param name="image"></param>
        public static void HorizontalLine(Image image)
        {
            int r = 100;

            for (int c = 0; c < image.BaseImage.Width; c++)
            {
                image.BaseImage.SetPixel(c, r, Color.Yellow);
            }
        }
        

        ///<summary>
        ///this class function fills the image with a vertical gradient 
        ///from blue at the top of the image to black at the bottom.
        /// </summary>
        /// <param name="image">the image to fill</param>
        public static void VerticalGradient(Image image)
        {
            for (int r = 0; r < image.BaseImage.Height; r++)
            {
                for (int c = 0; c < image.BaseImage.Width; c++)
                {
                    //image[c][r] = byte(float(c) / float(image.BaseImage.Width) * 255);
                    int shade = 255 - (int)Math.Round((float)r / (float)image.BaseImage.Height * 255);
                    Color pixel = Color.FromArgb(0, 0, shade);
                    image.BaseImage.SetPixel(c, r, pixel);
                }
            }
        }

        ///<summary>
        ///this class function fills the image with a horizontal gradient of black to white
        /// </summary>
        /// <param name="image">the image to fill</param>
        public static void HorizontalGradient(Image image)
        {
            for (int r = 0; r < image.BaseImage.Height; r++)
            {
                for (int c = 0; c < image.BaseImage.Width; c++)
                {
                    //image[c][r] = byte(float(c) / float(image.BaseImage.Width) * 255);
                    int shade = (int)Math.Round((float)c / (float)image.BaseImage.Width * 255);
                    Color pixel = Color.FromArgb(shade, shade, shade);
                    image.BaseImage.SetPixel(c, r, pixel);
                }
            }
        }


        /// <summary>
        /// this class funtion fills the image with SeaGreen
        /// </summary>
        /// <param name="image"> the image to fill</param>
        public static void FillSeaGreen(Image image)
        {
            for (int r = 0; r < image.BaseImage.Height; r++)
            {
                for (int c = 0; c < image.BaseImage.Width; c++)
                {
                    image.BaseImage.SetPixel(c, r, Color.SeaGreen);
                }
            }
        }

        /// <summary>
        /// this class function fills the base image with green
        /// </summary>
        /// <param name="image"> image to edit</param>
        public static void FillGreen(Image image)
        {
            for(int r = 0; r < image.BaseImage.Height; r++)
            {
                for(int c = 0; c < image.BaseImage.Width; c++)
                {
                    image.BaseImage.SetPixel(c, r, Color.Green);
                }
            }
        }

        /// <summary>
        /// This class function fills the base image with white.
        /// </summary>
        /// <param name="image">image to edit</param>
        public static void FillWhite(Image image)
        {
            for (int r = 0; r < image.BaseImage.Height; r++)
            {
                // Looping over the columns of the array
                for (int c = 0; c < image.BaseImage.Width ; c++)
                {
                    image.BaseImage.SetPixel(c, r, Color.White);
                }
            }

        }

        /// <summary>
        /// This class function fills the base image with black.
        /// </summary>
        /// <param name="image">image to edit</param>
        public static void FillBlack(Image image)
        {
            for (int r = 0; r < image.BaseImage.Height; r++)
            {
                // Looping over the columns of the array
                for (int c = 0; c < image.BaseImage.Width; c++)
                {
                    image.BaseImage.SetPixel(c, r, Color.Black);
                }
            }

        }

        //
        // Mouse functions----------------------------------------------------
        //

        /// <summary>
        /// Draw a red dot at the given point onthe base image
        /// </summary>
        /// <param name="image"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        public override void MousePress(Image image, int x, int y)
        {
            // We count the mouse clicks
            switch (mouseMode)
            {
                case MODE.Draw:
                    if(x< image.BaseImage.Width && y < image.BaseImage.Height)
                        image.BaseImage.SetPixel(x, y- image.Offset, Color.Red);
                    mouseMode = MODE.Move;
                    break;

            }
        }

        public override void MouseRelease()
        {
            if(mouseMode == MODE.Move)
                mouseMode = MODE.Draw;
        }

        /// <summary>
        /// Draw a red dot at the given point onthe base image
        /// </summary>
        /// <param name="image"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        public override void MouseMove(Image image, int x, int y)
        {

            switch (mouseMode)
            {
                case MODE.Move:
                    if (x < image.BaseImage.Width && y < image.BaseImage.Height)
                        image.BaseImage.SetPixel(x, y- image.Offset, Color.Red);
                    break;
            }

        }
    }
}
