namespace AudioProcess
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
            this.openItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openDefaultItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveItem = new System.Windows.Forms.ToolStripMenuItem();
            this.closeItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitItem = new System.Windows.Forms.ToolStripMenuItem();
            this.listenToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.playItem = new System.Windows.Forms.ToolStripMenuItem();
            this.stopItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pauseItem = new System.Windows.Forms.ToolStripMenuItem();
            this.generateToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.sineItem = new System.Windows.Forms.ToolStripMenuItem();
            this.sineParamsItem = new System.Windows.Forms.ToolStripMenuItem();
            this.SineWaves = new System.Windows.Forms.ToolStripMenuItem();
            this.Sine234 = new System.Windows.Forms.ToolStripMenuItem();
            this.Sine357 = new System.Windows.Forms.ToolStripMenuItem();
            this.AllHarmonics = new System.Windows.Forms.ToolStripMenuItem();
            this.AllOddHarmonics = new System.Windows.Forms.ToolStripMenuItem();
            this.processToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.volumeAdjustItem = new System.Windows.Forms.ToolStripMenuItem();
            this.OnRamp = new System.Windows.Forms.ToolStripMenuItem();
            this.renderFormatToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.darkModeItem = new System.Windows.Forms.ToolStripMenuItem();
            this.lightModeItem = new System.Windows.Forms.ToolStripMenuItem();
            this.hScrollBar = new System.Windows.Forms.HScrollBar();
            this.vScrollBar = new System.Windows.Forms.VScrollBar();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.RampInOut = new System.Windows.Forms.ToolStripMenuItem();
            this.Tremolo = new System.Windows.Forms.ToolStripMenuItem();
            this.Slow = new System.Windows.Forms.ToolStripMenuItem();
            this.Fast = new System.Windows.Forms.ToolStripMenuItem();
            this.Backwards = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.listenToolStripMenuItem,
            this.generateToolStripMenuItem,
            this.processToolStripMenuItem,
            this.renderFormatToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newMenu,
            this.openItem,
            this.openDefaultItem,
            this.saveAsItem,
            this.saveItem,
            this.closeItem,
            this.exitItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // newMenu
            // 
            this.newMenu.Name = "newMenu";
            this.newMenu.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.A)));
            this.newMenu.Size = new System.Drawing.Size(146, 22);
            this.newMenu.Text = "New";
            this.newMenu.Click += new System.EventHandler(this.newMenu_Click);
            // 
            // openItem
            // 
            this.openItem.Name = "openItem";
            this.openItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.openItem.Size = new System.Drawing.Size(146, 22);
            this.openItem.Text = "Open";
            this.openItem.Click += new System.EventHandler(this.openItem_Click);
            // 
            // openDefaultItem
            // 
            this.openDefaultItem.Name = "openDefaultItem";
            this.openDefaultItem.Size = new System.Drawing.Size(146, 22);
            this.openDefaultItem.Text = "Open Default";
            this.openDefaultItem.Click += new System.EventHandler(this.openDefaultItem_Click);
            // 
            // saveAsItem
            // 
            this.saveAsItem.Name = "saveAsItem";
            this.saveAsItem.Size = new System.Drawing.Size(146, 22);
            this.saveAsItem.Text = "Save As...";
            this.saveAsItem.Click += new System.EventHandler(this.saveAsItem_Click);
            // 
            // saveItem
            // 
            this.saveItem.Name = "saveItem";
            this.saveItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.saveItem.Size = new System.Drawing.Size(146, 22);
            this.saveItem.Text = "Save";
            this.saveItem.Click += new System.EventHandler(this.saveItem_Click);
            // 
            // closeItem
            // 
            this.closeItem.Name = "closeItem";
            this.closeItem.Size = new System.Drawing.Size(146, 22);
            this.closeItem.Text = "Close";
            this.closeItem.Click += new System.EventHandler(this.closeItem_Click);
            // 
            // exitItem
            // 
            this.exitItem.Name = "exitItem";
            this.exitItem.Size = new System.Drawing.Size(146, 22);
            this.exitItem.Text = "Exit";
            this.exitItem.Click += new System.EventHandler(this.exitItem_Click);
            // 
            // listenToolStripMenuItem
            // 
            this.listenToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.playItem,
            this.stopItem,
            this.pauseItem});
            this.listenToolStripMenuItem.Name = "listenToolStripMenuItem";
            this.listenToolStripMenuItem.Size = new System.Drawing.Size(50, 20);
            this.listenToolStripMenuItem.Text = "Listen";
            // 
            // playItem
            // 
            this.playItem.Name = "playItem";
            this.playItem.Size = new System.Drawing.Size(105, 22);
            this.playItem.Text = "Play";
            this.playItem.Click += new System.EventHandler(this.playItem_Click);
            // 
            // stopItem
            // 
            this.stopItem.Name = "stopItem";
            this.stopItem.Size = new System.Drawing.Size(105, 22);
            this.stopItem.Text = "Stop";
            this.stopItem.Click += new System.EventHandler(this.stopItem_Click);
            // 
            // pauseItem
            // 
            this.pauseItem.Name = "pauseItem";
            this.pauseItem.Size = new System.Drawing.Size(105, 22);
            this.pauseItem.Text = "Pause";
            this.pauseItem.Click += new System.EventHandler(this.pauseItem_Click);
            // 
            // generateToolStripMenuItem
            // 
            this.generateToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.sineItem,
            this.sineParamsItem,
            this.SineWaves,
            this.Sine234,
            this.Sine357,
            this.AllHarmonics,
            this.AllOddHarmonics});
            this.generateToolStripMenuItem.Name = "generateToolStripMenuItem";
            this.generateToolStripMenuItem.Size = new System.Drawing.Size(66, 20);
            this.generateToolStripMenuItem.Text = "Generate";
            // 
            // sineItem
            // 
            this.sineItem.Name = "sineItem";
            this.sineItem.Size = new System.Drawing.Size(180, 22);
            this.sineItem.Text = "Make Sine";
            this.sineItem.Click += new System.EventHandler(this.sineItem_Click);
            // 
            // sineParamsItem
            // 
            this.sineParamsItem.Name = "sineParamsItem";
            this.sineParamsItem.Size = new System.Drawing.Size(180, 22);
            this.sineParamsItem.Text = "Sine Parameters";
            this.sineParamsItem.Click += new System.EventHandler(this.sineParamsItem_Click);
            // 
            // SineWaves
            // 
            this.SineWaves.Name = "SineWaves";
            this.SineWaves.Size = new System.Drawing.Size(180, 22);
            this.SineWaves.Text = "Sine Waves";
            this.SineWaves.Click += new System.EventHandler(this.SineWaves_Click);
            // 
            // Sine234
            // 
            this.Sine234.Name = "Sine234";
            this.Sine234.Size = new System.Drawing.Size(180, 22);
            this.Sine234.Text = "234";
            this.Sine234.Click += new System.EventHandler(this.Sine234_Click);
            // 
            // Sine357
            // 
            this.Sine357.Name = "Sine357";
            this.Sine357.Size = new System.Drawing.Size(180, 22);
            this.Sine357.Text = "357";
            this.Sine357.Click += new System.EventHandler(this.Sine357_Click);
            // 
            // AllHarmonics
            // 
            this.AllHarmonics.Name = "AllHarmonics";
            this.AllHarmonics.Size = new System.Drawing.Size(180, 22);
            this.AllHarmonics.Text = "All Harmonics";
            this.AllHarmonics.Click += new System.EventHandler(this.AllHarmonics_Click);
            // 
            // AllOddHarmonics
            // 
            this.AllOddHarmonics.Name = "AllOddHarmonics";
            this.AllOddHarmonics.Size = new System.Drawing.Size(180, 22);
            this.AllOddHarmonics.Text = "All Odd Harmonics";
            this.AllOddHarmonics.Click += new System.EventHandler(this.AllOddHarmonics_Click);
            // 
            // processToolStripMenuItem
            // 
            this.processToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.volumeAdjustItem,
            this.OnRamp,
            this.RampInOut,
            this.Tremolo,
            this.Slow,
            this.Fast,
            this.Backwards});
            this.processToolStripMenuItem.Name = "processToolStripMenuItem";
            this.processToolStripMenuItem.Size = new System.Drawing.Size(59, 20);
            this.processToolStripMenuItem.Text = "Process";
            // 
            // volumeAdjustItem
            // 
            this.volumeAdjustItem.Name = "volumeAdjustItem";
            this.volumeAdjustItem.Size = new System.Drawing.Size(180, 22);
            this.volumeAdjustItem.Text = "Volume Adjust";
            this.volumeAdjustItem.Click += new System.EventHandler(this.volumeAdjustItem_Click);
            // 
            // OnRamp
            // 
            this.OnRamp.Name = "OnRamp";
            this.OnRamp.Size = new System.Drawing.Size(180, 22);
            this.OnRamp.Text = "Ramp";
            this.OnRamp.Click += new System.EventHandler(this.OnRamp_Click);
            // 
            // renderFormatToolStripMenuItem
            // 
            this.renderFormatToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.darkModeItem,
            this.lightModeItem});
            this.renderFormatToolStripMenuItem.Name = "renderFormatToolStripMenuItem";
            this.renderFormatToolStripMenuItem.Size = new System.Drawing.Size(97, 20);
            this.renderFormatToolStripMenuItem.Text = "Render Format";
            // 
            // darkModeItem
            // 
            this.darkModeItem.Name = "darkModeItem";
            this.darkModeItem.Size = new System.Drawing.Size(135, 22);
            this.darkModeItem.Text = "Dark Mode";
            this.darkModeItem.Click += new System.EventHandler(this.darkModeItem_Click);
            // 
            // lightModeItem
            // 
            this.lightModeItem.Name = "lightModeItem";
            this.lightModeItem.Size = new System.Drawing.Size(135, 22);
            this.lightModeItem.Text = "Light Mode";
            this.lightModeItem.Click += new System.EventHandler(this.lightModeItem_Click);
            // 
            // hScrollBar
            // 
            this.hScrollBar.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.hScrollBar.Location = new System.Drawing.Point(0, 433);
            this.hScrollBar.Maximum = 1000;
            this.hScrollBar.Name = "hScrollBar";
            this.hScrollBar.Size = new System.Drawing.Size(800, 17);
            this.hScrollBar.TabIndex = 1;
            this.hScrollBar.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScrollBar1_Scroll);
            // 
            // vScrollBar
            // 
            this.vScrollBar.Dock = System.Windows.Forms.DockStyle.Left;
            this.vScrollBar.Location = new System.Drawing.Point(0, 24);
            this.vScrollBar.Maximum = 1000;
            this.vScrollBar.Minimum = 1;
            this.vScrollBar.Name = "vScrollBar";
            this.vScrollBar.Size = new System.Drawing.Size(17, 409);
            this.vScrollBar.TabIndex = 2;
            this.vScrollBar.Value = 5;
            this.vScrollBar.Scroll += new System.Windows.Forms.ScrollEventHandler(this.vScrollBar1_Scroll);
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "openFileDialog";
            this.openFileDialog.Filter = "Wave Files (*.wav)|*.wav| MP3 (*.mp3)|*.mp3|All Files (*.*)|*.*";
            // 
            // saveFileDialog
            // 
            this.saveFileDialog.Filter = "Wave Files (*.wav)|*.wav| MP3 (*.mp3)|*.mp3";
            // 
            // RampInOut
            // 
            this.RampInOut.Name = "RampInOut";
            this.RampInOut.Size = new System.Drawing.Size(180, 22);
            this.RampInOut.Text = "Ramp In/Out";
            this.RampInOut.Click += new System.EventHandler(this.RampInOut_Click);
            // 
            // Tremolo
            // 
            this.Tremolo.Name = "Tremolo";
            this.Tremolo.Size = new System.Drawing.Size(180, 22);
            this.Tremolo.Text = "Tremolo ";
            this.Tremolo.Click += new System.EventHandler(this.Tremolo_Click);
            // 
            // Slow
            // 
            this.Slow.Name = "Slow";
            this.Slow.Size = new System.Drawing.Size(180, 22);
            this.Slow.Text = "Slow";
            this.Slow.Click += new System.EventHandler(this.Slow_Click);
            // 
            // Fast
            // 
            this.Fast.Name = "Fast";
            this.Fast.Size = new System.Drawing.Size(180, 22);
            this.Fast.Text = "Fast";
            this.Fast.Click += new System.EventHandler(this.Fast_Click);
            // 
            // Backwards
            // 
            this.Backwards.Name = "Backwards";
            this.Backwards.Size = new System.Drawing.Size(180, 22);
            this.Backwards.Text = "Backwards";
            this.Backwards.Click += new System.EventHandler(this.Backwards_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.vScrollBar);
            this.Controls.Add(this.hScrollBar);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "Tutorial 3 Campbell Riley";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newMenu;
        private System.Windows.Forms.HScrollBar hScrollBar;
        private System.Windows.Forms.VScrollBar vScrollBar;
        private System.Windows.Forms.ToolStripMenuItem openItem;
        private System.Windows.Forms.ToolStripMenuItem closeItem;
        private System.Windows.Forms.ToolStripMenuItem exitItem;
        private System.Windows.Forms.ToolStripMenuItem openDefaultItem;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.ToolStripMenuItem saveItem;
        private System.Windows.Forms.SaveFileDialog saveFileDialog;
        private System.Windows.Forms.ToolStripMenuItem listenToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem playItem;
        private System.Windows.Forms.ToolStripMenuItem stopItem;
        private System.Windows.Forms.ToolStripMenuItem pauseItem;
        private System.Windows.Forms.ToolStripMenuItem generateToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem sineItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsItem;
        private System.Windows.Forms.ToolStripMenuItem renderFormatToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem darkModeItem;
        private System.Windows.Forms.ToolStripMenuItem lightModeItem;
        private System.Windows.Forms.ToolStripMenuItem sineParamsItem;
        private System.Windows.Forms.ToolStripMenuItem processToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem volumeAdjustItem;
        private System.Windows.Forms.ToolStripMenuItem SineWaves;
        private System.Windows.Forms.ToolStripMenuItem Sine234;
        private System.Windows.Forms.ToolStripMenuItem Sine357;
        private System.Windows.Forms.ToolStripMenuItem AllHarmonics;
        private System.Windows.Forms.ToolStripMenuItem AllOddHarmonics;
        private System.Windows.Forms.ToolStripMenuItem OnRamp;
        private System.Windows.Forms.ToolStripMenuItem RampInOut;
        private System.Windows.Forms.ToolStripMenuItem Tremolo;
        private System.Windows.Forms.ToolStripMenuItem Slow;
        private System.Windows.Forms.ToolStripMenuItem Fast;
        private System.Windows.Forms.ToolStripMenuItem Backwards;
    }
}

