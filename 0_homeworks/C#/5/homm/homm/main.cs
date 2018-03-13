using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace homm{
    class Hero{
		public byte atk, def, moral, luck;
    }

	class StackUnit {
		public Title title { get; private set; }
		public string name { get; private set; }

		public byte atk, def, dmgMin, dmgMax, speed, hp;
		byte lashUnitHp;
		//byte atkRange;
		//bool isFlying;

		short number;
		Coord pos;
	}

	class Army {
		public Hero hero {private set; get; }
		StackUnit[] units;

		public Army(Hero newHero) {
			hero = newHero;
			units = new StackUnit[7];
			for (byte i = 0; i < units.Length; ++i)
				units[i] = null;
		}
	}

	class Fraction {

	}

	class BattleModule {
		Coord mapPrintPos;
		BattleMap map;
		Army pl, pr;

		public BattleModule(BattleMap.LandscapeTypes type) {
			mapPrintPos.x = 37;
			mapPrintPos.y = 1;
			map = new BattleMap();
			map.GenerateLandscape(type);
		}

		public void SetLeftArmy(ref Army left) { pl = left; }
		public void SetRightArmy(ref Army right) { pr = right; }

		public void Play() {
			PrintCurrState();
			PrintHeroInfo();
		}

		void PrintCurrState() {
			map.Print(mapPrintPos);
		}

		void PrintHeroInfo() {

		}

	}


    class CMain{
		static void Main(string[] args) {
			Army left = new Army(new Hero() {atk = 1, def = 5,luck = 0, moral = 0 }), 
				 right = new Army(new Hero() { atk = 5, def = 1, luck = 0, moral = 0 });
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
