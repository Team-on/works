using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace homm{
	struct Coord {
		public short x, y;
		public Coord(System.SByte X, System.SByte Y) { x = X; y = Y; }
	}
    class Hero{
		public byte atk, def, moral, luck;
    }

	class StackUnit {
		public GameTitle title { private set; get; }
		public byte atk, def, dmgMin, dmgMax, speed, hp;
		byte atkRange;
		bool isFlying;

		short number;
		Coord pos;

		Hero hero;

		bool MoveAttack() {
			return true;
		}
		bool Move() {
			return true;
		}
		bool Step(GameTitle title) {
			return true;
		}

		/*bool Attack(ref StackUnit enemy) {
			ushort dmg = 0;
			enemy.GetDMG(dmg, (byte)(atk + hero.atk));
			return true;
		}*/

		void GetDMG(ushort dmg, byte heroAtk) {

		}
	}

	class Army {
		Hero hero;
		StackUnit[] units; 
	}

	class Fraction {

	}

	class Game {
		BattleMap map;
		//Army p1, p2;

		public Game() {
			map = new BattleMap();
		}

		public void Play() {
			PrintCurrState();
		}

		void PrintCurrState() {
			map.Print(new Coord(5,5));
		}
	}

	class GameSingletone {
		static public Game game { get;  set; }

		static GameSingletone() {
			game = new Game();
		}
	}


    class CMain{
        static void Main(string[] args){
			GameSingletone.game.Play();
		}
    }
}
