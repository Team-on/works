using System;

namespace TeamCommander {
	namespace Output {
		class DColor : ICloneable {
			public ConsoleColor fore, back;

			public DColor() : this(Settings.StandartColor.color.fore) {
			}
			public DColor(ConsoleColor Fore) : this(Fore, Settings.StandartColor.color.back) {
			}
			public DColor(ConsoleColor Fore, ConsoleColor Back) {
				fore = Fore;
				back = Back;
			}

			public DColor(DColor Color) {
				fore = Color.fore;
				back = Color.back;
			}

			public void ChangeColor() {
				if (Console.ForegroundColor != fore)
					Console.ForegroundColor = fore;
				if (Console.BackgroundColor != back)
					Console.BackgroundColor = back;
			}

			public object Clone() {
				return this.MemberwiseClone();
			}

			public override bool Equals(object Obj) {
				DColor obj = Obj as DColor;
				if (obj == null)
					return false;
				return fore == obj.fore && back == obj.back;
			}
		}

		class OutputObj : ICloneable {
			public DColor color;
			public char sym;

			public OutputObj() : this('\0') {

			}

			public OutputObj(char Sym) : this(Sym, Settings.StandartColor.color) {
			}

			public OutputObj(char Sym, DColor Color) {
				color = new DColor(Color);
				sym = Sym;
			}

			public void Print() {
				color.ChangeColor();
				Console.Write(sym);
			}

			public override bool Equals(object Obj) {
				OutputObj obj = Obj as OutputObj;
				if (obj == null)
					return false;
				return obj.sym == sym && obj.color.Equals(color);
			}

			public object Clone() {
				return new OutputObj(sym, (DColor)color.Clone());
			}
		}

		class Output {
			public Support.Coord screenSize { get; private set; }
			public Support.Coord startPos { get; private set; }
			OutputObj[,] screen, screenBuff;

			public Output(Support.Coord StartPos, Support.Coord ScreenSize) {
				startPos = StartPos;
				screenSize = ScreenSize;
				screen = new OutputObj[screenSize.y, screenSize.x];
				screenBuff = new OutputObj[screenSize.y, screenSize.x];
				for (short i = 0; i < screen.GetLength(0); ++i)
					for (short j = 0; j < screen.GetLength(1); ++j) {
						screen[i, j] = new OutputObj();
						screenBuff[i, j] = new OutputObj();
					}
			}

			public void AddOn(OutputObj[] str, Support.Coord Pos) {
				Support.Coord pos = new Support.Coord(Pos.x, Pos.y);
				for (short i = 0; i < str.GetLength(0); ++i)
					if (str[i].sym != '\n')
						screen[pos.y, pos.x++] = (OutputObj) str[i].Clone();
					else {
						pos.x = Pos.x;
						++pos.y;
					}
			}

			public void ClearOn(OutputObj[] str, Support.Coord Pos) {
				Support.Coord pos = new Support.Coord(Pos.x, Pos.y);
				for (short i = 0; i < str.GetLength(0); ++i)
					if (str[i].sym != '\n') {
						screen[pos.y, pos.x].sym = ' ';
						screen[pos.y, pos.x++].color = (DColor) str[i].color.Clone();
					}
					else {
						pos.x = Pos.x;
						++pos.y;
					}
			}

			public void Init() {
				Console.SetWindowSize(Settings.ScreenSettings.size.x, Settings.ScreenSettings.size.y);
			}

			public void Print() {
				PrintToConsole();
				FillBuff();
			}

			void PrintToConsole() {
				for (short i = 0; i < screen.GetLength(0); ++i) {
					Console.SetCursorPosition(startPos.x, startPos.y + i);
					for (short j = 0; j < screen.GetLength(1); ++j) {
						if (screen[i, j].sym != '\0' && !screen[i, j].Equals(screenBuff[i, j])) {
							if (Console.CursorLeft != j + startPos.x)
								Console.SetCursorPosition(startPos.x + j, startPos.y + i);
							screen[i, j].Print();
						}
					}
				}
			}

			void FillBuff() {
				for (short i = 0; i < screen.GetLength(0); ++i)
					for (short j = 0; j < screen.GetLength(1); ++j)
						if (!screenBuff[i, j].Equals(screen[i, j]))
							screenBuff[i, j] = (OutputObj)screen[i, j].Clone();
			}

			public OutputObj this[int i, int j] {
				get {
					return screen[i, j];
				}
				set {
					screen[i, j] = value;
				}
			}
		}
	}
}
