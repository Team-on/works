using System;
using System.Collections.Generic;

namespace Hameleons {
	class InputFieldController {
		public int TabIdMax = 0;
		public int CurrTabId = 0;

		List<InputField> list = new List<InputField>();

		public void AddField(InputField f) {
			list.Add(f);
		}

		public void PrintAll() {
			for (int i = 0; i < list.Count; ++i) {
				if (i == CurrTabId)
					Console.ForegroundColor = ConsoleColor.Yellow;
				list[i].Print();
				if (i == CurrTabId)
					Console.ForegroundColor = ConsoleColor.White;
			}
		}

		public string GetData(int tab) {
			return list[tab].Text;
		}

		public void Clear() {
			foreach (var i in list) {
				i.Text = "";
			}
		}

		public void PressTab() {
			++CurrTabId;
			if (CurrTabId == TabIdMax)
				CurrTabId = 0;
		}

		public void AddLeterToSelectedTab(char l) {
			if ((list[CurrTabId].inputType == InputFieldType.Chars && char.IsLetter(l)) ||
				(list[CurrTabId].inputType == InputFieldType.Numbers && char.IsNumber(l)))
					if(list[CurrTabId].Text.Length < 20)
						list[CurrTabId].Text += l;
		}
		public void BackspaceLeterToSelectedTab() {
			if(list[CurrTabId].Text.Length != 0)
			if (list[CurrTabId].inputType != InputFieldType.Lock)
				list[CurrTabId].Text = list[CurrTabId].Text.Substring(0, list[CurrTabId].Text.Length - 1);
		}
	}

	enum InputFieldType : byte { Lock = 0, Numbers = 1, Chars = 2, All = 0b11111111 }

	class InputField {
		Point startPos;
		string PreText { get; set; }
		public string Text { get; set; }
		public int TabId { get; private set; }

		public InputFieldType inputType;

		public InputField(Point pos, string preText, InputFieldController ctor, InputFieldType InputType) {
			startPos = pos;
			PreText = preText;
			TabId = ++ctor.TabIdMax;
			inputType = InputType;
			Text = "";
		}

		public void Print() {
			Console.SetCursorPosition(startPos.x, startPos.y);
			Console.Write(PreText);
			Console.Write(Text);
			if(inputType != InputFieldType.Lock)
				Console.Write(new string(' ', 20 - Text.Length));
		}
	}
}
