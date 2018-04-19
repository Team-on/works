using System;
using System.Collections.Generic;
using System.IO;

using TeamCommander.Elements;
using TeamCommander.Support;
using TeamCommander.Output;

namespace TeamCommander {
	interface CommanderWindow {
		Coord leftUpCorner { get; }
		Coord rightDownCorner { get;}
		ElementsDirector director { get; }

		void Print();
	}

	class CommanderWindowAllInfo : CommanderWindow {
		public Coord leftUpCorner { get; private set; }
		public Coord rightDownCorner { get; private set; }
		public ElementsDirector director { get; private set; }

		DriveInfo[] drives = DriveInfo.GetDrives();
		Element[] files;

		public CommanderWindowAllInfo(ElementsDirector Director, Coord LeftUpCorner, Coord RightDownCorner) {
			if (RightDownCorner.y - LeftUpCorner.y - 6 <= 0)
				throw new CommanderWindowException();

			director = Director;
			leftUpCorner = LeftUpCorner;
			rightDownCorner = RightDownCorner;
			++leftUpCorner.x;
			++leftUpCorner.y;
			--rightDownCorner.x;
			--rightDownCorner.y;

			files = new Element[RightDownCorner.y - LeftUpCorner.y - 3];
			for (ushort i = 0; i < files.Length; ++i) {
				files[i] = new Elements.ElementText("file " + i.ToString(), new Coord(LeftUpCorner.x, LeftUpCorner.y + i), (ushort)(i + 5));
				director.AddElement(files[i]);
			}
		}

		public void Print() {
		}

		void AddDrivesLine() {

		}


	}

    class Commander{
		bool isLaunch;
		readonly Coord minScreenSize = new Coord(108, 26);
		readonly Coord screenSizeDivider = new Coord(150, 200);
		//readonly Coord screenSizeDivider = new Coord(100, 100);
		//readonly Coord screenSizeDivider = new Coord(150, 100);
		//readonly Coord screenSizeDivider = new Coord(100, 200);

		Output.Output screen;
		//menu Time
		ElementsDirector headDirector;
		//Console hotkeysList
		ElementsDirector downDirector;
		//LeftWindow
		ElementsDirector leftDirector;
		//RightWindow
		ElementsDirector rightDirector;
		CommanderWindow leftWindow, rightWindow, currWindow;

		//---------------------------------------------- Main ----------------------------------------------
		public void Launch() {
			ConsoleKeyInfo? input;
			Print(true);

			while (isLaunch) {
				Print();
				input = InvisibleInput();
				if (input.HasValue)
					InputReact(input.Value);
				else 
					System.Threading.Thread.Sleep(100);
			}

			AtExit();
		}

		void InputReact(ConsoleKeyInfo input) {
			if (input.Key == ConsoleKey.LeftArrow || input.Key == ConsoleKey.RightArrow)
				ChangeWindow();
			else if (input.Key == ConsoleKey.Escape)
				isLaunch = false;
		}

		void Print(bool eternal = false) {
			if (eternal) {
				headDirector.PrintElementsEternal();
				downDirector.PrintElementsEternal();
				leftDirector.PrintElementsEternal();
				rightDirector.PrintElementsEternal();
			}
			headDirector.AddElementsToOutput();
			headDirector.PrintScreen();
			downDirector.AddElementsToOutput();
			downDirector.PrintScreen();
			leftDirector.AddElementsToOutput();
			leftDirector.PrintScreen();
			rightDirector.AddElementsToOutput();
			rightDirector.PrintScreen();
		}

		ConsoleKeyInfo? InvisibleInput() {
			if (Console.KeyAvailable) {
				Console.SetCursorPosition(screen.screenSize.x - 1, 0);
				Console.ForegroundColor = Console.BackgroundColor = ConsoleColor.Black;
				return Console.ReadKey();
			}
			return null;
		}

		//---------------------------------------------- Window -----------------------------------------------
		void ChangeWindow() {
			if (currWindow == leftWindow)
				currWindow = rightWindow;
			else
				currWindow = leftWindow;
		}

