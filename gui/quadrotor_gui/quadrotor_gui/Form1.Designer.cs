namespace quadrotor_gui
{
    partial class QuadMainWindow
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
            this.runThread = false;

            comm?.Dispose();
            readThread?.Join();

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
            this.arm_btn = new System.Windows.Forms.Button();
            this.com_combo_box = new System.Windows.Forms.ComboBox();
            this.com_port_label = new System.Windows.Forms.Label();
            this.run_btn = new System.Windows.Forms.Button();
            this.stop_btn = new System.Windows.Forms.Button();
            this.talk_btn = new System.Windows.Forms.Button();
            this.last_receved_data_label = new System.Windows.Forms.Label();
            this.lrdll = new System.Windows.Forms.Label();
            this.is_conn_label = new System.Windows.Forms.Label();
            this.disconnect_btn = new System.Windows.Forms.Button();
            this.ax_label = new System.Windows.Forms.Label();
            this.ay_label = new System.Windows.Forms.Label();
            this.accel_z_label = new System.Windows.Forms.Label();
            this.ax_out = new System.Windows.Forms.Label();
            this.ay_out = new System.Windows.Forms.Label();
            this.az_out = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // arm_btn
            // 
            this.arm_btn.Location = new System.Drawing.Point(12, 12);
            this.arm_btn.Name = "arm_btn";
            this.arm_btn.Size = new System.Drawing.Size(229, 123);
            this.arm_btn.TabIndex = 0;
            this.arm_btn.Text = "ARM";
            this.arm_btn.UseVisualStyleBackColor = true;
            this.arm_btn.Click += new System.EventHandler(this.arm_btn_Click);
            // 
            // com_combo_box
            // 
            this.com_combo_box.FormattingEnabled = true;
            this.com_combo_box.Location = new System.Drawing.Point(583, 12);
            this.com_combo_box.Name = "com_combo_box";
            this.com_combo_box.Size = new System.Drawing.Size(225, 33);
            this.com_combo_box.TabIndex = 1;
            this.com_combo_box.SelectedIndexChanged += new System.EventHandler(this.com_combo_box_SelectedIndexChanged);
            // 
            // com_port_label
            // 
            this.com_port_label.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.com_port_label.Location = new System.Drawing.Point(427, 12);
            this.com_port_label.Name = "com_port_label";
            this.com_port_label.Size = new System.Drawing.Size(150, 33);
            this.com_port_label.TabIndex = 2;
            this.com_port_label.Text = "COM Port:";
            this.com_port_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.com_port_label.Click += new System.EventHandler(this.com_port_label_Click);
            // 
            // run_btn
            // 
            this.run_btn.Location = new System.Drawing.Point(12, 153);
            this.run_btn.Name = "run_btn";
            this.run_btn.Size = new System.Drawing.Size(229, 123);
            this.run_btn.TabIndex = 3;
            this.run_btn.Text = "RUN";
            this.run_btn.UseVisualStyleBackColor = true;
            this.run_btn.Click += new System.EventHandler(this.run_btn_Click);
            // 
            // stop_btn
            // 
            this.stop_btn.Location = new System.Drawing.Point(12, 595);
            this.stop_btn.Name = "stop_btn";
            this.stop_btn.Size = new System.Drawing.Size(796, 113);
            this.stop_btn.TabIndex = 4;
            this.stop_btn.Text = "STOP";
            this.stop_btn.UseVisualStyleBackColor = true;
            this.stop_btn.Click += new System.EventHandler(this.stop_btn_Click);
            // 
            // talk_btn
            // 
            this.talk_btn.Location = new System.Drawing.Point(583, 52);
            this.talk_btn.Name = "talk_btn";
            this.talk_btn.Size = new System.Drawing.Size(224, 43);
            this.talk_btn.TabIndex = 5;
            this.talk_btn.Text = "CONNECT";
            this.talk_btn.UseVisualStyleBackColor = true;
            this.talk_btn.Click += new System.EventHandler(this.talk_btn_Click);
            // 
            // last_receved_data_label
            // 
            this.last_receved_data_label.AutoSize = true;
            this.last_receved_data_label.Location = new System.Drawing.Point(41, 335);
            this.last_receved_data_label.Name = "last_receved_data_label";
            this.last_receved_data_label.Size = new System.Drawing.Size(0, 25);
            this.last_receved_data_label.TabIndex = 6;
            // 
            // lrdll
            // 
            this.lrdll.AutoSize = true;
            this.lrdll.Location = new System.Drawing.Point(12, 296);
            this.lrdll.Name = "lrdll";
            this.lrdll.Size = new System.Drawing.Size(206, 25);
            this.lrdll.TabIndex = 7;
            this.lrdll.Text = "Last Received Data:";
            // 
            // is_conn_label
            // 
            this.is_conn_label.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.is_conn_label.AutoSize = true;
            this.is_conn_label.ForeColor = System.Drawing.Color.Red;
            this.is_conn_label.Location = new System.Drawing.Point(383, 61);
            this.is_conn_label.Name = "is_conn_label";
            this.is_conn_label.Size = new System.Drawing.Size(194, 25);
            this.is_conn_label.TabIndex = 8;
            this.is_conn_label.Text = "NOT CONNECTED";
            this.is_conn_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // disconnect_btn
            // 
            this.disconnect_btn.Location = new System.Drawing.Point(583, 101);
            this.disconnect_btn.Name = "disconnect_btn";
            this.disconnect_btn.Size = new System.Drawing.Size(224, 42);
            this.disconnect_btn.TabIndex = 9;
            this.disconnect_btn.Text = "DISC";
            this.disconnect_btn.UseVisualStyleBackColor = true;
            this.disconnect_btn.Click += new System.EventHandler(this.disconnect_btn_Click);
            // 
            // ax_label
            // 
            this.ax_label.AutoSize = true;
            this.ax_label.Location = new System.Drawing.Point(486, 167);
            this.ax_label.Name = "ax_label";
            this.ax_label.Size = new System.Drawing.Size(91, 25);
            this.ax_label.TabIndex = 10;
            this.ax_label.Text = "Accel X:";
            this.ax_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.ax_label.Click += new System.EventHandler(this.label1_Click);
            // 
            // ay_label
            // 
            this.ay_label.AutoSize = true;
            this.ay_label.Location = new System.Drawing.Point(486, 202);
            this.ay_label.Name = "ay_label";
            this.ay_label.Size = new System.Drawing.Size(92, 25);
            this.ay_label.TabIndex = 11;
            this.ay_label.Text = "Accel Y:";
            this.ay_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // accel_z_label
            // 
            this.accel_z_label.AutoSize = true;
            this.accel_z_label.Location = new System.Drawing.Point(487, 238);
            this.accel_z_label.Name = "accel_z_label";
            this.accel_z_label.Size = new System.Drawing.Size(90, 25);
            this.accel_z_label.TabIndex = 12;
            this.accel_z_label.Text = "Accel Z:";
            this.accel_z_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // ax_out
            // 
            this.ax_out.AutoSize = true;
            this.ax_out.Location = new System.Drawing.Point(583, 167);
            this.ax_out.Name = "ax_out";
            this.ax_out.Size = new System.Drawing.Size(18, 25);
            this.ax_out.TabIndex = 13;
            this.ax_out.Text = "t";
            // 
            // ay_out
            // 
            this.ay_out.AutoSize = true;
            this.ay_out.Location = new System.Drawing.Point(583, 202);
            this.ay_out.Name = "ay_out";
            this.ay_out.Size = new System.Drawing.Size(18, 25);
            this.ay_out.TabIndex = 14;
            this.ay_out.Text = "t";
            // 
            // az_out
            // 
            this.az_out.AutoSize = true;
            this.az_out.Location = new System.Drawing.Point(583, 238);
            this.az_out.Name = "az_out";
            this.az_out.Size = new System.Drawing.Size(18, 25);
            this.az_out.TabIndex = 15;
            this.az_out.Text = "t";
            // 
            // QuadMainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(820, 720);
            this.Controls.Add(this.az_out);
            this.Controls.Add(this.ay_out);
            this.Controls.Add(this.ax_out);
            this.Controls.Add(this.accel_z_label);
            this.Controls.Add(this.ay_label);
            this.Controls.Add(this.ax_label);
            this.Controls.Add(this.disconnect_btn);
            this.Controls.Add(this.is_conn_label);
            this.Controls.Add(this.lrdll);
            this.Controls.Add(this.last_receved_data_label);
            this.Controls.Add(this.talk_btn);
            this.Controls.Add(this.stop_btn);
            this.Controls.Add(this.run_btn);
            this.Controls.Add(this.com_port_label);
            this.Controls.Add(this.com_combo_box);
            this.Controls.Add(this.arm_btn);
            this.Name = "QuadMainWindow";
            this.Text = "Quadrotor";
            this.Load += new System.EventHandler(this.QuadMainWindow_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button arm_btn;
        private System.Windows.Forms.ComboBox com_combo_box;
        private System.Windows.Forms.Label com_port_label;
        private System.Windows.Forms.Button run_btn;
        private System.Windows.Forms.Button stop_btn;
        private System.Windows.Forms.Button talk_btn;
        private System.Windows.Forms.Label last_receved_data_label;
        private System.Windows.Forms.Label lrdll;
        private System.Windows.Forms.Label is_conn_label;
        private System.Windows.Forms.Button disconnect_btn;
        private System.Windows.Forms.Label ax_label;
        private System.Windows.Forms.Label ay_label;
        private System.Windows.Forms.Label accel_z_label;
        private System.Windows.Forms.Label ax_out;
        private System.Windows.Forms.Label ay_out;
        private System.Windows.Forms.Label az_out;
    }
}

