using System;
using System.Collections.Generic;
using System.Threading;

namespace SSMO {
	class PizzaShop {
		const int CargoDeliverTime = 1;
		const int ClientEatTime = 5;  //[25%; 200%]
		const int MinClientsPerCompany = 1;
		const int MaxClientsPerCompany = 6;
		const int clientWisitChanse = 35;
		Coord HallSize = new Coord(51, 31);
		ushort tableCnt = (ushort)(Rand.rand.Next(5, 15));
		ushort tableCntReal = 0;
		ushort roomCnt = (ushort)(Rand.rand.Next(1, 7));

		DateTime lastTic = DateTime.Now.AddSeconds(CargoDeliverTime + 1);
		List<ClientsCompany> waitClients;
		Hall hall;
		Kitchen kitchen;
		byte menuChoose = 0, menuChoosePrevPos = 1, menuPuncts, horisontalPos = 0;

		public PizzaShop() {
			waitClients = new List<ClientsCompany>(8);
		}

		public void Launch() {
			Init();
			GenerateKitchen();
			GenerateHall();
			InitOutput();

			while (true) {
				if (lastTic.AddSeconds(1) <= DateTime.Now && waitClients.Count < 8 && Rand.rand.Next(1, 101) <= clientWisitChanse) 
					GenerateClients();

				ReactInput();

				hall.ClientsEat();
				CheckWaitClients();
				kitchen.PripaxatPovarov();
				Print();	

				if (lastTic.AddSeconds(1) <= DateTime.Now)
					lastTic = DateTime.Now;
				Thread.Sleep(100);
			}
		}

		void InitOutput() {
			InitWait();
			InitLog();
			InitInfoWindow();
			InitPeregorodka();
			InitMenu();

			void InitWait() {
				string pre = "Wait clients: ";
				Console.SetCursorPosition(hall.leftUpCorner.x, hall.leftUpCorner.y - 1);
				Console.BackgroundColor = ConsoleColor.Black;
				Console.ForegroundColor = ConsoleColor.White;
				Console.Write(pre);
			}
			void InitLog() {
				string str = "║" + new string(' ', Console.LargestWindowWidth - 6) + "║";
				for (int i = hall.rightDownCorner.y; i < Console.LargestWindowHeight - 3; ++i) {
					Console.SetCursorPosition(1, i);
					Console.Write(str);
				}
				Console.SetCursorPosition(1, hall.rightDownCorner.y);
				Console.Write("╔" + new string('═', Console.LargestWindowWidth - 6) + "╗");
				Console.SetCursorPosition(1, Console.LargestWindowHeight - 3);
				Console.Write("╚" + new string('═', Console.LargestWindowWidth - 6) + "╝");
			}
			void InitInfoWindow() {
				string str = "║" + new string(' ', Console.LargestWindowWidth - 7 - hall.rightDownCorner.x + hall.leftUpCorner.x) + "║";
				for (int i =1; i < hall.rightDownCorner.y; ++i) {
					Console.SetCursorPosition(hall.rightDownCorner.x + 1, i);
					Console.Write(str);
				}
				Console.SetCursorPosition(hall.rightDownCorner.x + 1, hall.leftUpCorner.y);
				Console.Write("╔" + new string('═', Console.LargestWindowWidth - 7 - hall.rightDownCorner.x + hall.leftUpCorner.x) + "╗");
				Console.SetCursorPosition(hall.rightDownCorner.x + 1, hall.rightDownCorner.y - 1);
				Console.Write("╚" + new string('═', Console.LargestWindowWidth - 7 - hall.rightDownCorner.x + hall.leftUpCorner.x) + "╝");
			}
			void InitPeregorodka() {
				for (int i = hall.leftUpCorner.y + 1; i < hall.rightDownCorner.y - 1; ++i) {
					Console.SetCursorPosition(Console.LargestWindowWidth - 16, i);
					Console.Write('║');
				}
				Console.SetCursorPosition(Console.LargestWindowWidth - 16, hall.leftUpCorner.y);
				Console.Write('╦');
				Console.SetCursorPosition(Console.LargestWindowWidth - 16, hall.rightDownCorner.y - 1);
				Console.Write('╩');
			}
			void InitMenu() {
				List <string> menuPuncts = new List<string>(){
					"Загально",
					"Доставка",
					"Склад",
					"Кухня",
					"Зала",
				};
				int table = this.tableCntReal;
				while(table-- != 0) {
					menuPuncts.Add("Стіл №" + (tableCntReal - table).ToString());
				}
				for(int i = 0; i < menuPuncts.Count; ++i) {
					Console.SetCursorPosition(Console.LargestWindowWidth - 13,i + hall.leftUpCorner.y + 1);
					Console.Write(menuPuncts[i]);
				}
				this.menuPuncts = (byte) (menuPuncts.Count);
			}
		}