		//---------------------------------------------- Init ----------------------------------------------
		public Commander() {
			isLaunch = true;
			Console.CursorVisible = false;
			Console.Title = "TeamCommander";

			int currWindowWidth  = screenSizeDivider.x <= 100? Console.LargestWindowWidth - 1 : (int)(Console.LargestWindowWidth  / ((float)(screenSizeDivider.x) / 100)), 
				currWindowHeight = screenSizeDivider.y <= 100 ? Console.LargestWindowHeight - 1 : (int)(Console.LargestWindowHeight / ((float)(screenSizeDivider.y) / 100));
			if (currWindowWidth < minScreenSize.x)
				currWindowWidth = minScreenSize.x;
			if (currWindowHeight < minScreenSize.y)
				currWindowHeight = minScreenSize.y;

			screen = new Output.Output(new Support.Coord(0, 0), new Support.Coord(currWindowWidth, currWindowHeight));
			for (short ii = 0; ii < screen.screenSize.y; ++ii)
				for (short jj = 0; jj < screen.screenSize.x; ++jj)
					screen[ii, jj] = new Output.OutputObj(' ', new Output.DColor(ConsoleColor.Black, ConsoleColor.DarkGray));

			headDirector = new Elements.ElementsDirector(screen);
			downDirector = new Elements.ElementsDirector(screen);
			leftDirector = new Elements.ElementsDirector(screen);
			rightDirector = new Elements.ElementsDirector(screen);

			headDirector.Init();

			leftWindow = new CommanderWindowAllInfo(leftDirector, new Coord(0, 1), new Coord(screen.screenSize.x / 2 - 1, screen.screenSize.y - 3));
			rightWindow = new CommanderWindowAllInfo(rightDirector, new Coord(screen.screenSize.x / 2, 1), new Coord(screen.screenSize.x - 1, screen.screenSize.y - 3));

			currWindow = leftWindow;

			CreateBackGround();
		}

		void CreateBackGround() {
			ushort i = 0;
			OutputObj[] obj;
			ElementText text;

			//head nav
			obj = new OutputObj[screen.screenSize.x - 10];
			for (i = 0; i < obj.Length; ++i)
				obj[i] = new OutputObj(' ', new DColor(ConsoleColor.Black, ConsoleColor.Gray));
			text = new ElementEternalText(obj, new Support.Coord(0, 0), 0);
			headDirector.AddElement(text);

			//Time
			obj = new OutputObj[10];
			for (i = 0; i < obj.Length; ++i)
				obj[i] = new OutputObj(' ', new DColor(ConsoleColor.Green, ConsoleColor.Black));
			text = new ElementTextFromFunc(obj, new Support.Coord(screen.screenSize.x - 10, 0), 0, () => ' ' + DateTime.Now.ToLongTimeString());
			headDirector.AddElement(text);


			//Hotkeys
			try {
				AddHotkeysBar();
			}
			catch (Exception) {
			}

			//Console
			obj = new OutputObj[screen.screenSize.x];
			for (i = 0; i < obj.Length; ++i)
				obj[i] = new OutputObj(' ', new DColor(ConsoleColor.White, ConsoleColor.Black));
			i = 0;
			foreach (char c in @"C:\>")
				obj[i++].sym = c;
			text = new ElementEternalText(obj, new Support.Coord((short)0, screen.screenSize.y - 2), 0);
			downDirector.AddElement(text);


			//frame
			obj = new OutputObj[screen.screenSize.x / 2];
			for (i = 0; i < obj.Length; ++i)
				obj[i] = new OutputObj('═', new DColor(ConsoleColor.Cyan, ConsoleColor.DarkGray));
			obj[0].sym = '╔';
			obj[obj.Length - 1].sym = '╗';
			text = new ElementEternalText(obj, new Support.Coord(0, 1), 0);
			leftDirector.AddElement(text);

			text = new ElementEternalText(obj, new Support.Coord(screen.screenSize.x / 2, 1), 0);
			rightDirector.AddElement(text);

			obj = new OutputObj[screen.screenSize.x / 2];
			for (i = 0; i < obj.Length; ++i)
				obj[i] = new OutputObj('═', new DColor(ConsoleColor.Cyan, ConsoleColor.DarkGray));
			obj[0].sym = '╚';
			obj[obj.Length - 1].sym = '╝';
			text = new ElementEternalText(obj, new Support.Coord(0, screen.screenSize.y - 3), 0);
			leftDirector.AddElement(text);

			text = new ElementEternalText(obj, new Support.Coord(screen.screenSize.x / 2, screen.screenSize.y - 3), 0);
			rightDirector.AddElement(text);

			leftDirector.AddElement(new ElementEternalVLine((short)(screen.screenSize.y - 5), new OutputObj('║', new DColor(ConsoleColor.Cyan, ConsoleColor.DarkGray)), new Support.Coord(0, 2), 0));
			leftDirector.AddElement(new ElementEternalVLine((short)(screen.screenSize.y - 5), new OutputObj('║', new DColor(ConsoleColor.Cyan, ConsoleColor.DarkGray)), new Support.Coord(obj.Length - 1, 2), 0));

			rightDirector.AddElement(new ElementEternalVLine((short)(screen.screenSize.y - 5), new OutputObj('║', new DColor(ConsoleColor.Cyan, ConsoleColor.DarkGray)), new Support.Coord((int)(screen.screenSize.x / 2), 2), 0));
			rightDirector.AddElement(new ElementEternalVLine((short)(screen.screenSize.y - 5), new OutputObj('║', new DColor(ConsoleColor.Cyan, ConsoleColor.DarkGray)), new Support.Coord((int)(obj.Length - 1 + screen.screenSize.x / 2), 2), 0));

			leftDirector.AddElement(new ElemenEternaltHLine((short)(screen.screenSize.x / 2 - 2), new OutputObj('─', new DColor(ConsoleColor.Cyan, ConsoleColor.DarkGray)), new Support.Coord(1, screen.screenSize.y - 7), 0));
			rightDirector.AddElement(new ElemenEternaltHLine((short)(screen.screenSize.x / 2 - 2), new OutputObj('─', new DColor(ConsoleColor.Cyan, ConsoleColor.DarkGray)), new Support.Coord((short)(1 + screen.screenSize.x / 2), screen.screenSize.y - 7), 0));

			leftDirector.AddElement(new ElementEternalVLine((short)(screen.screenSize.y - 9), new OutputObj('│', new DColor(ConsoleColor.Cyan, ConsoleColor.DarkGray)), new Support.Coord((int)(screen.screenSize.x / 6), 2), 0));
			leftDirector.AddElement(new ElementEternalVLine((short)(screen.screenSize.y - 9), new OutputObj('│', new DColor(ConsoleColor.Cyan, ConsoleColor.DarkGray)), new Support.Coord((int)(screen.screenSize.x / 3), 2), 0));

			rightDirector.AddElement(new ElementEternalVLine((short)(screen.screenSize.y - 9), new OutputObj('│', new DColor(ConsoleColor.Cyan, ConsoleColor.DarkGray)), new Support.Coord((int)(screen.screenSize.x / 6 + screen.screenSize.x / 2), 2), 0));
			rightDirector.AddElement(new ElementEternalVLine((short)(screen.screenSize.y - 9), new OutputObj('│', new DColor(ConsoleColor.Cyan, ConsoleColor.DarkGray)), new Support.Coord((int)(screen.screenSize.x / 3 + screen.screenSize.x / 2), 2), 0));
		}

