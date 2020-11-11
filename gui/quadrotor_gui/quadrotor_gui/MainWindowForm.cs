using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace quadrotor_gui
{
    public partial class QuadMainWindow : Form
    {
        SerialComm comm;
        bool runThread;
        const int DELAY = 10;
        Thread readThread;
        delegate void updateMsgDel();

        public QuadMainWindow()
        {
            InitializeComponent();
            this.runThread = true;
            readThread = new Thread(WriteReturnedData);
            readThread.Start();
            ax_out.Text = "";
            ay_out.Text = "";
            az_out.Text = "";
            init_serial_ports();
        }

        private void init_serial_ports()
        {
            // Load serial port data into com_combo_box
            com_combo_box.BeginUpdate();
            com_combo_box.Items.Clear();
            foreach (string s in SerialComm.GetSerialPorts())
            {
                com_combo_box.Items.Add(s);
            }
            com_combo_box.EndUpdate();
            if (com_combo_box.Items.Count > 0)
            {
                com_combo_box.SelectedIndex = 0;
            }
        }

        private void com_port_label_Click(object sender, EventArgs e)
        {
            init_serial_ports();
        }

        private void talk_btn_Click(object sender, EventArgs e)
        {
            if (comm != null) { comm.Close(); }
            set_conn_text();
            comm = new SerialComm((string)com_combo_box.SelectedItem, 115200);
            set_conn_text();
        }

        private void arm_btn_Click(object sender, EventArgs e)
        {
            if (comm != null) { comm.WriteCmd(Util.ARM_CMD_STR); }
        }

        private void run_btn_Click(object sender, EventArgs e)
        {
            if (comm != null) { comm.WriteCmd(Util.RUN_CMD_STR); }
        }

        private void stop_btn_Click(object sender, EventArgs e)
        {
            if (comm != null) { comm.WriteCmd(Util.STP_CMD_STR); }
        }

        private void updateMsg()
        {
            string msg = comm.GetNextMessage();
            switch(Util.GetMsgType(msg))
            {
                case Util.MessageType.AX:
                    ax_out.Text = msg.Substring(3);
                    break;
                case Util.MessageType.AY:
                    ay_out.Text = msg.Substring(3);
                    break;
                case Util.MessageType.AZ:
                    az_out.Text = msg.Substring(3);
                    break;
                default:
                    last_receved_data_label.Text = msg;
                    break;
            }
            last_receved_data_label.Text = comm.GetNextMessage();
            set_conn_text();
        }

        private void WriteReturnedData()
        {
            updateMsgDel mU = new updateMsgDel(updateMsg);
            while (runThread)
            {
                if (comm != null && comm.MessageAvailable())
                {
                    this.Invoke(mU);
                }
                Thread.Sleep(DELAY);
            }
        }

        private void disconnect_btn_Click(object sender, EventArgs e)
        {
            this.comm?.Close();
            set_conn_text();
        }

        private void set_conn_text()
        {
            bool Connected = false;
            if (comm != null) { Connected = comm.IsConnected(); }
            is_conn_label.Text = Connected ? "CONNECTED" : "NOT CONNECTED";
            is_conn_label.ForeColor = Connected ? Color.Green : Color.Red;
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void QuadMainWindow_Load(object sender, EventArgs e)
        {

        }

        private void com_combo_box_SelectedIndexChanged(object sender, EventArgs e)
        {
            comm?.Close();
            set_conn_text();
        }
    }
}
