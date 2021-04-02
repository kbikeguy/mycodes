namespace ImageProcess
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.openTestMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.openMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.closeMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.saveMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.exitMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.generateToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.fillWhiteMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.fillGreenOption = new System.Windows.Forms.ToolStripMenuItem();
            this.FillSeaGreenMenuOption = new System.Windows.Forms.ToolStripMenuItem();
            this.HorizontalLine = new System.Windows.Forms.ToolStripMenuItem();
            this.VerticalLine = new System.Windows.Forms.ToolStripMenuItem();
            this.DiagonalLine = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.drawMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.mouseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.copyMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.negativeMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.dimMenuOption = new System.Windows.Forms.ToolStripMenuItem();
            this.TintMenuOption = new System.Windows.Forms.ToolStripMenuItem();
            this.LowpassFilter = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.MonochromeFilter = new System.Windows.Forms.ToolStripSeparator();
            this.thresholdMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.warpMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.warpBilinearMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.horizontalGradient = new System.Windows.Forms.ToolStripMenuItem();
            this.verticalBlueGradient = new System.Windows.Forms.ToolStripMenuItem();
            this.diagonalGradient = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.filterToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MedianMenuOption = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.generateToolStripMenuItem,
            this.mouseToolStripMenuItem,
            this.horizontalGradient,
            this.verticalBlueGradient,
            this.diagonalGradient,
            this.filterToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newMenu,
            this.openTestMenu,
            this.openMenu,
            this.closeMenu,
            this.saveMenu,
            this.exitMenu});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // newMenu
            // 
            this.newMenu.Name = "newMenu";
            this.newMenu.Size = new System.Drawing.Size(126, 22);
            this.newMenu.Text = "New";
            this.newMenu.Click += new System.EventHandler(this.newMenu_Click);
            // 
            // openTestMenu
            // 
            this.openTestMenu.Name = "openTestMenu";
            this.openTestMenu.Size = new System.Drawing.Size(126, 22);
            this.openTestMenu.Text = "Open Test";
            this.openTestMenu.Click += new System.EventHandler(this.openTestMenu_Click);
            // 
            // openMenu
            // 
            this.openMenu.Name = "openMenu";
            this.openMenu.Size = new System.Drawing.Size(126, 22);
            this.openMenu.Text = "Open";
            this.openMenu.Click += new System.EventHandler(this.openMenu_Click);
            // 
            // closeMenu
            // 
            this.closeMenu.Name = "closeMenu";
            this.closeMenu.Size = new System.Drawing.Size(126, 22);
            this.closeMenu.Text = "Close";
            this.closeMenu.Click += new System.EventHandler(this.closeMenu_Click);
            // 
            // saveMenu
            // 
            this.saveMenu.Name = "saveMenu";
            this.saveMenu.Size = new System.Drawing.Size(126, 22);
            this.saveMenu.Text = "Save";
            this.saveMenu.Click += new System.EventHandler(this.saveMenu_Click);
            // 
            // exitMenu
            // 
            this.exitMenu.Name = "exitMenu";
            this.exitMenu.Size = new System.Drawing.Size(126, 22);
            this.exitMenu.Text = "Exit";
            this.exitMenu.Click += new System.EventHandler(this.exitMenu_Click);
            // 
            // generateToolStripMenuItem
            // 
            this.generateToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fillWhiteMenu,
            this.fillGreenOption,
            this.FillSeaGreenMenuOption,
            this.HorizontalLine,
            this.VerticalLine,
            this.DiagonalLine,
            this.toolStripSeparator2,
            this.drawMenu});
            this.generateToolStripMenuItem.Name = "generateToolStripMenuItem";
            this.generateToolStripMenuItem.Size = new System.Drawing.Size(66, 20);
            this.generateToolStripMenuItem.Text = "Generate";
            // 
            // fillWhiteMenu
            // 
            this.fillWhiteMenu.Name = "fillWhiteMenu";
            this.fillWhiteMenu.Size = new System.Drawing.Size(154, 22);
            this.fillWhiteMenu.Text = "Fill White";
            this.fillWhiteMenu.Click += new System.EventHandler(this.fillWhiteMenu_Click);
            // 
            // fillGreenOption
            // 
            this.fillGreenOption.Name = "fillGreenOption";
            this.fillGreenOption.Size = new System.Drawing.Size(154, 22);
            this.fillGreenOption.Text = "Fill Green";
            this.fillGreenOption.Click += new System.EventHandler(this.FillGreenOption_Click);
            // 
            // FillSeaGreenMenuOption
            // 
            this.FillSeaGreenMenuOption.Name = "FillSeaGreenMenuOption";
            this.FillSeaGreenMenuOption.Size = new System.Drawing.Size(154, 22);
            this.FillSeaGreenMenuOption.Text = "Fill SeaGreen";
            this.FillSeaGreenMenuOption.Click += new System.EventHandler(this.FillSeaGreenMenuOption_Click);
            // 
            // HorizontalLine
            // 
            this.HorizontalLine.Name = "HorizontalLine";
            this.HorizontalLine.Size = new System.Drawing.Size(154, 22);
            this.HorizontalLine.Text = "Horizontal Line";
            this.HorizontalLine.Click += new System.EventHandler(this.HorizontalLine_Click);
            // 
            // VerticalLine
            // 
            this.VerticalLine.Name = "VerticalLine";
            this.VerticalLine.Size = new System.Drawing.Size(154, 22);
            this.VerticalLine.Text = "Vertical Line";
            this.VerticalLine.Click += new System.EventHandler(this.VerticalLine_Click);
            // 
            // DiagonalLine
            // 
            this.DiagonalLine.Name = "DiagonalLine";
            this.DiagonalLine.Size = new System.Drawing.Size(154, 22);
            this.DiagonalLine.Text = "Diagonal Line";
            this.DiagonalLine.Click += new System.EventHandler(this.DiagonalLine_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(151, 6);
            // 
            // drawMenu
            // 
            this.drawMenu.Name = "drawMenu";
            this.drawMenu.Size = new System.Drawing.Size(154, 22);
            this.drawMenu.Text = "Draw";
            this.drawMenu.Click += new System.EventHandler(this.drawMenu_Click);
            // 
            // mouseToolStripMenuItem
            // 
            this.mouseToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.copyMenu,
            this.negativeMenu,
            this.dimMenuOption,
            this.TintMenuOption,
            this.LowpassFilter,
            this.toolStripMenuItem1,
            this.MonochromeFilter,
            this.thresholdMenu,
            this.warpMenu,
            this.warpBilinearMenu});
            this.mouseToolStripMenuItem.Name = "mouseToolStripMenuItem";
            this.mouseToolStripMenuItem.Size = new System.Drawing.Size(59, 20);
            this.mouseToolStripMenuItem.Text = "Process";
            // 
            // copyMenu
            // 
            this.copyMenu.Name = "copyMenu";
            this.copyMenu.Size = new System.Drawing.Size(180, 22);
            this.copyMenu.Text = "Copy";
            this.copyMenu.Click += new System.EventHandler(this.copyMenu_Click);
            // 
            // negativeMenu
            // 
            this.negativeMenu.Name = "negativeMenu";
            this.negativeMenu.Size = new System.Drawing.Size(180, 22);
            this.negativeMenu.Text = "Negative";
            this.negativeMenu.Click += new System.EventHandler(this.negativeMenu_Click);
            // 
            // dimMenuOption
            // 
            this.dimMenuOption.Name = "dimMenuOption";
            this.dimMenuOption.Size = new System.Drawing.Size(180, 22);
            this.dimMenuOption.Text = "Dim";
            this.dimMenuOption.Click += new System.EventHandler(this.DimMenuOption_Click);
            // 
            // TintMenuOption
            // 
            this.TintMenuOption.Name = "TintMenuOption";
            this.TintMenuOption.Size = new System.Drawing.Size(180, 22);
            this.TintMenuOption.Text = "Tint";
            this.TintMenuOption.Click += new System.EventHandler(this.TintMenuOption_Click);
            // 
            // LowpassFilter
            // 
            this.LowpassFilter.Name = "LowpassFilter";
            this.LowpassFilter.Size = new System.Drawing.Size(180, 22);
            this.LowpassFilter.Text = "Lowpass Filter";
            this.LowpassFilter.Click += new System.EventHandler(this.LowpassFilter_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(180, 22);
            this.toolStripMenuItem1.Text = "Monochrome";
            this.toolStripMenuItem1.Click += new System.EventHandler(this.MonochromeFilter_Click);
            // 
            // MonochromeFilter
            // 
            this.MonochromeFilter.Name = "MonochromeFilter";
            this.MonochromeFilter.Size = new System.Drawing.Size(177, 6);
            // 
            // thresholdMenu
            // 
            this.thresholdMenu.Name = "thresholdMenu";
            this.thresholdMenu.Size = new System.Drawing.Size(180, 22);
            this.thresholdMenu.Text = "Threshold";
            this.thresholdMenu.Click += new System.EventHandler(this.thresholdMenu_Click);
            // 
            // warpMenu
            // 
            this.warpMenu.Name = "warpMenu";
            this.warpMenu.Size = new System.Drawing.Size(180, 22);
            this.warpMenu.Text = "Warp Nearest";
            this.warpMenu.Click += new System.EventHandler(this.warpMenu_Click);
            // 
            // warpBilinearMenu
            // 
            this.warpBilinearMenu.Name = "warpBilinearMenu";
            this.warpBilinearMenu.Size = new System.Drawing.Size(180, 22);
            this.warpBilinearMenu.Text = "Warp Bilinear";
            this.warpBilinearMenu.Click += new System.EventHandler(this.warpBilinearMenu_Click);
            // 
            // horizontalGradient
            // 
            this.horizontalGradient.Name = "horizontalGradient";
            this.horizontalGradient.Size = new System.Drawing.Size(122, 20);
            this.horizontalGradient.Text = "Horizontal Gradient";
            this.horizontalGradient.Click += new System.EventHandler(this.horizontalGradient_Click);
            // 
            // verticalBlueGradient
            // 
            this.verticalBlueGradient.Name = "verticalBlueGradient";
            this.verticalBlueGradient.Size = new System.Drawing.Size(131, 20);
            this.verticalBlueGradient.Text = "Vertical Blue Gradient";
            this.verticalBlueGradient.Click += new System.EventHandler(this.verticalBlueGradient_Click);
            // 
            // diagonalGradient
            // 
            this.diagonalGradient.Name = "diagonalGradient";
            this.diagonalGradient.Size = new System.Drawing.Size(114, 20);
            this.diagonalGradient.Text = "Diagonal Gradient";
            this.diagonalGradient.Click += new System.EventHandler(this.DiagonalGradient_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.Filter = "JPEG Files (*.jpg)|*.jpg|GIF Files (*.gif)|*.gif|PNG Files (*.png)|*.png|BMP File" +
    "s (*.bmp)| *p.bmp|All files (*.*)|*.*";
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.Filter = "JPEG Files (*.jpg)|*.jpg|GIF Files (*.gif)|*.gif|PNG Files (*.png)|*.png|BMP File" +
    "s (*.bmp)| *.bmp";
            // 
            // filterToolStripMenuItem
            // 
            this.filterToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MedianMenuOption});
            this.filterToolStripMenuItem.Name = "filterToolStripMenuItem";
            this.filterToolStripMenuItem.Size = new System.Drawing.Size(45, 20);
            this.filterToolStripMenuItem.Text = "Filter";
            // 
            // MedianMenuOption
            // 
            this.MedianMenuOption.Name = "MedianMenuOption";
            this.MedianMenuOption.Size = new System.Drawing.Size(180, 22);
            this.MedianMenuOption.Text = "Median";
            this.MedianMenuOption.Click += new System.EventHandler(this.MedianMenuOption_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "Image Process: Campbell Riley";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newMenu;
        private System.Windows.Forms.ToolStripMenuItem openMenu;
        private System.Windows.Forms.ToolStripMenuItem closeMenu;
        private System.Windows.Forms.ToolStripMenuItem saveMenu;
        private System.Windows.Forms.ToolStripMenuItem exitMenu;
        private System.Windows.Forms.ToolStripMenuItem generateToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mouseToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem copyMenu;
        private System.Windows.Forms.ToolStripMenuItem fillWhiteMenu;
        private System.Windows.Forms.ToolStripMenuItem openTestMenu;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.ToolStripMenuItem negativeMenu;
        private System.Windows.Forms.ToolStripMenuItem thresholdMenu;
        private System.Windows.Forms.ToolStripMenuItem warpMenu;
        private System.Windows.Forms.ToolStripMenuItem drawMenu;
        private System.Windows.Forms.ToolStripMenuItem warpBilinearMenu;
        private System.Windows.Forms.ToolStripSeparator MonochromeFilter;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem fillGreenOption;
        private System.Windows.Forms.ToolStripMenuItem dimMenuOption;
        private System.Windows.Forms.ToolStripMenuItem TintMenuOption;
        private System.Windows.Forms.ToolStripMenuItem LowpassFilter;
        private System.Windows.Forms.ToolStripMenuItem FillSeaGreenMenuOption;
        private System.Windows.Forms.ToolStripMenuItem horizontalGradient;
        private System.Windows.Forms.ToolStripMenuItem verticalBlueGradient;
        private System.Windows.Forms.ToolStripMenuItem diagonalGradient;
        private System.Windows.Forms.ToolStripMenuItem HorizontalLine;
        private System.Windows.Forms.ToolStripMenuItem VerticalLine;
        private System.Windows.Forms.ToolStripMenuItem DiagonalLine;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem filterToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem MedianMenuOption;
    }
}

