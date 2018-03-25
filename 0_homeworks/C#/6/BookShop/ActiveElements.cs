using System;

namespace ActiveElements {
	struct Coord {
		public short x, y;
		public Coord(short X, short Y) { x = X; y = Y; }
	}

	//Всі елементи
	interface Element {
		Coord pos { set; get; }
		void Print();
		void Clear();
	}

	//Ті, які можна вибрати page up\down + enter
	interface ActiveElement : Element {
	}

	//Просто текст
	class StaticElement : Element {
		public Coord pos { set; get; }
		protected string str;

		public StaticElement(string elem, Coord printPos) {
			pos = printPos;
			str = elem;
		}

		virtual public void Print() {
			Coord currPos = pos;
			Console.SetCursorPosition(currPos.x, currPos.y);
			foreach (char j in str)
				if (j != '\n')
					Console.Write(j);
				else
					Console.SetCursorPosition(currPos.x, ++currPos.y);
		}

		virtual public void Clear() {
			Coord currPos = pos;
			Console.SetCursorPosition(currPos.x, currPos.y);
			foreach (char j in str)
				if (j != '\n')
					Console.Write(' ');
				else
					Console.SetCursorPosition(currPos.x, ++currPos.y);
		}
	}

	//Просто текст + можливість вибору. Типу кнопка
	class ActiveStaticElement : StaticElement, ActiveElement {
		public ActiveStaticElement(string elem, Coord printPos) : base(elem, printPos) {
		}

	}

	//Поле для вводу. Може бути і кнопкою.
	//Сюда вписуэться лише char
	//TODO: А вообше то тупо якось вийшло. Крашеб був інтерфейс ElementInput у якому би регулювався інпут. А то все в ActiveElementDraw.
	class ActiveInputElement : ActiveElement {
		byte maxLen;
		string str, input;
		public Coord pos { set; get; }
		Coord inputPos;

		public ActiveInputElement(string elem, Coord printPos, Coord InputPos, byte MaxLen) {
			pos = printPos;
			str = elem;
			input = "";
			inputPos = InputPos;
			maxLen = MaxLen;
		}

		public void AddToValue(char c) {
			if (input.Length < maxLen)
				input += c;
		}

		public void DelLastSymbol() {
			if (input.Length != 0)
				input = input.Substring(0, input.Length - 1);
		}

		public string GetValue() {
			return input;
		}

		public void Print() {
			Coord currPos = pos;
			Console.SetCursorPosition(currPos.x, currPos.y);
			foreach (char j in str)
				if (j != '\n')
					Console.Write(j);
				else
					Console.SetCursorPosition(currPos.x, ++currPos.y);
			Console.SetCursorPosition(inputPos.x + pos.x, inputPos.y + pos.y);
			Console.Write(input);
		}

		public void Clear() {
			Coord currPos = pos;
			Console.SetCursorPosition(currPos.x, currPos.y);
			foreach (char j in str)
				if (j != '\n')
					Console.Write(' ');
				else
					Console.SetCursorPosition(currPos.x, ++currPos.y);
		}
	}

	//Для вводу любого голубого
	class ActiveInputElementAllSymbols : ActiveInputElement {
		public ActiveInputElementAllSymbols(string elem, Coord printPos, Coord InputPos, byte MaxLen) : base(elem, printPos, InputPos, MaxLen) {
		}
	}

	//Поле з 2 можливими станами. Все виставляється флагом. Можна вибирати.
	//Нада для зміни з Register/Login на Logout
	class ActiveDoubleElement : ActiveStaticElement {
		public bool flag;
		string str2;
		Coord pos2;

		public ActiveDoubleElement(string elem1, Coord printPos1, string elem2, Coord printPos2) : base(elem1, printPos1) {
			flag = false;
			str2 = elem2;
			pos2 = printPos2;
		}

		override public void Print() {
			string currStr;
			Coord currPos;
			if (flag == false) {
				currPos = pos;
				currStr = str;
			}
			else {
				currPos = pos2;
				currStr = str2;
			}
			if (str.Length != str2.Length) {
				int longer = Math.Max(str.Length, str2.Length);
				if (currStr.Length != longer) {
					currStr += new string(' ', longer - currStr.Length);
				}
			}

			Console.SetCursorPosition(currPos.x, currPos.y);
			foreach (char j in currStr)
				if (j != '\n')
					Console.Write(j);
				else
					Console.SetCursorPosition(currPos.x, ++currPos.y);
		}