		void Init() {
			Console.SetWindowSize(Console.LargestWindowWidth - 2, Console.LargestWindowHeight - 2);
			Console.CursorVisible = false;
			//if (!IngradientLoader.IsIngradientsExist())
			IngradientLoader.CreateIngradientFile();
			//if (!PizzaLoader.IsPizzaExist())
			PizzaLoader.CreatePizzaFile();
		}

		void GenerateClients() {
			int clientsCnt = Rand.rand.Next(MinClientsPerCompany, MaxClientsPerCompany + 1);
			ClientsCompany comp = new ClientsCompany();
			double timeMult = (double)(Rand.rand.Next(25, 200)) / 100;
			ushort eatTime = (ushort)(ClientEatTime * timeMult);
			comp.SetEatTime((ushort)(eatTime != 0? eatTime : 1));

			while(clientsCnt-- != 0)
				comp.AddClient(new Client(Human.GenerateName(), Human.GenerateName()));

			if(comp.Count != 1)
				Log.log.LogNewLine("New clients. " + comp.Count.ToString() + " humans.");
			else
				Log.log.LogNewLine("New client.  " + "1 human. ");

			var place = hall.GetFreePlace(comp.Count);
			if (place != null) {
				comp.PickPizzas(kitchen);
				comp.TakePlace(place);
				comp.MakeOrder(kitchen);
			}
			else {
				waitClients.Add(comp);
				Log.log.LogAddToLine(" Added to queue.");
			}
		}

		void CheckWaitClients() {
			foreach (var cli in waitClients) {
				var place = hall.GetFreePlace(cli.Count);
				if (place != null) {
					cli.PickPizzas(kitchen);
					cli.TakePlace(place);
					cli.MakeOrder(kitchen);
					waitClients.Remove(cli);
					break;
				}
			}
		}

		void GenerateKitchen() {
			kitchen = new Kitchen(new Cargo(0.80, 1.05, new DeliveryBasic(DELIVERY_TYPE.All, 0.90, CargoDeliverTime, 1.53)));

			kitchen.AddStaff(new KitchenStaff(new Staff(Human.GenerateName(), "Povar Middle", Human.GenerateName(), Human.GenerateName()), 2.10, 1500));
			kitchen.AddStaff(new KitchenStaff(new Staff(Human.GenerateName(), "Povar Junior", Human.GenerateName(), Human.GenerateName()), 0.90, 150));
			kitchen.AddStaff(new KitchenStaff(new Staff(Human.GenerateName(), "Povar Junior", Human.GenerateName(), Human.GenerateName()), 0.90, 200));
			kitchen.AddStaff(new KitchenStaff(new Staff(Human.GenerateName(), "Povar Junior", Human.GenerateName(), Human.GenerateName()), 0.90, 200));
			kitchen.AddStaff(new KitchenStaff(new Staff(Human.GenerateName(), "Povar Junior", Human.GenerateName(), Human.GenerateName()), 0.90, 100));
			kitchen.AddStaff(new KitchenStaff(new Staff(Human.GenerateName(), "Povar Junior", Human.GenerateName(), Human.GenerateName()), 0.90, 100));

			kitchen.WeeklyDeliver();
		}

		void GenerateHall() {
			hall = new Hall(new Coord(1, 1), HallSize);
			hall.SetWalls(GenerateRoom());
			hall.PrintWalls();
		}

