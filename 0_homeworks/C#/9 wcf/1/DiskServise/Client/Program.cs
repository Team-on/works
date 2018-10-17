using System;
using System.IO;
using System.Windows.Forms;
using System.ServiceModel;

namespace Client {
	class Program {
		[STAThread]
		static void Main() {
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);
			Application.Run(new Form1());
		}
	}
}
