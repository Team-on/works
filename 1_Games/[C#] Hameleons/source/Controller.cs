using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using static Hameleons.Output;

namespace Hameleons {
	sealed class Controller {
		bool isRunning = true;
		//bool needNewText = true;
		HameleonCommander hameleonCommander = new HameleonCommander();

		public void Launch() {
			Init();
			while (isRunning)
				Loop();
		}

		void Init() {
			InitConsole();
			InitOutput();

			hameleonCommander.Start(10);

			void InitConsole() {
				Console.Title = "Hameleons";
			}

			void InitOutput() {
				output.InitOutput(new string[]{
					"All info",
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
				Log.log.PrintLog(new Point(2, (byte)(output.rightDownCorner.y + 1)), (byte)(Console.LargestWindowHeight - 5 - output.rightDownCorner.y), (byte)(Console.LargestWindowWidth - 20));
			}

			void PrintRightTab() {
				if (/*needNewText*/true) {
					//needNewText = false;

					string str = null;
					switch (output.GetMenuChoose()) {
						case 0:
							str = $"Remaing meatings: {HameleonCommander.MeatingCounter}";
							break;
						case 1:
							str = "Text 1";
							break;
						case 2:
							str = "Text 2";
							break;
						case 3:
							str = "Text 3";
							break;
						case 4:
							str = "Text 4";
							break;
					}
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
				//needNewText = true;
				break;
				case ConsoleKey.UpArrow:
				output.MoveArrowUp();
				//needNewText = true;
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
