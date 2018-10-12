using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Threading;

namespace Client {
	public partial class Form1 : Form {
		TcpClient tcp = new TcpClient();
		NetworkStream stream;
		Thread r;

		public Form1() {
			InitializeComponent();
			r = new Thread(new ThreadStart(recieve));
			r.Start();
		}

		public void recieve() {
			byte[] arr = new byte[3];
			int readRez = 0;

			while(true) {
				while(!(stream?.DataAvailable ?? false))
					Thread.Sleep(2);
				readRez = stream?.ReadByte() ?? -1;

				if(readRez == -1) {
					Thread.Sleep(10);
					continue;
				}

				else if(readRez == 1) {
					while(!stream.DataAvailable)
						Thread.Sleep(2);
					stream.Read(arr, 0, 3);
					/*MessageBox.Show*/ this.Text =  (string.Format($"\tRecieve: {arr[0]} {arr[1]} {arr[2]}"));

					foreach(var item in this.Controls) {
						if(item != null && (((item as Button)?.Tag as string)?.Equals(arr[0].ToString()) ?? false)) {
							(item as Button).Text = arr[1] == 0 ? "0" : "X";

							//MessageBox.Show(arr[0].ToString() + "  |  " + ((item as Button)?.Tag as string));

							switch(arr[2]) {
								case 1: MessageBox.Show("Nichiya"); break;
								case 2: MessageBox.Show("Win: O"); break;
								case 3: MessageBox.Show("Win: X"); break;
							}

							if(arr[2] != 0) {
								stream.Close();
								tcp.Close();
								return;
							}

							break;
						}
					}
				}

			}
		}

		private void button10_Click(object sender, EventArgs e) {
			new Task(
				new Action(delegate () {
					try {
						tcp.Connect(textBox1.Text, Int32.Parse(textBox2.Text));
						stream = tcp.GetStream();
						button10.Enabled = textBox1.Enabled = textBox2.Enabled = false;
						byte rez = (byte)stream.ReadByte();
						label2.Text = rez == 0 ? "0" : "X";
					}
					catch(Exception s) {
						MessageBox.Show(s.Message);
					}
				})
			).Start();
		}

		private void CLICK(object sender, EventArgs e) {
			new Task(
				new Action(delegate () {
					stream.WriteByte(byte.Parse(((sender as Button).Tag as string)));
				})
			).Start();
		}

		private void Form1_FormClosing(object sender, FormClosingEventArgs e) {
			stream?.Close();
			tcp?.Close();
		}
	}
}
