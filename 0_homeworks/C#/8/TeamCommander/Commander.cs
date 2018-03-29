using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using TeamCommander.Elements;
using TeamCommander.Output;


namespace TeamCommander {
    class Commander{
		Output.Output screen;
		Elements.ElementsDirector headDirector;
		Elements.ElementsDirector downDirector;
		ElementsDirector leftDirector, rightDirector;

		public Commander() {
			screen = new Output.Output(new Support.Coord(0, 0), new Support.Coord((short)(Console.LargestWindowWidth / 1.5), Console.LargestWindowHeight / 2));
			for (short ii = 0; ii < screen.screenSize.y; ++ii)
				for (short jj = 0; jj < screen.screenSize.x; ++jj)
					screen[ii, jj] = new Output.OutputObj(' ', new Output.DColor(ConsoleColor.Black, ConsoleColor.DarkGray));

			headDirector = new Elements.ElementsDirector(screen);
			downDirector = new Elements.ElementsDirector(screen);
			leftDirector = new Elements.ElementsDirector(screen); 
			rightDirector = new Elements.ElementsDirector(screen);
			headDirector.Init();

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
			i = 0;
			foreach (char c in " XX:XX:XX ")
				obj[i++].sym = c;
			text = new ElementText(obj, new Support.Coord(screen.screenSize.x - 10, 0), 0);
			headDirector.AddElement(text);


			//Hotkeys
			obj = new OutputObj[screen.screenSize.x];
			for (i = 0; i < obj.Length; ++i)
				obj[i] = new OutputObj(' ', new DColor(ConsoleColor.Black, ConsoleColor.Gray));
			text = new ElementEternalText(obj, new Support.Coord((short)0, screen.screenSize.y - 1), 0);
			downDirector.AddElement(text);

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

		public void Launch() {
			Print(true);
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
	}
}
