using System;

namespace Hameleons {
	sealed class Output {
		public static OutputBase output { get; private set; }

		static Output() {
			output = new OutputBase();
		}
	}

	class OutputBase {
		byte menuPuncts, menuChoose, horisontalPos, menuChoosePrevPos;
		public Point leftUpCorner, rightDownCorner;

		public OutputBase() {
			horisontalPos = menuChoose = 0;
			menuChoosePrevPos = 1;

			leftUpCorner = new Point(0, 0);
			rightDownCorner = new Point(100, 41);

			height = rightDownCorner.y - 2 - leftUpCorner.y;
		}

		public void InitOutput(string[] menuPuncts) {
			SharedMutex.console.WaitOne();
			Console.SetWindowSize(Console.LargestWindowWidth - 2, Console.LargestWindowHeight - 2);
			Console.CursorVisible = false;

			Console.ForegroundColor = ConsoleColor.DarkGray;
			InitLog();
			InitInfoWindow();
			InitStatus();
			InitPeregorodka();
			InitMenu();
			SharedMutex.console.ReleaseMutex();

			void InitLog() {
				string str = "║" + new string(' ', Console.LargestWindowWidth - 7) + "║";
				for (int i = rightDownCorner.y; i < Console.LargestWindowHeight - 3; ++i) {
					Console.SetCursorPosition(1, i);
					Console.Write(str);
				}
				Console.SetCursorPosition(1, rightDownCorner.y);
				Console.Write("╔" + new string('═', Console.LargestWindowWidth - 7) + "╗");
				Console.SetCursorPosition(1, Console.LargestWindowHeight - 3);
				Console.Write("╚" + new string('═', Console.LargestWindowWidth - 7) + "╝");
			}
			void InitInfoWindow() {
				string str = "║" + new string(' ', Console.LargestWindowWidth - 7 - rightDownCorner.x + leftUpCorner.x) + "║";
				for (int i = 1; i < rightDownCorner.y; ++i) {
					Console.SetCursorPosition(rightDownCorner.x + 1, i);
					Console.Write(str);
				}
				Console.SetCursorPosition(rightDownCorner.x + 1, leftUpCorner.y);
				Console.Write("╔" + new string('═', Console.LargestWindowWidth - 7 - rightDownCorner.x + leftUpCorner.x) + "╗");
				Console.SetCursorPosition(rightDownCorner.x + 1, rightDownCorner.y - 1);
				Console.Write("╚" + new string('═', Console.LargestWindowWidth - 7 - rightDownCorner.x + leftUpCorner.x) + "╝");
			}
			void InitPeregorodka() {
				for (int i = leftUpCorner.y + 1; i < rightDownCorner.y - 1; ++i) {
					Console.SetCursorPosition(Console.LargestWindowWidth - 20, i);
					Console.Write('║');
				}
				Console.SetCursorPosition(Console.LargestWindowWidth - 20, leftUpCorner.y);
				Console.Write('╦');
				Console.SetCursorPosition(Console.LargestWindowWidth - 20, rightDownCorner.y - 1);
				Console.Write('╩');
			}
			void InitMenu() {
				Console.ForegroundColor = ConsoleColor.Green;
				for (int i = 0; i < menuPuncts.Length; ++i) {
					Console.SetCursorPosition(Console.LargestWindowWidth - 17, i + leftUpCorner.y + 1);
					Console.Write(menuPuncts[i]);
				}
				this.menuPuncts = (byte)(menuPuncts.Length);
			}
			void InitStatus() {
				string str = "║" + new string(' ', rightDownCorner.x - leftUpCorner.x - 2) + "║";
				for (int i = 1; i < rightDownCorner.y; ++i) {
					Console.SetCursorPosition(leftUpCorner.x + 1, i);
					Console.Write(str);
				}
				Console.SetCursorPosition(leftUpCorner.x + 1, leftUpCorner.y);
				Console.Write("╔" + new string('═', rightDownCorner.x - leftUpCorner.x - 2) + "╗");
				Console.SetCursorPosition(leftUpCorner.x + 1, rightDownCorner.y - 1);
				Console.Write("╚" + new string('═', rightDownCorner.x - leftUpCorner.x - 2) + "╝");
			}
		}

		public void Print(string textToPrint) {
			PrintMenuPunctArrow();
			if (textToPrint != null)
				PrintTextInFrame(textToPrint);
		}

		void PrintMenuPunctArrow() {
			if (menuChoose != menuChoosePrevPos) {
				SharedMutex.console.WaitOne();
				Console.SetCursorPosition(Console.LargestWindowWidth - 19, leftUpCorner.y + 1 + menuChoosePrevPos);
				Console.Write(' ');
				menuChoosePrevPos = menuChoose;
				Console.SetCursorPosition(Console.LargestWindowWidth - 19, leftUpCorner.y + 1 + menuChoose);
				Console.ForegroundColor = ConsoleColor.Yellow;
				Console.BackgroundColor = ConsoleColor.Black;
				Console.Write('→');

				string space = new string(' ', Console.LargestWindowWidth - rightDownCorner.x - 22);
				for (int i = leftUpCorner.y + 1; i < rightDownCorner.y - 1; ++i) {
					Console.SetCursorPosition(rightDownCorner.x + 2, i);
					Console.WriteLine(space);
				}
				SharedMutex.console.ReleaseMutex();
			}
		}

		string[] text;
		int height;
		void PrintTextInFrame(string textToPrint) {
			SharedMutex.console.WaitOne();

			ConsoleColor prev = Console.ForegroundColor;
			Console.ForegroundColor = ConsoleColor.White;
			Console.BackgroundColor = ConsoleColor.Black;

			if (textToPrint != null)
				text = textToPrint.Split('\n');

			for (int i = 0; i < height && i + horisontalPos * height < text.Length; ++i) {
				Console.SetCursorPosition(rightDownCorner.x + 2, i + leftUpCorner.y + 1);
				Console.WriteLine(text[i + horisontalPos * height].PadRight(Console.LargestWindowWidth - rightDownCorner.x - 22));
			}

			for (int i = text.Length - horisontalPos * height; i < height; ++i) {
				Console.SetCursorPosition(rightDownCorner.x + 2, i + leftUpCorner.y + 1);
				Console.WriteLine(new string(' ', Console.LargestWindowWidth - rightDownCorner.x - 22));
			}

			Console.ForegroundColor = prev;
			SharedMutex.console.ReleaseMutex();
		}

		public void MoveArrowDown() {
			++menuChoose;
			if (menuChoose >= menuPuncts)
				menuChoose = 0;
		}
		public void MoveArrowUp() {
			if (menuChoose == 0)
				menuChoose = (byte)(menuPuncts - 1);
			else
				--menuChoose;
		}

		public void HorisontalLeft() {
			if (horisontalPos != 0) {
				--horisontalPos;
				PrintTextInFrame(null);
			}
		}
		public void HorisontalRight() {
			if ((horisontalPos + 1) * height < text.Length) {
				++horisontalPos;
				PrintTextInFrame(null);
			}
		}

		public byte GetMenuChoose() => menuChoose;
	}

	class Point {
		public short x, y;

		public Point() : this(0, 0) { }
		public Point(byte X, byte Y) { x = X; y = Y; }
		public Point(short X, short Y) { x = X; y = Y; }
	}
}
