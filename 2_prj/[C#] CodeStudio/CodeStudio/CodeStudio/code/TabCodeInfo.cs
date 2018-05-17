using System.Collections.Generic;
using System.IO;
using System.Diagnostics;
using System.Windows.Forms;
using System;
using System.Runtime.InteropServices;

namespace CodeStudio {
	public class TabCodeInfo {
		static SaveFileDialog saveFileDialog = new SaveFileDialog();

		public string path;
		public string name;
		public bool isNew, isSaved, isDefault;
		public RichTextBox tab = new RichTextBox() { Dock = DockStyle.Fill, WordWrap = Singletones.settings.WordWarp };
		public string extensions = "";
		public TreeNode solutionExprorerNode;
		public SyntaxChecker syntaxChecker = null;

		public TabCodeInfo(string Path, CodeTemplateInfo codeTemplateInfo) {
			SetTabWidth(tab, Singletones.settings.TabLength);
			isDefault = false;
			tab.AutoWordSelection = false;
			tab.BackColor = Singletones.settings.DefaultBackgroundText;
			tab.ForeColor = Singletones.settings.DefaultForeground;

			if (Path != null) {
				isNew = false;
				isSaved = true;
				path = Path;
				name = Path.Substring(Path.LastIndexOf('\\') + 1);
				ReadLinkedFile();
			}
			else {
				isNew = true;
				isSaved = false;
				path = name = "New File";
			}

			if (codeTemplateInfo != null) {
				name = "New Code." + codeTemplateInfo.ex;
				tab.Text = codeTemplateInfo.code;
				extensions = codeTemplateInfo.ex + " file" + "|*." + codeTemplateInfo.ex;
				isDefault = true;

				string standartText = tab.Text;
				tab.KeyUp += delegate (object sender, KeyEventArgs args) {

					if (!(args.KeyCode == Keys.Space || args.KeyCode == Keys.Tab || args.KeyCode == Keys.Enter || args.KeyCode == Keys.Up || args.KeyCode == Keys.Left || args.KeyCode == Keys.Right || args.KeyCode == Keys.Down || (args.KeyCode == Keys.C && args.Control) || (args.KeyCode == Keys.X && args.Control) || args.KeyCode == Keys.ShiftKey || args.KeyCode == Keys.ControlKey)) {
						if (isDefault && standartText != tab.Text) {
							isDefault = false;
						}
						else if (!isDefault && standartText == tab.Text) {
							isDefault = true;
						}
					}
				};
								
			}

			if (name.Substring(name.LastIndexOf('.') + 1) == "cs")
				syntaxChecker = Singletones.syntaxChekers.CSharp;

			if (syntaxChecker != null) {
				tab.KeyUp += delegate (object sender, KeyEventArgs args) {
					if (args.KeyCode == Keys.V && args.Control) {
						syntaxChecker.HighlightText(tab);
						return;
					}

					if (args.KeyCode == Keys.Up || args.KeyCode == Keys.Left || args.KeyCode == Keys.Right || args.KeyCode == Keys.Down || (args.KeyCode == Keys.C && args.Control) || (args.KeyCode == Keys.X && args.Control) || args.KeyCode == Keys.ShiftKey || args.KeyCode == Keys.ControlKey)
						return;

					//Singletones.codeStudioMain.Text = (args.KeyData.ToString() + " :: " + KeyToChar(args).ToString());

					bool isSep = false;
					foreach (var i in syntaxChecker.separators) {
						if (KeyToChar(args) == i) {
							isSep = true;
							break;
						}
					}
					if (!isSep)
						syntaxChecker.HighlightThisLine(tab);
					else {
						int SELECTION_START = tab.SelectionStart, SELECTION_LENGTH = tab.SelectionLength;

						tab.SelectionStart -= 1;
						tab.SelectionLength = 1;
						if (tab.SelectedText.IndexOfAny(syntaxChecker.separators) != -1) {
							syntaxChecker.HighlightThisLine(tab);
						}

						tab.SelectionStart = SELECTION_START;
						tab.SelectionLength = SELECTION_LENGTH;
						++tab.SelectionStart;
						tab.SelectionLength = 1;
						//if (tab.SelectedText.IndexOfAny(syntaxChecker.separators) != -1) {
						tab.SelectionLength = 0;
						syntaxChecker.HighlightThisLine(tab);
						//}


						tab.SelectionStart = SELECTION_START;
						tab.SelectionLength = SELECTION_LENGTH;
					}
				};
			}

			var EvenSymbols1 = new char[] { '[', '{', '(', '\"', '\'' };
			var EvenSymbols2 = new char[] { ']', '}', ')', '\"', '\'' };
			bool prevIsEven = false;
			char prevEven = '\0';
			byte prevEvenId = 0;
			tab.KeyDown += delegate (object sender, KeyEventArgs args) {
				if(args.KeyCode == Keys.ShiftKey || args.KeyCode == Keys.ControlKey)
					return;

				if (prevIsEven) {
					if (args.KeyCode == Keys.Back) {
						tab.SelectionLength = 1;
						tab.SelectedText = "";
						if (prevEven == '{') {
							tab.SelectionLength = 1;
							tab.SelectedText = "";
						}
						tab.SelectionLength = 0;
					}

					if (KeyToChar(args) == EvenSymbols2[prevEvenId]) {
						++tab.SelectionStart;
						if (prevEven == '{')
							++tab.SelectionStart;
						args.Handled = true;
						args.SuppressKeyPress = true;
					}
				}

				prevIsEven = false;
				for(byte i = 0; i < EvenSymbols1.Length; ++i) {
					if (EvenSymbols1[i] == KeyToChar(args)) {
						prevEven = EvenSymbols1[i];
						prevIsEven = true;
						prevEvenId = i;
						break;
					}
				}
			};

			SetAutoComplete();
		}

		char KeyToChar(KeyEventArgs key) {
			//bool caplock = Console.CapsLock;
			bool shift = key.Shift;
			bool iscap = shift; //(caplock && !shift) || (!caplock && shift);

			switch (key.KeyCode) {
			case Keys.Enter: return '\n';
			case Keys.A: return (iscap ? 'A' : 'a');
			case Keys.B: return (iscap ? 'B' : 'b');
			case Keys.C: return (iscap ? 'C' : 'c');
			case Keys.D: return (iscap ? 'D' : 'd');
			case Keys.E: return (iscap ? 'E' : 'e');
			case Keys.F: return (iscap ? 'F' : 'f');
			case Keys.G: return (iscap ? 'G' : 'g');
			case Keys.H: return (iscap ? 'H' : 'h');
			case Keys.I: return (iscap ? 'I' : 'i');
			case Keys.J: return (iscap ? 'J' : 'j');
			case Keys.K: return (iscap ? 'K' : 'k');
			case Keys.L: return (iscap ? 'L' : 'l');
			case Keys.M: return (iscap ? 'M' : 'm');
			case Keys.N: return (iscap ? 'N' : 'n');
			case Keys.O: return (iscap ? 'O' : 'o');
			case Keys.P: return (iscap ? 'P' : 'p');
			case Keys.Q: return (iscap ? 'Q' : 'q');
			case Keys.R: return (iscap ? 'R' : 'r');
			case Keys.S: return (iscap ? 'S' : 's');
			case Keys.T: return (iscap ? 'T' : 't');
			case Keys.U: return (iscap ? 'U' : 'u');
			case Keys.V: return (iscap ? 'V' : 'v');
			case Keys.W: return (iscap ? 'W' : 'w');
			case Keys.X: return (iscap ? 'X' : 'x');
			case Keys.Y: return (iscap ? 'Y' : 'y');
			case Keys.Z: return (iscap ? 'Z' : 'z');
			case Keys.D0: return (shift ? ')' : '0');
			case Keys.D1: return (shift ? '!' : '1');
			case Keys.D2: return (shift ? '@' : '2');
			case Keys.D3: return (shift ? '#' : '3');
			case Keys.D4: return (shift ? '$' : '4');
			case Keys.D5: return (shift ? '%' : '5');
			case Keys.D6: return (shift ? '^' : '6');
			case Keys.D7: return (shift ? '&' : '7');
			case Keys.D8: return (shift ? '*' : '8');
			case Keys.D9: return (shift ? '(' : '9');
			case Keys.Oemplus: return (shift ? '+' : '=');
			case Keys.OemMinus: return (shift ? '_' : '-');
			case Keys.OemQuestion: return (shift ? '?' : '/');
			case Keys.Oemcomma: return (shift ? '<' : ',');
			case Keys.OemPeriod: return (shift ? '>' : '.');
			case Keys.OemOpenBrackets: return (shift ? '{' : '[');
			case Keys.OemQuotes: return (shift ? '"' : '\'');
			case Keys.Oem1: return (shift ? ':' : ';');
			case Keys.Oem3: return (shift ? '~' : '`');
			case Keys.Oem5: return (shift ? '|' : '\\');
			case Keys.Oem6: return (shift ? '}' : ']');
			case Keys.Tab: return '\t';
			case Keys.Space: return ' ';

			// Number Pad
			case Keys.NumPad0: return '0';
			case Keys.NumPad1: return '1';
			case Keys.NumPad2: return '2';
			case Keys.NumPad3: return '3';
			case Keys.NumPad4: return '4';
			case Keys.NumPad5: return '5';
			case Keys.NumPad6: return '6';
			case Keys.NumPad7: return '7';
			case Keys.NumPad8: return '8';
			case Keys.NumPad9: return '9';
			case Keys.Subtract: return '-';
			case Keys.Add: return '+';
			case Keys.Decimal: return '.';
			case Keys.Divide: return '/';
			case Keys.Multiply: return '*';

			default: return '\x00';
			}
		}

		void SetAutoComplete() {
			var brakesOpen = new char[] { '[', '{', '(' };
			tab.KeyUp += delegate (object s, KeyEventArgs args) {
				if (args.KeyCode == Keys.Enter) {
					AddTabsToLineLikePrevLine();
					if ((GetPrevLineText()?.LastIndexOfAny(brakesOpen) ?? 0) != -1) {
						PressEnterInsideBrakes();
						tab.SelectedText += '\t';
					}
				}
				else if (args.KeyData == (Keys.OemOpenBrackets | Keys.Shift)) {
					AutoBrakesComplete(" }");
				}
				else if (args.KeyData == (Keys.D9 | Keys.Shift)) {
					AutoBrakesComplete(")");
				}
				else if (args.KeyData == (Keys.OemOpenBrackets)) {
					AutoBrakesComplete("]");
				}
				else if (args.KeyData == (Keys.OemQuotes)) {
					AutoBrakesComplete("\'");
				}
				else if (args.KeyData == (Keys.OemQuotes | Keys.Shift)) {
					AutoBrakesComplete("\"");
				}

				void PressEnterInsideBrakes() {
					tab.SelectionLength = 2;

					if (tab.SelectedText.Contains("}")) {
						if (tab.SelectedText[0] == ' ') {
							tab.SelectedText = "}";
							--tab.SelectionStart;
						}
						tab.SelectionLength = 0;
						int SAVE_POS = tab.SelectionStart;
						tab.SelectedText += '\n';
						AddTabsToLineLikePrevLine();
						tab.SelectionStart = SAVE_POS;
						//tab.SelectedText += '\t';
					}

					else if (tab.SelectedText.Contains(")")) {
						if (tab.SelectedText[0] == ' ') {
							tab.SelectedText = ")";
							--tab.SelectionStart;
						}
						tab.SelectionLength = 0;
						int SAVE_POS = tab.SelectionStart;
						tab.SelectedText += '\n';
						AddTabsToLineLikePrevLine();
						tab.SelectionStart = SAVE_POS;
						//tab.SelectedText += '\t';
					}
					else if (tab.SelectedText.Contains("]")) {
						if (tab.SelectedText[0] == ' ') {
							tab.SelectedText = "]";
							--tab.SelectionStart;
						}
						tab.SelectionLength = 0;
						int SAVE_POS = tab.SelectionStart;
						tab.SelectedText += '\n';
						AddTabsToLineLikePrevLine();
						tab.SelectionStart = SAVE_POS;
						//tab.SelectedText += '\t';
					}
					tab.SelectionLength = 0;
				}

				void AutoBrakesComplete(string closed) {
					tab.SelectedText += closed;
					tab.SelectionStart -= closed.Length;
				}

				void AddTabsToLineLikePrevLine() {
					if (tab.SelectionStart <= 2)
						return;

					int SAVE_SELECTION_START = tab.SelectionStart;

					--tab.SelectionStart;
					int endPos = tab.SelectionStart, tabsCnt = 0, startPos;
					tab.SelectionLength = 1;

					--tab.SelectionStart;
					while (tab.SelectedText[0] != '\n' && tab.SelectionStart != 0) --tab.SelectionStart;
					++tab.SelectionStart;
					startPos = tab.SelectionStart;

					while (tab.SelectedText[0] == '\t' && tab.SelectionStart++ < endPos) ++tabsCnt;

					tab.SelectionStart = endPos + 1;
					tab.SelectionLength = 0;
					tab.SelectedText += new string('\t', tabsCnt);
				}

				string GetPrevLineText() {
					int SAVE_SELECTION_START = tab.SelectionStart;
					int SAVE_SELECTION_LENGTH = tab.SelectionLength;

					int end = tab.Text.Substring(0, tab.SelectionStart).LastIndexOf('\n');
					if (end == -1)
						return null;
					int start = tab.Text.Substring(0, end).LastIndexOf('\n') + 1;
					if (start == 0)
						return null;
					tab.SelectionStart = start;
					tab.SelectionLength = end - start;

					string rez = tab.SelectedText;

					tab.SelectionStart = SAVE_SELECTION_START;
					tab.SelectionLength = SAVE_SELECTION_LENGTH;

					return rez;
				}
			};
		}

		public Process CompileSingleFile() {
			return Singletones.singleFileCompiler.Compile(path);
		}
		public void RunLinkedExe() {
			Singletones.singleFileCompiler.RunExe(path);
		}

		public void ReadLinkedFile() {
			using (var t = new StreamReader(path))
				tab.Text = t.ReadToEnd();
			isSaved = true;
		}

		//True if saved
		public bool SaveLinkedFile(bool forcedByUser = false) {
			if (!forcedByUser && (isSaved || isDefault))
				return false;

			if (isNew) {
				if (extensions != "")
					saveFileDialog.Filter = extensions;
				if (saveFileDialog.ShowDialog() == DialogResult.OK) {
					path = saveFileDialog.FileName;
					using (var writer = new StreamWriter(path))
						writer.Write(tab.Text);
					isNew = false;
					name = path.Substring(path.LastIndexOf('\\') + 1);
					isSaved = true;
					solutionExprorerNode.Text = name;
					saveFileDialog.FileName = "";
				}
			}
			else {
				using (var writer = new StreamWriter(path))
					writer.Write(tab.Text);
				isSaved = true;
			}
			return isSaved;
		}

		// set tab stops to a width of 4
		private const int EM_SETTABSTOPS = 0x00CB;

		[DllImport("User32.dll", CharSet = CharSet.Auto)]
		public static extern IntPtr SendMessage(IntPtr h, int msg, int wParam, int[] lParam);

		public static void SetTabWidth(RichTextBox textbox, int tabWidth) {
			var characterWidth = (int)textbox.CreateGraphics().MeasureString("M", Singletones.codeStudioMain.Font).Width;
			SendMessage(textbox.Handle, EM_SETTABSTOPS, 1,
						new int[] { tabWidth / 2 * characterWidth });

			//SendMessage(textbox.Handle, EM_SETTABSTOPS, 1,
			//new int[] { tabWidth * 4 });
		}
		//END of tab with set
	}
}
