using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using static CarParking.Output;
using static CarParking.Parking;

namespace CarParking {
	sealed class Controller {
		bool isRunning = true;
		bool needNewText = true;

		InputFieldController[] fieldController = new InputFieldController[3];

		public void Launch() {
			Init();
			while (isRunning)
				Loop();
		}

		void Init() {
			InitConsole();

			InitOutput();
			InitInput();

			void InitConsole() {
				Console.Title = "Parking";

			}

			void InitOutput() {
				output.InitOutput(new string[]{
					"View cars",
					"Add car",
					"Delete car",
					"Add balance",
					"Log"
				});
			}

			void InitInput() {
				fieldController[0] = new InputFieldController();
				string str = "Car type [";
				for (byte i = 0; i < (byte)CarType.NONE; ++i) {
					str += ((CarType)(i)).ToString().ToLower();
					if (i != (byte)CarType.NONE - 1)
						str += ", ";
				}
				str += "]: ";

				fieldController[0].AddField(new InputField(new Point(54, 1), str, fieldController[0], InputFieldType.Chars));
				fieldController[0].AddField(new InputField(new Point(54, 2), "Balance(uint): ", fieldController[0], InputFieldType.Numbers));
				fieldController[0].AddField(new InputField(new Point(54, 3), "|Create|", fieldController[0], InputFieldType.Lock));


				fieldController[1] = new InputFieldController();
				fieldController[1].AddField(new InputField(new Point(54, 1), "Car id(uint): ", fieldController[1], InputFieldType.Numbers));
				fieldController[1].AddField(new InputField(new Point(54, 2), "|Delete|", fieldController[1], InputFieldType.Lock));


				fieldController[2] = new InputFieldController();
				fieldController[2].AddField(new InputField(new Point(54, 1), "Car id(uint): ", fieldController[2], InputFieldType.Numbers));
				fieldController[2].AddField(new InputField(new Point(54, 2), "Money to deposit(uint): ", fieldController[2], InputFieldType.Numbers));
				fieldController[2].AddField(new InputField(new Point(54, 3), "|Deposit|", fieldController[2], InputFieldType.Lock));
			}
		}