		string[] GenerateRoom() {
			int sizex = hall.rightDownCorner.x - hall.leftUpCorner.x, sizey = hall.rightDownCorner.y - hall.leftUpCorner.y;

			System.Text.StringBuilder[] wall = new System.Text.StringBuilder[sizey];
			for (var i = 0; i < wall.Length; ++i)
				wall[i] = new System.Text.StringBuilder("#" + new String(' ', sizex - 2) + "#");
			wall[wall.Length - 5] = new System.Text.StringBuilder(new String('#', sizex));
			wall[0] = new System.Text.StringBuilder(new String('#', sizex));
			wall[wall.Length - 1] = new System.Text.StringBuilder(new String('#', sizex));

			int roomCnt = this.roomCnt;

			while (roomCnt-- != 0) {
				ushort x = 0, y = 0;
				bool vertical = Rand.rand.Next(0, 2) == 1 ? true : false;
				int times = 0;
				do {
					if (times++ >= 1000)
						break;
					x = (ushort)Rand.rand.Next(0, wall[0].Length);
					y = (ushort)Rand.rand.Next(0, wall.Length);
				} while (wall[y][x] == '#' || wall[y + 1][x] == '#' || wall[y - 1][x] == '#' || wall[y][x + 1] == '#' || wall[y][x - 1] == '#' || wall[y + 2][x] == '#' || wall[y - 2][x] == '#' || wall[y][x + 2] == '#' || wall[y][x - 2] == '#' || wall[y + 3][x] == '#' || wall[y - 3][x] == '#' || wall[y][x + 3] == '#' || wall[y][x - 3] == '#');
				if (times >= 1000)
					break;
				PlaceToEnd(x, y);
				if(vertical)
					wall[y][x] = '|';
				else
					wall[y][x] = '-';

				void PlaceToEnd(ushort X, ushort Y) {
					if(wall[Y][X] == '-' || wall[Y][X] == '|') {
						wall[Y][X] = '#';
						return;
					}
					if (wall[Y][X] == '#') {
						if (Y == sizey - 5) {
							if (Rand.rand.Next(0, 2) == 1)
								wall[Y][X - 1] = '-';
							else
								wall[Y][X + 1] = '-';
						}
						else /*if(X != 0 && Y != 0 && X != sizex && Y != sizey)*/ {
							int xx = X, yy = Y;
							if (vertical) {
								if (xx - 1 < 0)
									++xx;
								else
									--xx;
							}
							else {
								if (yy - 1 < 0)
									++yy;
								else
									--yy;
							}
							if(wall[yy][xx] == '#')
								wall[yy][xx] = vertical?'-':'|';
						}
						return;
					}

					wall[Y][X] = '#';
					if (vertical) {
						PlaceToEnd(X, (ushort)(Y + 1));
						PlaceToEnd(X, (ushort)(Y - 1));
					}
					else {
						PlaceToEnd((ushort)(X + 1), Y);
						PlaceToEnd((ushort)(X - 1), Y);
					}
				}
			}

			void PlaceKitchenDoor(){
				foreach (var i in wall[wall.Length - 5].ToString())
					if (i == '-')
						return;
				wall[wall.Length - 5][1] = '-';
			};
			PlaceKitchenDoor();

			void PlaceSingleTable() {
				ushort x = 0, y = 0;

				int times = 0;
				do {
					if (times++ >= 1000)
						break;
					x = (ushort)Rand.rand.Next(2, wall[0].Length - 2);
					y = (ushort)Rand.rand.Next(2, wall.Length - 7);
				} while (wall[y][x] == '#' || wall[y][x] == '|' || wall[y][x] == '-' ||
				wall[y + 1][x] == '#' || wall[y - 1][x] == '#' || wall[y][x + 1] == '#' || wall[y][x - 1] == '#' ||
				wall[y + 2][x] == '#' || wall[y - 2][x] == '#' || wall[y][x + 2] == '#' || wall[y][x - 2] == '#' ||
				wall[y + 1][x] == '|' || wall[y - 1][x] == '|' || wall[y][x + 1] == '|' || wall[y][x - 1] == '|' ||
				wall[y + 2][x] == '|' || wall[y - 2][x] == '|' || wall[y][x + 2] == '|' || wall[y][x - 2] == '|' ||
				wall[y + 1][x] == '-' || wall[y - 1][x] == '-' || wall[y][x + 1] == '-' || wall[y][x - 1] == '-' ||
				wall[y + 2][x] == '-' || wall[y - 2][x] == '-' || wall[y][x + 2] == '-' || wall[y][x - 2] == '-' ||
				hall.NearTable(new Coord(x, y)));
				if (times++ >= 1000)
					return;
				Place pl = new Place(new Coord(x, y));

				ushort chairs = (ushort)Rand.rand.Next(1, 5);
				bool up = false, down = false, left = false, right = false;
				while (chairs-- != 0) {
					REPEAT:
					switch (Rand.rand.Next(0, 4)) {
					case 0:
					if (up == false) {
						pl.AddChair(new Chair(new Coord(0, -1)));
						up = true;
					}
					else
						goto REPEAT;
					break;
					case 1:
					if (down == false) {
						pl.AddChair(new Chair(new Coord(0, 1)));
						down = true;
					}
					else
						goto REPEAT;
					break;
					case 2:
					if (left == false) {
						pl.AddChair(new Chair(new Coord(-1, 0)));
						left = true;
					}
					else
						goto REPEAT;
					break;
					case 3:
					if (right == false) {
						pl.AddChair(new Chair(new Coord(1, 0)));
						right = true;
					}
					else
						goto REPEAT;
					break;
					}
				}

				hall.AddPlace(pl);
				++tableCntReal;
			}
			void PlaceMultiTable() {
				short x = 0, y = 0;

				int times = 0;
				do {
					if (times++ >= 1000)
						break;
					x = (short)Rand.rand.Next(2, wall[0].Length - 2);
					y = (short)Rand.rand.Next(2, wall.Length - 7);
				} while (wall[y][x] == '#' || wall[y][x] == '|' || wall[y][x] == '-' ||
				wall[y + 1][x] == '#' || wall[y - 1][x] == '#' || wall[y][x + 1] == '#' || wall[y][x - 1] == '#' ||
				wall[y + 2][x] == '#' || wall[y - 2][x] == '#' || wall[y][x + 2] == '#' || wall[y][x - 2] == '#' ||
				wall[y + 3][x] == '#' || wall[y - 3][x] == '#' || wall[y][x + 3] == '#' || wall[y][x - 3] == '#' ||
				wall[y + 1][x] == '|' || wall[y - 1][x] == '|' || wall[y][x + 1] == '|' || wall[y][x - 1] == '|' ||
				wall[y + 2][x] == '|' || wall[y - 2][x] == '|' || wall[y][x + 2] == '|' || wall[y][x - 2] == '|' ||
				wall[y + 3][x] == '|' || wall[y - 3][x] == '|' || wall[y][x + 3] == '|' || wall[y][x - 3] == '|' ||
				wall[y + 1][x] == '-' || wall[y - 1][x] == '-' || wall[y][x + 1] == '-' || wall[y][x - 1] == '-' ||
				wall[y + 2][x] == '-' || wall[y - 2][x] == '-' || wall[y][x + 2] == '-' || wall[y][x - 2] == '-' ||
				wall[y + 3][x] == '-' || wall[y - 3][x] == '-' || wall[y][x + 3] == '-' || wall[y][x - 3] == '-' ||
				hall.NearTable(new Coord(x, y)));
				if (times++ >= 1000)
					return;
				ManyPlaces pl = new ManyPlaces(new Coord(x, y));
				byte type = (byte) Rand.rand.Next(0, 3);
				if (type == 0) {
					pl.AddTable(new Coord(0,1));
					if(Rand.rand.Next(0, 2) == 1)
						pl.AddTable(new Coord(0, - 1));
				}
				else if (type == 1) {
					pl.AddTable(new Coord(-1, 0));
					if (Rand.rand.Next(0, 2) == 1)
						pl.AddTable(new Coord(1, 0));
				}
				else if (type == 2) {
					pl.AddTable(new Coord(-1, 0));
					if (Rand.rand.Next(0, 2) == 1)
						pl.AddTable(new Coord(0, Rand.rand.Next(0, 2) == 1?1:-1));
				}

				ushort chairs = (ushort)Rand.rand.Next(3, 7);
				times = 0;
				while (chairs-- != 0) {
					do {
						if (++times >= 1000)
							break;
						x = (short)Rand.rand.Next(-3, 4);
						y = (short)Rand.rand.Next(-3, 4);
					} while (!(pl.FreePlace(new Coord(x,y)) && pl.NearTable(new Coord(x, y)) && wall[pl.refPos.y + y][pl.refPos.x + x] == ' '));
					if (++times >= 1000)
						break;
					pl.AddChair(new Chair(new Coord(x, y)));
				}

				hall.AddPlace(pl);
				++tableCntReal;
			}
			void PlaceMaxTableTable() {
				short x = 0, y = 0;

				int times = 0;
				do {
					if (times++ >= 1000)
						break;
					x = (short)Rand.rand.Next(2, wall[0].Length - 2);
					y = (short)Rand.rand.Next(2, wall.Length - 7);
				} while (wall[y][x] == '#' || wall[y][x] == '|' || wall[y][x] == '-' ||
				wall[y + 1][x] == '#' || wall[y - 1][x] == '#' || wall[y][x + 1] == '#' || wall[y][x - 1] == '#' ||
				wall[y + 2][x] == '#' || wall[y - 2][x] == '#' || wall[y][x + 2] == '#' || wall[y][x - 2] == '#' ||
				wall[y + 3][x] == '#' || wall[y - 3][x] == '#' || wall[y][x + 3] == '#' || wall[y][x - 3] == '#' ||
				wall[y + 1][x] == '|' || wall[y - 1][x] == '|' || wall[y][x + 1] == '|' || wall[y][x - 1] == '|' ||
				wall[y + 2][x] == '|' || wall[y - 2][x] == '|' || wall[y][x + 2] == '|' || wall[y][x - 2] == '|' ||
				wall[y + 3][x] == '|' || wall[y - 3][x] == '|' || wall[y][x + 3] == '|' || wall[y][x - 3] == '|' ||
				wall[y + 1][x] == '-' || wall[y - 1][x] == '-' || wall[y][x + 1] == '-' || wall[y][x - 1] == '-' ||
				wall[y + 2][x] == '-' || wall[y - 2][x] == '-' || wall[y][x + 2] == '-' || wall[y][x - 2] == '-' ||
				wall[y + 3][x] == '-' || wall[y - 3][x] == '-' || wall[y][x + 3] == '-' || wall[y][x - 3] == '-' ||
				hall.NearTable(new Coord(x, y)));
				if (times++ >= 1000)
					return;
				ManyPlaces pl = new ManyPlaces(new Coord(x, y));
				pl.AddTable(new Coord(0, 1));
				pl.AddTable(new Coord(0, -1));

				ushort chairs = MaxClientsPerCompany + 1;
				times = 0;
				while (chairs-- != 0) {
					do {
						if (++times >= 1000)
							break;
						x = (short)Rand.rand.Next(-3, 4);
						y = (short)Rand.rand.Next(-3, 4);
					} while (!(pl.FreePlace(new Coord(x, y)) && pl.NearTable(new Coord(x, y)) && wall[pl.refPos.y + y][pl.refPos.x + x] == ' '));
					if (++times >= 1000)
						break;
					pl.AddChair(new Chair(new Coord(x, y)));
				}

				hall.AddPlace(pl);
				++tableCntReal;
			}


			int tableCnt = this.tableCnt - 1;
			while (tableCnt-- != 0) {
				if (Rand.rand.Next(0, 3) == 1)
					PlaceSingleTable();
				else
					PlaceMultiTable();
			}
			PlaceMaxTableTable();

			string[] res = new string[wall.Length];
			for (var i = 0; i < res.Length; ++i)
				res[i] = wall[i].ToString();
			return res;
		}

