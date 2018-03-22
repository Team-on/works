using System;

namespace BookShop {
	static class Validator {
		static public bool IsEmail(string str) {
			bool sob = false;
			foreach(char i in str) {
				if (i == '@')
					sob = true;
				if (sob && i == '.')
					return true;
			}
			return false;
		}
	}


	class UiConsoleBookShop {
		BookShop shop;
		
		Coord downLeftCorner = new Coord(150, 45);
		ActiveElementDraw head;

		public UiConsoleBookShop() {

			string verticalLine = "|\n";
			for (byte i = 0; i < 44; ++i)
				verticalLine += "|\n";
			shop = new BookShop();
			head = new ActiveElementDraw(
				new ActiveStaticElement("Main", new Coord(2, 1)),
				new ActiveInputElement("Find: " + new string(' ', 75), new Coord(21, 1), new Coord(6, 0), 74),
				new ActiveDoubleElement("Login/Register", new Coord(134, 1), "Logout", new Coord(134, 1)),
				new StaticElement(new string('_', downLeftCorner.x), new Coord(0, 0)),
				new StaticElement(new string('_', downLeftCorner.x), new Coord(0, downLeftCorner.y)),
				new StaticElement(new string('-', downLeftCorner.x - 2), new Coord(1, 2)),
				new StaticElement(verticalLine, new Coord(0, 1)),
				new StaticElement(verticalLine, new Coord(downLeftCorner.x, 1)),
				new StaticElement("|", new Coord(7, 1)),

				new StaticElement("|", new Coord(20, 1)),
				new StaticElement("|", new Coord(102, 1)),

				new StaticElement("|", new Coord(133, 1)),
				new StaticElement("|", new Coord(148, 1))
				);
		}

		public void Launch() {
			Console.SetWindowSize(Console.LargestWindowWidth, Console.LargestWindowHeight);
			PrintHelloScreen();
			//System.Threading.Thread.Sleep(1500);
			Console.Clear();
			MainScreen();
			Console.Clear();
		}

		ConsoleKeyInfo InbisibleInput() {
			Console.SetCursorPosition(103, 1);
			ConsoleColor prev = Console.ForegroundColor;
			Console.ForegroundColor = Console.BackgroundColor;
			ConsoleKeyInfo rez = Console.ReadKey();
			Console.ForegroundColor = prev;
			return rez;
		}

		void PrintHelloScreen() {
			Console.Write("\n\n\n\n\n\n\n\n\n" + @"
          .-. .-')                     ^,,^   .-. .-')         .-')      ('-. .-.                   _ (`-.  
          \  ( OO )                   ( oO )  \  ( OO )       ( OO ).   ( OO )  /                  ( (OO  ) 
           ;-----.\    .-'),-----.    ,-----.  ,--. ,--.      (_)---\_)  ,--. ,--.   .-'),-----.   _.`     \ 
           | .-.  |   ( OO'  .-.  '  '  .-.  ' |  .'   /      /    _ |   |  | |  |  ( OO'  .-.  ' (__...--'' 
           | '-' /_)  /   |  | |  |  |  | |  | |      /,      \  :` `.   |   .|  |  /   |  | |  |  |  /  | | 
           | .-. `.   \_) |  |\|  |  |  | |  | |     ' _)      '..`''.)  |       |  \_) |  |\|  |  |  |_.' | 
           | |  \  |    \ |  | |  |  |  | |  | |  .   \       .-._)   \  |  .-.  |    \ |  | |  |  |  .___.' 
           | '--'  /     `'  '-'  '  '  '-'  ' |  |\   \      \       /  |  | |  |     `'  '-'  '  |  |      
           `------'       `-------'  `-------' `--' '--'       `-----'    `--' `-'       `------'   `-'     