		override public void Clear() {
			string currStr;
			Coord currPos;
			if (flag == false) {
				currPos = pos;
				currStr = str;
			}
			else {
				currPos = pos2;
				currStr = str2;
			}
			if (str.Length != str2.Length) {
				int longer = Math.Max(str.Length, str2.Length);
				if (currStr.Length != longer) {
					currStr += new string(' ', longer - currStr.Length);
				}
			}

			Console.SetCursorPosition(currPos.x, currPos.y);
			foreach (char j in currStr)
				if (j != '\n')
					Console.Write(' ');
				else
					Console.SetCursorPosition(currPos.x, ++currPos.y);
		}
	}

	//Клас, який керуватиме всіми елементами.
	//Щеб додати конструктор, який дозволятиме розширяти існуючий ActiveElementDraw. Бо є head, а щоб від нього можна було наповнити контент для кожгої сторінки
	class ActiveElementDraw {
		Element[] elements;

		byte currElement;

		public ActiveElementDraw(params Element[] arr) {
			elements = arr;
		}

		public ActiveElementDraw(ActiveElementDraw prev, params Element[] arr) {
			elements = new Element[prev.elements.Length + arr.Length];
			for (byte i = 0; i < elements.Length; ++i) {
				if (i < prev.elements.Length)
					elements[i] = prev.elements[i];
				if (i < arr.Length)
					elements[i + prev.elements.Length] = arr[i];
			}
		}

		public void InitStatic() {
			for (byte i = 0; i < elements.Length; ++i)
				if (elements[i] is ActiveElement == false)
					elements[i].Print();
		}

		public void ClearScreen() {
			foreach (var i in elements)
				i.Clear();
		}

		public void Print() {
			for (byte i = 0; i < elements.Length; ++i) {
				if (elements[i] is ActiveElement) {
					if (i == currElement)
						Console.BackgroundColor = ConsoleColor.DarkYellow;
					elements[i].Print();
					if (i == currElement)
						Console.BackgroundColor = ConsoleColor.Black;
				}
			}
		}

		public bool ChangeDoubleElementContrain(byte id) {
			if (elements[id] is ActiveDoubleElement) {
				((ActiveDoubleElement)(elements[id])).flag = ((ActiveDoubleElement)(elements[id])).flag ? false : true;
				return true;
			}
			return false;
		}

		public bool GetDoubleElementContrain(byte id) {
			if (elements[id] is ActiveDoubleElement) {
				return ((ActiveDoubleElement)(elements[id])).flag;
			}
			throw new ArgumentException(id.ToString() + " is not ActiveDoubleElement id");
		}

		public string GetInputValue(byte id) {
			if (elements[id] is ActiveInputElement)
				return ((ActiveInputElement)(elements[id])).GetValue();
			return null;
		}

		public byte Input(ConsoleKeyInfo read) {
			do {
				switch (read.Key) {
				case ConsoleKey.PageUp:
				if (currElement != 0)
					--currElement;
				else
					currElement = (byte)(elements.Length - 1);
				break;
				case ConsoleKey.PageDown:
				++currElement;
				if (currElement == elements.Length)
					currElement = 0;
				break;
				case ConsoleKey.Enter:
				return currElement;
				}
			} while (elements[currElement] is ActiveElement == false);

			if (elements[currElement] is ActiveInputElement && read.Key != ConsoleKey.PageUp && read.Key != ConsoleKey.PageDown && read.Key != ConsoleKey.Enter) {
				if (char.IsLetterOrDigit(read.KeyChar))
					((ActiveInputElement)(elements[currElement])).AddToValue(read.KeyChar);
				else if (read.Key == ConsoleKey.Backspace)
					((ActiveInputElement)(elements[currElement])).DelLastSymbol();
				else if (elements[currElement] is ActiveInputElementAllSymbols)
					((ActiveInputElement)(elements[currElement])).AddToValue(read.KeyChar);
			}

			return 255;
		}
	}
}
