using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Threading;

namespace quadrotor_gui
{
    public class SerialComm
    {
        const int DELAY = 10;
        private SerialPort port;
        private Queue<string> receivedQueue;
        private Thread rThread;
        private bool Continue;
        private bool Connected;
                
        public SerialComm(string port, int baud)
        {
            // 1 start bit, 1 stop bit
            // No Parity
            // 8 bits
            this.Continue = true;
            this.receivedQueue = new Queue<string>();
            this.port = new SerialPort(port, baud, Parity.None, 8, StopBits.One)
            {
                ReadTimeout = 1000
            };
            try { this.port.Open(); }
            catch
            {
                Connected = false;
                return;
            }
            Connected = true;
            rThread = new Thread(Receive);
            rThread.Start();
        }
        
        public void WriteCmd(string command) { this.port.WriteLine(command); }

        public bool IsConnected() { return Connected; }

        private void Receive()
        {
            string line = "";
            while (Continue && this.port.IsOpen)
            { 
                if (this.port.BytesToRead > 0)
                {
                    try { line = this.port.ReadLine();  }
                    catch { }
                    if (line != "") { this.receivedQueue.Enqueue(line); }
                }
                Thread.Sleep(DELAY);
            }
            Connected = false;
        }

        public bool MessageAvailable() { return receivedQueue.Count > 0; }

        public string GetNextMessage()
        {
            if (MessageAvailable()) { return receivedQueue.Dequeue(); }
            else { return ""; }
        }

        public void Close()
        {
            this.Continue = false;
            this.rThread?.Join();            
            this.port?.Close();
        }

        public void Dispose() { Close(); }

        public static List<string> GetSerialPorts()
        {
            return SerialPort.GetPortNames().ToList();
        }
    }
}
