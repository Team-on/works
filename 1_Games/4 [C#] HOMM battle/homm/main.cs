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
			//Console.SetWindowSize(152, 47);
			Console.SetWindowSize(Console.LargestWindowWidth, Console.LargestWindowHeight);
			Hero hLeft  = new Hero(new Title(), "Thant") { atk = 1, def = 5, luck = 0, moral = 0 },
				 hRight = new Hero(new Title(), "Galthran") { atk = 5, def = 1, luck = 0, moral = 0 };
			Army left  = new Army(ref hLeft), 
				 right = new Army(ref hRight);

			left.AddUnit(new StackUnit("Skelet1", new Title('$', ConsoleColor.Red), 5, 4, new DMG(1, 3), 15, 6, 1));
			left.AddUnit(new StackUnit("Skelet1", new Title('$', ConsoleColor.Red), 5, 4, new DMG(1, 3), 15, 6, 100));
			left.AddUnit(new StackUnit("Skelet1", new Title('$', ConsoleColor.Red), 5, 4, new DMG(1, 3), 15, 6, 200));
			left.AddUnit(new StackUnit("Skelet1", new Title('$', ConsoleColor.Red), 5, 4, new DMG(1, 3), 15, 6, 500));
			left.AddUnit(new StackUnit("Skelet1", new Title('$', ConsoleColor.Red), 5, 4, new DMG(1, 3), 15, 6, 750));
			left.AddUnit(new StackUnit("Skelet1", new Title('$', ConsoleColor.Red), 5, 4, new DMG(1, 3), 15, 6, 1000));
			left.AddUnit(new StackUnit("Skelet1", new Title('$', ConsoleColor.Red), 5, 4, new DMG(1, 3), 15, 6, 1500));

			right.AddUnit(new StackUnit("Skelet2", new Title('$', ConsoleColor.Blue), 5, 4, new DMG(1, 3), 15, 6, 1));
			right.AddUnit(new StackUnit("Skelet2", new Title('$', ConsoleColor.Blue), 5, 4, new DMG(1, 3), 15, 6, 100));
			right.AddUnit(new StackUnit("Skelet2", new Title('$', ConsoleColor.Blue), 5, 4, new DMG(1, 3), 15, 6, 200));
			right.AddUnit(new StackUnit("Skelet2", new Title('$', ConsoleColor.Blue), 5, 4, new DMG(1, 3), 15, 6, 500));
			right.AddUnit(new StackUnit("Skelet2", new Title('$', ConsoleColor.Blue), 5, 4, new DMG(1, 3), 15, 6, 750));
			right.AddUnit(new StackUnit("Skelet2", new Title('$', ConsoleColor.Blue), 5, 4, new DMG(1, 3), 15, 6, 1000));
			right.AddUnit(new StackUnit("Skelet2", new Title('$', ConsoleColor.Blue), 5, 4, new DMG(1, 3), 15, 6, 1500));


			BattleModule battle = new BattleModule(BattleMap.LandscapeTypes.FOREST);
			battle.SetLeftArmy(ref left);
			battle.SetRightArmy(ref right);
			battle.Play(); 
		}
	}
}