		ConsoleKeyInfo? inputNull;
		ConsoleKeyInfo input;
		void ReactInput() {
			inputNull = Input();
			if (inputNull.HasValue) {
				input = inputNull.Value;
				if (input.Key == ConsoleKey.UpArrow) {
					if (menuChoose == 0)
						menuChoose = (byte)(menuPuncts - 1);
					else
					--menuChoose;
				}
				else if (input.Key == ConsoleKey.DownArrow) {
					++menuChoose;
					if (menuChoose >= menuPuncts)
						menuChoose = 0;
				}
				else if (input.Key == ConsoleKey.LeftArrow || input.Key == ConsoleKey.RightArrow) {
					horisontalPos = (byte) ((horisontalPos == 0) ? 1 : 0);
				}
			}

			ConsoleKeyInfo? Input() {
				if (Console.KeyAvailable) {
					Console.SetCursorPosition(0, 0);
					return Console.ReadKey();
				}
				return null;
			}
		}

		void Print() {
			hall.Print();
			PrintWaitClients();
			PrintTime();
			PrintArrow();
			PrintWindowInfo();
			Log.log.PrintLog(new Coord(2, hall.rightDownCorner.y + 1), (byte)(Console.LargestWindowHeight - 5 - hall.rightDownCorner.y), (byte)(Console.LargestWindowWidth - 6));
			
			void PrintArrow() {
				if(menuChoose != menuChoosePrevPos) {
					Console.SetCursorPosition(Console.LargestWindowWidth - 15, hall.leftUpCorner.y + 1 + menuChoosePrevPos);
					Console.Write(' ');
					menuChoosePrevPos = menuChoose;
					Console.SetCursorPosition(Console.LargestWindowWidth - 15, hall.leftUpCorner.y + 1 + menuChoose);
					Console.ForegroundColor = ConsoleColor.Yellow;
					Console.Write('→');

					string space = new string(' ', Console.LargestWindowWidth - hall.rightDownCorner.x - 18);
					for (int i = hall.leftUpCorner.y + 1; i < hall.rightDownCorner.y - 1; ++i) {
						Console.SetCursorPosition(hall.rightDownCorner.x + 2, i);
						Console.WriteLine(space);
					}
				}
			}
			void PrintWaitClients() {
				Coord pos = new Coord(hall.leftUpCorner.x + "Wait clients: ".Length, hall.leftUpCorner.y - 1);
				ConsoleColor[] color = new ConsoleColor[waitClients.Capacity];
				for (ushort i = 0; i < color.Length; ++i)
					if (i < color.Length / 3)
						color[i] = ConsoleColor.Green;
					else if (i > color.Length / 3 * 2)
						color[i] = ConsoleColor.Red;
					else
						color[i] = ConsoleColor.Yellow;

				Console.SetCursorPosition(pos.x, pos.y);
				for (ushort i = 0; i < color.Length; ++i) {
					if (i < waitClients.Count)
						Console.BackgroundColor = color[i];
					else
						Console.BackgroundColor = ConsoleColor.Black;
					Console.Write(' ');
				}
			}
			void PrintTime() {
				Console.SetCursorPosition(hall.rightDownCorner.x - DateTime.Now.ToLongTimeString().Length, hall.leftUpCorner.x - 1);
				Console.BackgroundColor = ConsoleColor.Black;
				Console.ForegroundColor = ConsoleColor.White;
				Console.WriteLine(lastTic.ToLongTimeString());
			}
		}

