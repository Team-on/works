using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;

namespace FormXML {
	class FormCreator {
		public Form LoadForm(string path) {
			Form res = new Form();


			XmlDocument xml = new XmlDocument();
			xml.Load(path);
			
			

			return res;
		}
	}
}
