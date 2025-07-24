namespace wsbToolSettings
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(16, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(283, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = "Windows Style Builder Extension Help Menu";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(6, 54);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(262, 48);
            this.button1.TabIndex = 1;
            this.button1.Text = "Open the theme backup directory";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.Button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(6, 107);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(262, 39);
            this.button2.TabIndex = 2;
            this.button2.Text = "Open the system theme directory";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.Button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(6, 151);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(262, 32);
            this.button3.TabIndex = 3;
            this.button3.Text = "Open the current theme directory";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.Button3_Click);
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(272, 54);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(399, 48);
            this.label2.TabIndex = 4;
            this.label2.Text = "Each time you click the [Test] button to test the theme, wsb will generate a temp" +
    "orary file in the backup directory. If wsb crashes accidentally, you can find th" +
    "e theme tested in this directory.";
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(272, 107);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(281, 35);
            this.label3.TabIndex = 5;
            this.label3.Text = "Open the system theme directory \r\nC:/W/R/T";
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(272, 151);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(281, 34);
            this.label4.TabIndex = 6;
            this.label4.Text = "Open the directory where the current theme is located.";
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(272, 189);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(396, 76);
            this.label5.TabIndex = 8;
            this.label5.Text = resources.GetString("label5.Text");
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(6, 189);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(262, 76);
            this.button4.TabIndex = 7;
            this.button4.Text = "Disable MWsbToolLib";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.Button4_Click);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(6, 288);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(262, 44);
            this.button5.TabIndex = 9;
            this.button5.Text = "View Credits";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // label6
            // 
            this.label6.Location = new System.Drawing.Point(275, 288);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(396, 44);
            this.label6.TabIndex = 10;
            this.label6.Text = "View Credits";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(670, 353);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label1);
            this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Windows Style Builder Help Menu";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Label label6;
    }
}