		void Loop() {
			ReactInput();

			PrintRightTab();
			PrintLeftTab();

			PrintInputFileds();

			PrintLog();

			System.Threading.Thread.Sleep(1);

			void PrintLog() {
				Log.log.PrintLog(new Point(2, (byte)(output.rightDownCorner.y + 1)), (byte)(Console.LargestWindowHeight - 5 - output.rightDownCorner.y), (byte)(Console.LargestWindowWidth - 12));
			}

			void PrintRightTab() {
				if (needNewText) {
					needNewText = false;

					string str = null;
					if (output.GetMenuChoose() == 0)
						str = FillWithCarList();
					else if (output.GetMenuChoose() == 4)
						str = FillWithTransactionLog();
					output.Print(str);
				}

				string FillWithTransactionLog() {
					StringBuilder res = new StringBuilder(" ║ " + "    Date".PadRight(12) + " ║ " + "  Time".PadRight(8) + " ║ " + "    Income".PadRight(15) + " ║\n");

					string[] strs;

					using (StreamReader file = new StreamReader("transaction.log")) {
						while (!file.EndOfStream) {
							strs = file.ReadLine().Split(' ');
							res.Append(" ║ " + strs[0].Trim().PadRight(12) + " ║ " + strs[1].Trim().PadRight(8) + " ║ " + strs[2].Trim().PadRight(15) + " ║\n");
						}
					}

					return res.ToString();
				}

				string FillWithCarList() {
					StringBuilder str = new StringBuilder(" ║ " + " Id".PadRight(5) + " ║ " + "    Type".PadRight(10) + " ║ " + "   Balance".PadRight(15) + " ║\n");
					needNewText = true;

					foreach (Car i in parking) {
						str.Append(" ║ " + i.Id.ToString().PadRight(5) + " ║ " + i.Type.ToString().PadRight(10) + " ║ " + (i.Balance != 0 ? i.Balance : -i.Fine).ToString().PadRight(15) + " ║\n");
					}

					return str.ToString();
				}
			}

			void PrintInputFileds() {
				if (output.GetMenuChoose() == 1)
					fieldController[0].PrintAll();
				else if (output.GetMenuChoose() == 2)
					fieldController[1].PrintAll();
				else if (output.GetMenuChoose() == 3)
					fieldController[2].PrintAll();
			}

			void PrintLeftTab() {
				FillPlaces();
				FillProgressBar();
				FillEarnedMoney();

				void FillPlaces() {
					Console.ForegroundColor = ConsoleColor.White;
					Console.SetCursorPosition(3, 2);
					Console.Write(string.Format($"Places: {parking.ParkingSpaceFree} / {parking.ParkingSpaceAll}"));
				}

				void FillProgressBar() {
					int currPersent = (int)Math.Round(parking.ParkingSpaceFree * 1.0 / parking.ParkingSpaceAll * 47);

					Console.SetCursorPosition(3, 3);
					Console.BackgroundColor = ConsoleColor.Red;
					for (int i = 0; i < currPersent; ++i) {
						if (Console.BackgroundColor == ConsoleColor.Red && i >= 47 / 3 && i < 47 / 3 * 2)
							Console.BackgroundColor = ConsoleColor.Yellow;
						else if (Console.BackgroundColor == ConsoleColor.Yellow && i >= 47 / 3 * 2)
							Console.BackgroundColor = ConsoleColor.Green;

						Console.Write(' ');
					}
					Console.BackgroundColor = ConsoleColor.Black;
					for (int i = currPersent; i < 47; ++i)
						Console.Write(' ');
				}

				void FillEarnedMoney() {
					Console.SetCursorPosition(3, 5);
					Console.Write(string.Format($"Earned money: {parking.EarnedMoney}"));
				}
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
				output.HorisontalLeft();
				break;
				case ConsoleKey.RightArrow:
				output.HorisontalRight();
				break;

				case ConsoleKey.Tab:
				if (output.GetMenuChoose() >= 1 && output.GetMenuChoose() <= 3)
					fieldController[output.GetMenuChoose() - 1].PressTab();
				break;

				case ConsoleKey.Backspace:
				if (output.GetMenuChoose() >= 1 && output.GetMenuChoose() <= 3)
					fieldController[output.GetMenuChoose() - 1].BackspaceLeterToSelectedTab();
				break;

				case ConsoleKey.Enter:
				try {
					if (output.GetMenuChoose() == 1 && fieldController[0].CurrTabId == fieldController[0].TabIdMax - 1) {
						if(StrTotype(fieldController[0].GetData(0)) != CarType.NONE)
						parking.AddCar(new Car(StrTotype(fieldController[0].GetData(0)), uint.Parse(fieldController[0].GetData(1))));
						fieldController[0].Clear();
					}
					else if (output.GetMenuChoose() == 2 && fieldController[1].CurrTabId == fieldController[1].TabIdMax - 1) {
						parking.DelCar(uint.Parse(fieldController[1].GetData(0)));
						fieldController[1].Clear();
					}
					else if (output.GetMenuChoose() == 3 && fieldController[2].CurrTabId == fieldController[2].TabIdMax - 1) {
						parking.DepositMoney(uint.Parse(fieldController[2].GetData(0)), uint.Parse(fieldController[2].GetData(1)));
						fieldController[2].Clear();
					}

					CarType StrTotype(string str) {
						str = str.ToLower();
						for (int i = 0; i <= 3; ++i)
							if (((CarType)(i)).ToString().ToLower() == str)
								return (CarType)i;
						return CarType.NONE;
					}
				}
				catch(Exception) { };
				break;

				default:
				if (output.GetMenuChoose() >= 1 && output.GetMenuChoose() <= 3)
					fieldController[output.GetMenuChoose() - 1].AddLeterToSelectedTab(key.KeyChar);
				break;
				}
			}
		}
	}
}
