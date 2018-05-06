using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;

namespace FormXML {
	class FormCreator {
		Form res = new Form();

		public Form LoadForm(string path) {
			XmlDocument xml = new XmlDocument();
			xml.Load(path);

			MainParse(xml, res);

			return res;
		}

		void MainParse(XmlNode node, Control elem) {
			Control control = elem;
			switch (node.Name.ToLower()) {
				case "button":
					control = new Button();
				break;
				case "label":
					control = new Label();
				break;
			}

			foreach (XmlNode i in node.ChildNodes) {
				switch (i.Name.ToLower()) {
					case "controlinfo":
						ParseControlInfo(i, control);
					break;
					case "buttoninfo":
						ParseButtonInfo(i, (Button)control);
					break;
					case "labelinfo":
						ParseLabelInfo(i, (Label)control);
					break;
				}

				MainParse(i, control);
			}

			if (elem != control)
				elem.Controls.Add(control);
		}

		void ParseControlInfo(XmlNode node, System.Windows.Forms.Control c) {
			foreach(XmlNode i in node.ChildNodes) {
				string name = i.Name.ToLower();
				i.InnerText = i.InnerText.Trim();
				if (name == "size") {
					var tmp = i.InnerText.Split(',');
					c.Size = new Size(int.Parse(tmp[0]), int.Parse(tmp[1]));
				}
				else if (name == "location") {
					var tmp = i.InnerText.Split(',');
					c.Location = new Point(int.Parse(tmp[0]), int.Parse(tmp[1]));
				}
				else if (name == "name")
					c.Name = i.InnerText;
				else if (name == "text")
					c.Text = i.InnerText;
				else if (name == "forecolor")
					c.ForeColor = Color.FromName(i.InnerText);
				else if (name == "backcolor")
					c.BackColor = Color.FromName(i.InnerText);

				else if (name == "fontinfo")
					ParseFontInfo(i, c);
			}
		}

		void ParseFontInfo(XmlNode node, System.Windows.Forms.Control c) {
			string familyName = "GenericSansSerif";
			float size = 10;
			FontStyle fontStyle = FontStyle.Regular;

			foreach (XmlNode i in node.Attributes) {
				string name = i.Name.ToLower().Trim();
				string text =  i.InnerText.ToLower().Trim();
				
				if (name == "familyname")
					familyName = i.InnerText.Trim();
				if (name == "size") 
					size = int.Parse(text);
				if (name == "fontstyle") {
					var tmp = text.Split(',');
					foreach (var str in tmp) {
						var str2 = str.Trim();
						if (str2 == FontStyle.Bold.ToString().ToLower())
							fontStyle |= FontStyle.Bold;
						else if (str2 == FontStyle.Italic.ToString().ToLower())
							fontStyle |= FontStyle.Italic;
						else if (str2 == FontStyle.Strikeout.ToString().ToLower())
							fontStyle |= FontStyle.Strikeout;
						else if (str2 == FontStyle.Underline.ToString().ToLower())
							fontStyle |= FontStyle.Underline;
					}
				}
			}
			c.Font = new Font(familyName, size, fontStyle);
		}

		void ParseButtonInfo(XmlNode node, System.Windows.Forms.Button c) {

		}

		void ParseLabelInfo(XmlNode node, System.Windows.Forms.Label c) {
			foreach (XmlNode i in node.ChildNodes) {
				string text = i.InnerText.Trim().ToLower();
				string name = i.Name.ToLower();
				if (name == "autosize") {
					if(text[0] == 'f')
						c.AutoSize = false;
					else if (text[0] == 't')
						c.AutoSize = true;
				}
				else if (name == "textalign") {
					if (text == "bottomleft")
						c.TextAlign = ContentAlignment.BottomLeft;
					else if (text == "bottomcenter")
						c.TextAlign = ContentAlignment.BottomCenter;
					else if (text == "bottomright")
						c.TextAlign = ContentAlignment.BottomRight;
					else if (text == "middleleft")
						c.TextAlign = ContentAlignment.MiddleLeft;
					else if (text == "middlecenter")
						c.TextAlign = ContentAlignment.MiddleCenter;
					else if (text == "middleright")
						c.TextAlign = ContentAlignment.MiddleRight;
					else if (text == "topleft")
						c.TextAlign = ContentAlignment.TopLeft;
					else if (text == "topcenter")
						c.TextAlign = ContentAlignment.TopCenter;
					else if (text == "topright")
						c.TextAlign = ContentAlignment.TopRight;
				}
			}
		}
	}
}
