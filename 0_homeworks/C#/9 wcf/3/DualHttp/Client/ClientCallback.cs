using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client {
	class ClientCallback : ServiceReference1.IService1Callback {
		public Client.Form1 form;

		public void TextForUsers(string txt) {
			form.textBox3.Text = txt;
		}
	}
}
