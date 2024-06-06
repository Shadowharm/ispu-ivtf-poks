namespace StarDestroyer
{
    partial class MainGame
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainGame));
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.AmmoCount = new System.Windows.Forms.Label();
            this.ScoreLabel = new System.Windows.Forms.Label();
            this.Pause = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // timer
            // 
            this.timer.Enabled = true;
            this.timer.Interval = 30;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // AmmoCount
            // 
            this.AmmoCount.AutoSize = true;
            this.AmmoCount.BackColor = System.Drawing.Color.Transparent;
            this.AmmoCount.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.AmmoCount.ForeColor = System.Drawing.Color.White;
            this.AmmoCount.Location = new System.Drawing.Point(17, 17);
            this.AmmoCount.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.AmmoCount.Name = "AmmoCount";
            this.AmmoCount.Size = new System.Drawing.Size(85, 20);
            this.AmmoCount.TabIndex = 1;
            this.AmmoCount.Text = "Патроны: ";
            // 
            // ScoreLabel
            // 
            this.ScoreLabel.AutoSize = true;
            this.ScoreLabel.BackColor = System.Drawing.Color.Transparent;
            this.ScoreLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ScoreLabel.ForeColor = System.Drawing.Color.White;
            this.ScoreLabel.Location = new System.Drawing.Point(17, 37);
            this.ScoreLabel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.ScoreLabel.Name = "ScoreLabel";
            this.ScoreLabel.Size = new System.Drawing.Size(64, 20);
            this.ScoreLabel.TabIndex = 2;
            this.ScoreLabel.Text = "Счет: 0";
            // 
            // Pause
            // 
            this.Pause.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.Pause.Location = new System.Drawing.Point(1021, 12);
            this.Pause.Name = "Pause";
            this.Pause.Size = new System.Drawing.Size(40, 40);
            this.Pause.TabIndex = 1;
            this.Pause.TabStop = false;
            this.Pause.Text = "❚❚";
            this.Pause.UseVisualStyleBackColor = true;
            this.Pause.Click += new System.EventHandler(this.Pause_Click);
            // 
            // MainGame
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.BackgroundImage = global::StarDestroyer.Properties.Resources.background;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(1071, 607);
            this.Controls.Add(this.Pause);
            this.Controls.Add(this.ScoreLabel);
            this.Controls.Add(this.AmmoCount);
            this.DoubleBuffered = true;
            this.ForeColor = System.Drawing.SystemColors.ControlText;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainGame";
            this.Text = "StarDestroyer";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainGame_FormClosed);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.OnPaint);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.OnKeyDown);
            this.Resize += new System.EventHandler(this.OnResize);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.Label AmmoCount;
        private System.Windows.Forms.Label ScoreLabel;
        private System.Windows.Forms.Button Pause;
    }
}

