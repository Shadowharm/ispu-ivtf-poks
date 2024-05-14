namespace StarDestroyer
{
    partial class StartMenu
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(StartMenu));
            this.Start = new System.Windows.Forms.Button();
            this.Title = new System.Windows.Forms.Label();
            this.Records = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // Start
            // 
            this.Start.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Start.Location = new System.Drawing.Point(367, 217);
            this.Start.Name = "Start";
            this.Start.Size = new System.Drawing.Size(177, 43);
            this.Start.TabIndex = 0;
            this.Start.Text = "Играть";
            this.Start.UseVisualStyleBackColor = true;
            this.Start.Click += new System.EventHandler(this.Start_Click);
            // 
            // Title
            // 
            this.Title.AutoSize = true;
            this.Title.BackColor = System.Drawing.Color.Transparent;
            this.Title.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Title.ForeColor = System.Drawing.Color.White;
            this.Title.Location = new System.Drawing.Point(361, 84);
            this.Title.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.Title.Name = "Title";
            this.Title.Size = new System.Drawing.Size(183, 31);
            this.Title.TabIndex = 2;
            this.Title.Text = "StarDestroyer";
            this.Title.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Records
            // 
            this.Records.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Records.Location = new System.Drawing.Point(367, 276);
            this.Records.Name = "Records";
            this.Records.Size = new System.Drawing.Size(177, 43);
            this.Records.TabIndex = 3;
            this.Records.Text = "Рекорды";
            this.Records.UseVisualStyleBackColor = true;
            this.Records.Click += new System.EventHandler(this.Records_Click);
            // 
            // StartMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::StarDestroyer.Properties.Resources.background;
            this.ClientSize = new System.Drawing.Size(883, 489);
            this.Controls.Add(this.Records);
            this.Controls.Add(this.Title);
            this.Controls.Add(this.Start);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "StartMenu";
            this.Text = "StartMenu";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Start;
        private System.Windows.Forms.Label Title;
        private System.Windows.Forms.Button Records;
    }
}