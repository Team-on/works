using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace homm{
	class Fraction {

	}

    class CMain{
		static void Main(string[] args) {
			/*int pos = 0;
			while (true){
				for (int i = 0; i < 15; ++i)
				{
					Console.SetCursorPosition((i + 1) * 3, 4);
					Console.Write("|");
					Console.SetCursorPosition((i + 1) * 3, 5);
					if (pos == i)
						Console.Write("^");
					else
						Console.Write(" ");
				}
				Console.ForegroundColor = ConsoleColor.Black;
				ConsoleKey read = Console.ReadKey().Key;
				Console.ForegroundColor = ConsoleColor.White;

				if (read == ConsoleKey.A)
					--pos;
				if (read == ConsoleKey.D)
					++pos;

				if (pos == -1)
					pos = 14;
				else if(pos == 15)
					pos = 0;
			}*/

			//Console.SetWindowSize(152, 47);
			Console.SetWindowSize(Console.LargestWindowWidth, Console.LargestWindowHeight);
			Hero hLeft  = new Hero(new Title(), "Thant") { atk = 1, def = 5, luck = 0, moral = 0 },
				 hRight = new Hero(new Title(), "Galthran") { atk = 5, def = 1, luck = 0, moral = 0 };
			Army left  = new Army(ref hLeft), 
				 right = new Army(ref hRight);

			left.AddUnit(new StackUnit("Skelet", new Title('$', ConsoleColor.Red), 5, 4, new DMG(1, 3), 15, 6, 1));
			left.AddUnit(new StackUnit("Skelet", new Title('$', ConsoleColor.Red), 5, 4, new DMG(1, 3), 15, 6, 100));
			left.AddUnit(new StackUnit("Skelet", new Title('$', ConsoleColor.Red), 5, 4, new DMG(1, 3), 15, 6, 200));
			left.AddUnit(new StackUnit("Skelet", new Title('$', ConsoleColor.Red), 5, 4, new DMG(1, 3), 15, 6, 500));
			left.AddUnit(new StackUnit("Skelet", new Title('$', ConsoleColor.Red), 5, 4, new DMG(1, 3), 15, 6, 750));
			left.AddUnit(new StackUnit("Skelet", new Title('$', ConsoleColor.Red), 5, 4, new DMG(1, 3), 15, 6, 1000));
			left.AddUnit(new StackUnit("Skelet", new Title('$', ConsoleColor.Red), 5, 4, new DMG(1, 3), 15, 6, 1500));

			right.AddUnit(new StackUnit("Skelet", new Title('$', ConsoleColor.Blue), 5, 4, new DMG(1, 3), 15, 6, 1));
			right.AddUnit(new StackUnit("Skelet", new Title('$', ConsoleColor.Blue), 5, 4, new DMG(1, 3), 15, 6, 100));
			right.AddUnit(new StackUnit("Skelet", new Title('$', ConsoleColor.Blue), 5, 4, new DMG(1, 3), 15, 6, 200));
			right.AddUnit(new StackUnit("Skelet", new Title('$', ConsoleColor.Blue), 5, 4, new DMG(1, 3), 15, 6, 500));
			right.AddUnit(new StackUnit("Skelet", new Title('$', ConsoleColor.Blue), 5, 4, new DMG(1, 3), 15, 6, 750));
			right.AddUnit(new StackUnit("Skelet", new Title('$', ConsoleColor.Blue), 5, 4, new DMG(1, 3), 15, 6, 1000));
			right.AddUnit(new StackUnit("Skelet", new Title('$', ConsoleColor.Blue), 5, 4, new DMG(1, 3), 15, 6, 1500));


			BattleModule battle = new BattleModule(BattleMap.LandscapeTypes.FOREST);
			battle.SetLeftArmy(ref left);
			battle.SetRightArmy(ref right);
			battle.Play();
			/*
			Console.SetWindowSize(152, 47);
			for (int i = 0; i < 45; ++i) { 
				for (int j = 0; j < 150; ++j)
					Console.Write('-');
				Console.WriteLine();
			}

			int x = 37, y = 1;
			Console.SetCursorPosition(x, y);
			for (int i = 0; i < 33; ++i) {
				for (int j = 0; j < 75; ++j)
					Console.Write('*');
				Console.SetCursorPosition(x,++y);
			}
			x = 37 + 2; y = 1 + 1;
			Console.SetCursorPosition(x, y);
			for (int i = 0; i < 11; ++i) {
				for (int j = 0; j < 15; ++j) {
					Console.Write('@');
					Console.SetCursorPosition(x += 5, y);
				}
				x = 37 + 2;
				Console.SetCursorPosition(x, y += 3);
			}
			*/
		}
	}
}
