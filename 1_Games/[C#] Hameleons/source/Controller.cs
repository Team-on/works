using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using static Hameleons.Output;

namespace Hameleons {
	sealed class Controller {
		bool isRunning = true;
		bool needNewText = true;

		public void Launch() {
			Init();
			while (isRunning)
				Loop();
		}

		void Init() {
			InitConsole();

			InitOutput();

			void InitConsole() {
				Console.Title = "Hameleons";
			}

			void InitOutput() {
				output.InitOutput(new string[]{
					"All info",
					"Hameleon 1",
					"Hameleon 2",
					"Hameleon 3",
					"Hameleon 4",
				});
			}
		}

		void Loop() {
			ReactInput();

			PrintRightTab();
			PrintLeftTab();

			PrintLog();

			System.Threading.Thread.Sleep(1);

			void PrintLog() {
				Log.log.PrintLog(new Point(2, (byte)(output.rightDownCorner.y + 1)), (byte)(Console.LargestWindowHeight - 5 - output.rightDownCorner.y), (byte)(Console.LargestWindowWidth - 12));
			}

			void PrintRightTab() {
				if (needNewText) {
					needNewText = false;

					string str = null;
					output.Print(str);
				}
			}

			void PrintLeftTab() {

			}
		}

		void ReactInput() {
			if (Console.KeyAvailable) {
				var key = Console.ReadKey(true);
				switch (key.Key) {
				case ConsoleKey.DownArrow:
				output.MoveArrowDown();
				needNewText = true;
				break;
				case ConsoleKey.UpArrow:
				output.MoveArrowUp();
				needNewText = true;
				break;

				case ConsoleKey.LeftArrow:
				//output.HorisontalLeft();
				break;
				case ConsoleKey.RightArrow:
				//output.HorisontalRight();
				break;

				case ConsoleKey.Tab:

				break;

				case ConsoleKey.Backspace:

				break;

				case ConsoleKey.Enter:

				break;

				default:

				break;
				}
			}
		}
	}
}