		void AtExit() {
			Console.BackgroundColor = ConsoleColor.Black;
			Console.ForegroundColor = ConsoleColor.Green;
			Console.SetCursorPosition(5, screen.screenSize.y - 2);
		}

		//---------------------------------------------- Hotkeys ----------------------------------------------
		void AddHotkeysBar() {
			byte oneLength = (byte)(System.Math.Round(screen.screenSize.x / 10.0 - 6));

			System.Collections.Generic.List<OutputObj> obj = new List<OutputObj>(screen.screenSize.x);

			for (byte i = 0; i < 10; ++i) {
				string descript = GetHelpDescription(i);
				if (descript.Length < oneLength)
					descript += new string(' ', oneLength - descript.Length);
				else if (descript.Length > oneLength)
					descript = descript.Substring(0, oneLength);
				foreach (var o in FormatHotkey("F" + (i + 1).ToString(), descript))
					obj.Add(o);
			}

			for (ushort i = (ushort)(obj.Count); i < obj.Capacity; ++i)
				obj.Add(new OutputObj(' ', new DColor(ConsoleColor.Black, ConsoleColor.Gray)));

			Element text = new ElementEternalText(obj.ToArray(), new Support.Coord((short)0, screen.screenSize.y - 1), 0);
			downDirector.AddElement(text);
		}

		string GetHelpDescription(byte id) {
			switch (id) {
			case 0:
			return "Help";
			case 1:
			return "User";
			case 2:
			return "View";
			case 3:
			return "Edit";
			case 4:
			return "Copy";
			case 5:
			return "Ren";
			case 6:
			return "MkDir";
			case 7:
			return "Del";
			case 8:
			return "Size";
			case 9:
			return "Menu";
			default:
			return "NONE";
			}
		}

		OutputObj[] FormatHotkey(string key, string description) {
			key = ' ' + key;
			OutputObj[] rez = new OutputObj[key.Length + description.Length + 2];
			for (ushort i = 0; i < key.Length; ++i)
				rez[i] = new OutputObj(key[i], new DColor(ConsoleColor.DarkMagenta, ConsoleColor.Gray));
			rez[key.Length] = new OutputObj(' ', new DColor(ConsoleColor.Black, ConsoleColor.Gray));
			for (ushort i = 0; i < description.Length; ++i)
				rez[i + key.Length + 1] = new OutputObj(description[i], new DColor(ConsoleColor.Black, ConsoleColor.Gray));
			rez[key.Length + description.Length + 1] = new OutputObj(' ', new DColor(ConsoleColor.Black, ConsoleColor.Gray));
			return rez;
		}
	}
}
