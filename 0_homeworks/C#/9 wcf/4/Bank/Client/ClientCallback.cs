﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client {
	class ClientCallback : Client.BankServiceReference.IBankCallback {
		public Client.Form1 form;

		public void Balance(int m) {
			form.textBox3.Text = m.ToString();
		}

	}
}