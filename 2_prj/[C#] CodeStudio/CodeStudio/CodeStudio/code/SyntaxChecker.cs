using System.Collections.Generic;
using System.IO;
using System.Drawing;
using System.Windows.Forms;
using System;
using System.Xml;

namespace CodeStudio {
	public class CS_SyntaxChecker : SyntaxChecker {
		public CS_SyntaxChecker() {
			LoadByEx("cs");
		}
	}

	public class SyntaxChecker {
		SyntaxKeyword[] words;
		Color defaultColor = Color.Black;
		public char[] separators;

		public void HighlightThisLine(RichTextBox tab) {
			try {
				int startH, endH;
				GetWordStart();
				SetWordEnd();

				HightlightInputedWord(tab, startH, endH);

				void GetWordStart() {
					startH = 0;
					int tmp;
					tmp = tab.Text.Substring(0, tab.SelectionStart).LastIndexOfAny(separators);
					if (tmp == -1)
						return;
					startH = tmp + 1;
				}
				void SetWordEnd() {
					endH = tab.Text.Length;
					int tmp = tab.Text.Substring(tab.SelectionStart).IndexOfAny(separators);
					if (tmp == -1)
						return;
					endH = tmp + tab.SelectionStart;
				}
			}
			catch (Exception ex) {

			}
		}

		void HightlightInputedWord(RichTextBox tab, int start, int end) {
			int SELECTION_START = tab.SelectionStart, SELECTION_LENGTH = tab.SelectionLength;

			bool colored = false;

			string prevSep = tab.Text.Substring(start - 1, 1), nextSep = tab.Text.Substring(end, 1);
			if (prevSep.LastIndexOfAny(separators) != -1 && nextSep.LastIndexOfAny(separators) != -1) {

				string str = tab.Text.Substring(start, end - start);

				//Singletones.codeStudioMain.Text = ("_" + prevSep + "_ _" + str + "_ _"  + nextSep + "_");
				foreach (var currWord in words) {
					if (currWord.Word.Length == end - start &&
							str.Contains(currWord.Word)
						) {
						tab.SelectionStart = start;
						tab.SelectionLength = currWord.Word.Length;
						tab.SelectionColor = currWord.Color;
						colored = true;
						break;
					}
				}

				if (!colored) {
					tab.SelectionStart = start;
					tab.SelectionLength = end - start;
					tab.SelectionColor = defaultColor;
				}
			}

			tab.SelectionStart = SELECTION_START;
			tab.SelectionLength = SELECTION_LENGTH;
			tab.SelectionColor = defaultColor;
		}

		public void HighlightText(RichTextBox textBox) {
			int SELECTION_START = textBox.SelectionStart, SELECTION_LENGTH = textBox.SelectionLength;
			textBox.SelectionStart = 0;
			textBox.SelectionLength = textBox.Text.Length;
			textBox.SelectionColor = defaultColor;

			var separatedText = textBox.SelectedText.Split(separators);

			foreach (var currWord in words) {
				textBox.SelectionLength = currWord.Word.Length;
				currWord.LastPos = -currWord.Word.Length;
				foreach (var str in separatedText) {
					if (str == currWord.Word) {
						if (currWord.LastPos + textBox.SelectionLength >= 0) {
							currWord.LastPos = textBox.Text.Substring(currWord.LastPos + textBox.SelectionLength).
								IndexOf(currWord.Word) + currWord.LastPos + textBox.SelectionLength;
							textBox.SelectionStart = currWord.LastPos;
							textBox.SelectionColor = currWord.Color;
						}
					}
				}
			}

			textBox.SelectionStart = SELECTION_START;
			textBox.SelectionLength = SELECTION_LENGTH;
		}

		protected void LoadByEx(string ex) {
			Color keywordDefault = Color.Blue, currKeywordColor;
			List<SyntaxKeyword> listKeyword = new List<SyntaxKeyword>(64);
			List<char> listSeparator = new List<char>(64);

			XmlDocument xml = new XmlDocument();
			xml.Load("SyntaxChecker\\" + ex.ToLower() + ".xml");

			LoadDefaultsSettings();

			string nodeName;
			foreach (XmlNode node in xml.ChildNodes[1]) {
				nodeName = node.Name.ToLower();

				if (nodeName == "keyword") {
					currKeywordColor = keywordDefault;
					foreach (XmlAttribute attrib in node.Attributes) {
						if (attrib.Name.ToLower() == "color")
							currKeywordColor = Color.FromName(attrib.Value);
					}

					listKeyword.Add(new SyntaxKeyword(node.InnerText.Trim(), currKeywordColor));
				}
				else if (nodeName == "separator") {
					if(node.InnerText == "\\t")
						listSeparator.Add('\t');
					else if (node.InnerText == "\\n")
						listSeparator.Add('\n');
					else if (node.InnerText == "\\ ")
						listSeparator.Add(' ');
					else if(node.InnerText.Length == 1)
						listSeparator.Add(node.InnerText[0]);
					//MessageBox.Show("@" + node.InnerText + "@");
				}
			}

			words = listKeyword.ToArray();
			separators = listSeparator.ToArray();


			void LoadDefaultsSettings() {
				foreach (XmlNode nodeRoot in xml.ChildNodes[1]) {
					if (nodeRoot.Name.ToLower() == "colors") {
						foreach (XmlNode node in nodeRoot.ChildNodes) {
							if (node.Name.ToLower() == "keywordcolor")
								keywordDefault = Color.FromName(node.InnerText);
							else if (node.Name.ToLower() == "defaultcolor")
								defaultColor = Color.FromName(node.InnerText);
						}
						break;
					}
				}
			}
		}

		protected SyntaxChecker() {

		}
	}

	class SyntaxKeyword {
		public string Word { get; private set; }
		public Color Color { get; private set; }
		public int LastPos { get; set; }

		public SyntaxKeyword(string word, Color color) {
			Word = word;
			Color = color;
		}
	}
}
