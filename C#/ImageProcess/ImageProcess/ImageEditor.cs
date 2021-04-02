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
    
    public class ImageEditor
    {
        public enum MODE
        {
            None, Draw, Move, Threshold, Warp, WarpNearest
        }

        protected MODE mouseMode = MODE.None;

        public MODE MouseMode { get => mouseMode;}

        /// <summary>
        /// mdoe for processing
        /// </summary>
        /// <param name="m"></param>
        public virtual void SetMode(MODE m) { }
        public virtual void MouseMove(Image image1, int x, int y) { }
        public virtual void MousePress(Image image1, int x, int y) { }
        public virtual void MouseRelease(){  }
        
    }
}
