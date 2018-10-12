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
		byte[] one = new byte[1];

		public Form1() {
			InitializeComponent();
			r = new Thread(new ThreadStart(recieve));
			r.Start();
		}
		public void recieve() {
			while(true)
				if(stream != null) {
					while(true) {
						byte[] arr = new byte[1];
						stream.Read(arr, 0, 1);
						if(arr[0] == 1) {
							arr = new byte[3];
							stream.Read(arr, 0, arr.Length);
							foreach(var item in this.Controls) {
								if(item != null && (((item as Button)?.Tag as String)?.Equals(arr[0].ToString()) ?? false)) {
									(item as Button).Text = arr[1] == 1 ? "X" : "O";
									switch(arr[2]) {
										case 1: MessageBox.Show("Nichiya"); break;
										case 2: MessageBox.Show("Win : O"); break;
										case 3: MessageBox.Show("Win : X"); break;
									}
									if(arr[2] > 0 && arr[2] < 4) {
										stream.Close();
										tcp.Close();
									}
								}
							}
						}
					}
				}
		}
		private void button10_Click(object sender, EventArgs e) {
			Task a = new Task(new Action(delegate () {
				try {
					tcp.Connect(textBox1.Text, Int32.Parse(textBox2.Text));
					stream = tcp.GetStream();
					stream.Read(one, 0, 1);
					textBox1.Enabled = textBox2.Enabled = false;
					label2.Text = one[0] == 1 ? "0" : "Y";
				}
				catch(Exception s) { MessageBox.Show(s.Message); }
			}));
			a.Start();
		}
		private void CLICK(object sender, EventArgs e) {
			Task l = new Task(new Action(delegate () { stream.Write(BitConverter.GetBytes(Int32.Parse((sender as Button).Name[1].ToString())), 0, 1); }));
			l.Start();
		}

		private void Form1_FormClosing(object sender, FormClosingEventArgs e) {
			if(stream != null)
				stream.Close();
			if(tcp != null)
				tcp.Close();
		}
	}
}