											 ____  ____  ____ 
											||H ||||i ||||! ||
											||__||||__||||__||
											|/__\||/__\||/__\|");
		}

		void MainScreen() {
			byte choose;
			head.InitStatic();
			while (true) {
				head.Print();
				choose = head.Input(InbisibleInput());
				if (choose == 255)
					continue;

				switch (choose) {
				//Main
				case 0:
				break;
				//Find
				case 1:
				break;
				//Register/Login    Logout
				case 2:
				if (head.GetDoubleElementContrain(2)) {
					shop.Logoff();
					head.ChangeDoubleElementContrain(2);
				}
				else
					RegisterAndLoginScreen();
				break;
				}
			}

		}

		void BooksListScreen() {

		}

		void BookInfoScreen() {

		}

		void RegisterAndLoginScreen() {
			byte choose;
			ActiveElementDraw loginWindow;

			{
				loginWindow = new ActiveElementDraw(head,

					new StaticElement(" ::Login::", new Coord(10, 5)),
					new ActiveInputElement("Login:" + new string(' ', 16), new Coord(10, 7), new Coord(7, 0), 15),
					new ActiveInputElement("Pass:" + new string(' ', 34), new Coord(10, 8), new Coord(7, 0), 32),
					new ActiveStaticElement("-------\n|Login|\n-------", new Coord(10, 10)),


					new StaticElement(@"╔══╗╔═══╗
║╔╗║║╔═╗║
║║║║║╚═╝║
║║║║║╔╗╔╝
║╚╝║║║║║
╚══╝╚╝╚╝", new Coord((short)(downLeftCorner.x / 2 - 10), (short)(downLeftCorner.y / 2 - 5))),

					new StaticElement(" ::Register::", new Coord((short)(downLeftCorner.x / 2 + 10), 5)),
					new ActiveInputElementAllSymbols("E-mail: " + new string(' ', 31), new Coord((short)(downLeftCorner.x / 2 + 10), 7), new Coord(8, 0), 32),
					new ActiveInputElement("Login: " + new string(' ', 17), new Coord((short)(downLeftCorner.x / 2 + 10), 8), new Coord(8, 0), 16),
					new ActiveInputElement("Pass: " + new string(' ', 34), new Coord((short)(downLeftCorner.x / 2 + 10), 9), new Coord(8, 0), 32),

					new ActiveInputElement("Name:    " + new string(' ', 16), new Coord((short)(downLeftCorner.x / 2 + 10), 11), new Coord((short)"Name:    ".Length, 0), 16),
					new ActiveInputElement("Surname: " + new string(' ', 16), new Coord((short)(downLeftCorner.x / 2 + 10), 12), new Coord((short)"Surname: ".Length, 0), 16),
					new ActiveInputElement("Phone:   " + new string(' ', 13), new Coord((short)(downLeftCorner.x / 2 + 10), 13), new Coord((short)"Phone:   ".Length, 0), 10),

					new ActiveStaticElement("----------\n|Register|\n----------", new Coord((short)(downLeftCorner.x / 2 + 10), 15))
					);
			}

			loginWindow.InitStatic();
			while (true) {
				loginWindow.Print();
				choose = loginWindow.Input(InbisibleInput());
				if (choose == 255)
					continue;

				switch (choose) {
				//Main
				case 0:
				goto REGISTER_AND_LOGIN_RETURN;
				//Find
				case 1:
				break;
				//Register/Login    Logout
				case 2:
				break;
				//Login
				case 16:
				if (shop.Login(loginWindow.GetInputValue(14), LoginPass.Hasher(loginWindow.GetInputValue(15))) != null) {
					head.ChangeDoubleElementContrain(2);
					goto REGISTER_AND_LOGIN_RETURN;
				}
				break;
				//Register
				case 25:
				if (loginWindow.GetInputValue(22).Length == 0 || loginWindow.GetInputValue(23).Length == 0 
					|| loginWindow.GetInputValue(24).Length == 0 || loginWindow.GetInputValue(21).Length == 0 
					|| loginWindow.GetInputValue(20).Length == 0 || loginWindow.GetInputValue(19).Length == 0
					)
					break;
				if (!Validator.IsEmail(loginWindow.GetInputValue(19)))
					break;
				if (shop.CreateUser(new Person(loginWindow.GetInputValue(22), loginWindow.GetInputValue(23), loginWindow.GetInputValue(24)),
					loginWindow.GetInputValue(20), LoginPass.Hasher(loginWindow.GetInputValue(21)), loginWindow.GetInputValue(19))) {
						shop.Login(loginWindow.GetInputValue(20), LoginPass.Hasher(loginWindow.GetInputValue(21)));
						head.ChangeDoubleElementContrain(2);
						goto REGISTER_AND_LOGIN_RETURN;
				}
				
				break;
				default:
				//Console.Write(choose);
				break;
				}
			}

		REGISTER_AND_LOGIN_RETURN:
			loginWindow.ClearScreen();
			head.InitStatic();
		}
	}
}