		void PrintWindowInfo() {
			Console.ForegroundColor = ConsoleColor.White;
			List<string> content = new List<string>(10);

			if(menuChoose == 0)
				FillWithPizzaShop();
			else if (menuChoose == 1)
				FillWithDelivery();
			else if (menuChoose == 2)
				FillWithCargo();
			else if (menuChoose == 3)
				FillWithKitchen();
			else if (menuChoose == 4)
				FillWithHall();
			else
				TableInfo(menuChoose - 5);

			if ((menuChoose == 1 || menuChoose == 2) && horisontalPos == 1 && content.Count > hall.rightDownCorner.y - hall.leftUpCorner.y - 5) {
				if (menuChoose == 2) {
					Console.SetCursorPosition(hall.rightDownCorner.x + 2, hall.rightDownCorner.y - hall.leftUpCorner.y - 5 - hall.rightDownCorner.y + hall.leftUpCorner.y + 7);
					Console.WriteLine(content[5]);
					Console.SetCursorPosition(hall.rightDownCorner.x + 2, hall.rightDownCorner.y - hall.leftUpCorner.y - 4 - hall.rightDownCorner.y + hall.leftUpCorner.y + 7);
					Console.WriteLine(content[6]);
				}
				else {
					Console.SetCursorPosition(hall.rightDownCorner.x + 2, hall.rightDownCorner.y - hall.leftUpCorner.y - 5 - hall.rightDownCorner.y + hall.leftUpCorner.y + 7);
					Console.WriteLine(content[7]);
					Console.SetCursorPosition(hall.rightDownCorner.x + 2, hall.rightDownCorner.y - hall.leftUpCorner.y - 4 - hall.rightDownCorner.y + hall.leftUpCorner.y + 7);
					Console.WriteLine(content[8]);
				}
				for (int i = hall.rightDownCorner.y - hall.leftUpCorner.y - 3; i < content.Count; ++i) {
					Console.SetCursorPosition(hall.rightDownCorner.x + 2, i - hall.rightDownCorner.y + hall.leftUpCorner.y + 7);
					Console.WriteLine(content[i]);
				}
			}
			else {
				for (int i = 0; i < content.Count && hall.leftUpCorner.y + 2 + i < hall.rightDownCorner.y; ++i) {
					Console.SetCursorPosition(hall.rightDownCorner.x + 2, hall.leftUpCorner.y + 1 + i);
					Console.WriteLine(content[i]);
				}
			}

			void FillWithPizzaShop() {
				content.Add(string.Format("Money: {0:0.##}", Money.value));
			}
			void FillWithDelivery() {
				string space = new string(' ', Console.LargestWindowWidth - hall.rightDownCorner.x - 18);
				for (int i = hall.leftUpCorner.y + 1; i < hall.rightDownCorner.y - 1; ++i) {
					Console.SetCursorPosition(hall.rightDownCorner.x + 2, i);
					Console.WriteLine(space);
				}

				DeliveryBasic delivery = kitchen.GetCargo().GetDelivery();

				content.Add(string.Format("Money: {0:0.##}", delivery.EarnedMoney));
				content.Add(string.Format("QualityMod: {0}", delivery.QualityModifier));
				content.Add(string.Format("SellMod: {0}", delivery.CostMod));
				content.Add(string.Format("Type: {0}", delivery.DeliveryType));
				content.Add(string.Format("Seconds: {0}", delivery.SecondsToDeliver));

				if(delivery.GetToOrder().Count != 0) {
					content.Add("");
					content.Add("In order: ");
					content.Add(string.Format("{0,-20} ║ {1,-7} ║ {2,-14} ║ {3,-7} ║ {4,-20}",
							"Name",
							"MassGr",
							"PriceSell(Buy)",
							"Quality",
							"Description"
							));
					content.Add(new string('═', 21) + "╬" + new string('═', 9) + "╬" + new string('═', 16) + "╬" + new string('═', 9) + "╬" + new string('═', 27));
					foreach (var i in delivery.GetToOrder()) {
						content.Add(string.Format("{0,-20} ║ {1,-7} ║ {2,-14} ║ {3,-7} ║ {4,-20}",
							i.Name, 
							i.MassGr, 
							i.PriceSell.ToString() + "(" + i.PriceBuy.ToString() + ")",
							i.Quality.current,
							i.Description
							));
					}
				}
				if (delivery.GetToDeliver().Count != 0) {
					content.Add("");
					content.Add("To deliver: ");
					content.Add(string.Format("{0,-20} ║ {1,-7} ║ {2,-14} ║ {3,-7} ║ {4,-20}",
							"Name",
							"MassGr",
							"PriceSell(Buy)",
							"Quality",
							"Description"
							));
					content.Add(new string('═', 21) + "╬" + new string('═', 9) + "╬" + new string('═', 16) + "╬" + new string('═', 9) + "╬" + new string('═', 27));
					foreach (var i in delivery.GetToDeliver()) {
						content.Add(string.Format("{0,-20} ║ {1,-7} ║ {2,-14} ║ {3,-7} ║ {4,-20}",
							i.Name,
							i.MassGr,
							i.PriceSell.ToString() + " (" + i.PriceBuy.ToString() + ")",
							i.Quality.current,
							i.Description
							));
					}
				}

			}
			void FillWithCargo() {
				string space = new string(' ', Console.LargestWindowWidth - hall.rightDownCorner.x - 18);
				for (int i = hall.leftUpCorner.y + 1; i < hall.rightDownCorner.y - 1; ++i) {
					Console.SetCursorPosition(hall.rightDownCorner.x + 2, i);
					Console.WriteLine(space);
				}

				Cargo cargo = kitchen.GetCargo();

				content.Add(string.Format("Money: {0:0.##}", cargo.EarnedMoney));
				content.Add(string.Format("QualityMod: {0}", cargo.QualityMod));
				content.Add(string.Format("SellMod: {0}", cargo.SellMod));

				List<IngradientOnCargo> list = cargo.GetIngradients();
				if (list.Count != 0) {
					content.Add("");
					content.Add("");
					content.Add(string.Format("{0,-20} ║ {1,-7} ║ {2,-14} ║ {3,-7} ║ {4,-20}",
							"Name",
							"MassGr",
							"PriceSell(Buy)",
							"Quality",
							"Description"
							));
					content.Add(new string('═', 21) + "╬" + new string('═', 9) + "╬" + new string('═', 16) + "╬" + new string('═', 9) + "╬" + new string('═', 27));
					foreach (var i in list) {
						content.Add(string.Format("{0,-20} ║ {1,-7} ║ {2,-14} ║ {3,-7} ║ {4,-20}",
							i.Name,
							i.MassGr,
							(i.PriceSell * cargo.SellMod).ToString() + "(" + i.PriceSell.ToString() + ")",
							i.Quality.current * cargo.QualityMod,
							i.Description
							));
					}
				}
			}
			void FillWithKitchen() {
				content.Add(string.Format("{0,-11} ║ {1,-13} ║ {2,-11} ║ {3,-15} ║ {4,-4} ║ {5,-4}", "Name", "Clicuxa", "Surname", "Posada", "QMod", "Salary"));
				content.Add(new string('═', 12) + "╬" + new string('═', 15) + "╬" + new string('═', 13) + "╬" + new string('═', 17) + "╬" + new string('═', 6) + "╬" + new string('═', 7));
				foreach (var i in kitchen.GetStaff()) {
					content.Add(string.Format("{0,-11} ║ {1,-13} ║ {2,-11} ║ {3,-15} ║ {4,-4} ║ {5,-4}", i.Name, "\"" + i.Clicuxa + "\"", i.Surname, i.Posada, i.QualityMod, i.Salary));
					if (!i.IsReady)
						content[content.Count - 1] += " *";
					else
						content[content.Count - 1] += "  ";
				}
				content.Add("");
				content.Add("");
				content.Add("Orders in queue: " + kitchen.OrderCnt().ToString());
				content.Add("Orders cooked: " + kitchen.CookedCnt().ToString());
				content.Add("");
				content.Add("");
				content.Add("Salary: " + kitchen.GetSalary().ToString());
				content.Add("Seconds For Salary: " + kitchen.SalarySeconds().ToString());
				content.Add("Last salary: " + kitchen.WhenLastSalary().ToLongTimeString());
			}
			void FillWithHall() {
				content.Add(string.Format("Rooms: {0}", roomCnt + 2));
				content.Add(string.Format("Places: {0}", tableCntReal));
			}
			void TableInfo(int id) {
				string space = new string(' ', Console.LargestWindowWidth - hall.rightDownCorner.x - 18);
				for (int i = hall.leftUpCorner.y + 1; i < hall.rightDownCorner.y - 1; ++i) {
					Console.SetCursorPosition(hall.rightDownCorner.x + 2, i);
					Console.WriteLine(space);
				}

				Place place = hall.GetPlaceById(id);
				content.Add("Chairs: "+ (place.isFree?"0": place.client.Count.ToString()) + "/" + place.ChairsCnt.ToString());
				content.Add("");
				content.Add("");

				if (place.isFree)
					content.Add("Free");
				else {
					content.Add(string.Format("{0,-11} ║ {1,-13}", "Name", "Surname"));
					content.Add(new string('═', 12) + "╬" + new string('═', 15));
					foreach (Client i in place.client)
						content.Add(string.Format("{0,-11} ║ {1,-13}", i.Name, i.Surname));
					content.Add("");
					content.Add("");

					content.Add("EatTime: \t" + place.client.eatTime.ToString());
					content.Add("Cafe: \t" + place.client.inCafe.ToLongTimeString());
					content.Add("Table: \t" + place.client.inTable.ToLongTimeString());
					content.Add("MakeOrder: " + place.client.makeOrder.ToLongTimeString());
					content.Add("GetOrder: \t" + place.client.getOrder.ToLongTimeString());
					content.Add("");
					content.Add("");

					try {
						if (place.client.GetWhatOrder().Count != 0) {
							content.Add(string.Format("{0,-12} ║ {1,-13} ║ {2,-7} ║ {3,-7}", "Name", "Quality", "Price", "MassGr"));
							content.Add(new string('═', 13) + "╬" + new string('═', 15) + "╬" + new string('═', 9) + "╬" + new string('═', 9));
							foreach (var i in place.client.GetWhatOrder())
								content.Add(string.Format("{0,-12} ║ {1,-13} ║ {2,-7:0.##} ║ {3,-7}", i.Name, i.Quality, i.Price, i.MassGr));
							
						}
					}
					catch (Exception) {
					}
				}
			}
		}
	}
}
