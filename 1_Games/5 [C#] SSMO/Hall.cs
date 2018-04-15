using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SSMO {
	class Coord {
		public int x, y;
		public Coord() : this(0, 0) { }
		public Coord(int X, int Y) { x = X; y = Y; }
	}

	class Chair {
		const char symbol = '╥';
		const char symbolPeople = '☺';

		public Coord refPos;
		public bool withPeople = false;
		bool prevPrintState = true;

		public Chair(Coord refpos) {
			refPos = refpos;
		}

		public void Print() {
			if (prevPrintState == withPeople)
				return;
			prevPrintState = withPeople;
			Console.CursorLeft += refPos.x;
			Console.CursorTop += refPos.y;
			Console.BackgroundColor = ConsoleColor.Black;

			if (withPeople) {
				Console.ForegroundColor = ConsoleColor.Red;
				Console.Write(symbolPeople);
			}
			else {
				Console.ForegroundColor = ConsoleColor.DarkYellow;
				Console.Write(symbol);
			}
		}
	}

	class Place {
		protected const char symbol = '╤';
		protected const char symbolPizza = '@';
		protected bool withPizza = false;
		protected List<Chair> chairs;
		public Coord refPos;
		public bool isFree = true;
		protected bool prevPrintState = true;
		public ClientsCompany client;

		public void PlacePizza(bool state) => withPizza = state;
		public void PlaceHumans(byte cnt, bool state) {
			void Peremishat<T>(List<T> data) {
				for (int i = (data as List<T>).Count - 1; i >= 1; --i) {
						int j = Rand.rand.Next(i + 1);
						var temp = data[j];
						data[j] = data[i];
						data[i] = temp;
				}
			}

			Peremishat(chairs);
			for (byte i = 0; i < cnt && i < chairs.Count; ++i)
				chairs[i].withPeople = state;
		}

		public Place(Coord refpos) {
			refPos = refpos;
			chairs = new List<Chair>();
		}

		public byte ChairsCnt { get { return (byte)chairs.Count; } }

		public void AddChair(Chair chair) => chairs.Add(chair);

		public virtual void Print(Coord startPos) {
			if (prevPrintState != withPizza) {
				prevPrintState = withPizza;
				Console.CursorLeft = startPos.x + refPos.x;
				Console.CursorTop = startPos.y + refPos.y;
				Console.BackgroundColor = ConsoleColor.Black;
				if (withPizza) {
					Console.ForegroundColor = ConsoleColor.Yellow;
					Console.Write(symbolPizza);
				}
				else {
					Console.ForegroundColor = ConsoleColor.DarkYellow;
					Console.Write(symbol);
				}
			}
			foreach (var i in chairs) {
				Console.CursorLeft = startPos.x + refPos.x;
				Console.CursorTop = startPos.y + refPos.y;
				i.Print();
			}
		}
	}

	class ManyPlaces : Place {
		List<Coord> tables;

		public void AddTable(Coord refPos) => tables.Add(refPos);

		public ManyPlaces(Coord refpos) : base(refpos) {
			tables = new List<Coord>();
		}

		public override void Print(Coord startPos) {
			if (prevPrintState != withPizza) {
				foreach (var i in tables) {
					Console.CursorLeft = startPos.x + i.x + refPos.x;
					Console.CursorTop = startPos.y + i.y + refPos.y;
					Console.BackgroundColor = ConsoleColor.Black;
					Console.ForegroundColor = ConsoleColor.DarkYellow;
					Console.Write(symbol);
				}
			}
			base.Print(startPos);
		}

		public bool FreePlace(Coord check) {
			if (refPos.x - check.x < 0 || refPos.y - check.y < 0)
				return false;
			foreach(var i in tables)
				if(i.x == check.x && i.y == check.y)
					return false;
			foreach (var i in chairs)
				if (i.refPos.x == check.x && i.refPos.y == check.y)
					return false;
			return true;
		}
		public bool NearTable(Coord check) {
			int abs(int a) => a < 0 ?-a:a;

			if ( 
				(abs(check.x) == 1 && abs(check.y) == 0) ||
				(abs(check.x) == 0 && abs(check.y) == 1)
				)
				return true;
			foreach (var i in tables) {
				if (
				(abs(check.x - i.x) == 1 && abs(check.y - i.y) == 0) ||
				(abs(check.x - i.x) == 0 && abs(check.y - i.y) == 1)
				)
					return true;
			}
			return false;
		}
	}

	class Hall {
		public Coord leftUpCorner;
		public Coord rightDownCorner;
		string[] walls;

		List<Place> places;

		public Hall(Coord _leftUpCorner, Coord _rightDownCorner) {
			leftUpCorner = _leftUpCorner;
			rightDownCorner = _rightDownCorner;
			places = new List<Place>();
		}

		public void SetWalls(string[] _walls) {
			walls = _walls;
		}

		public void PrintWalls() {
			Console.ForegroundColor = ConsoleColor.DarkGray;
			Console.BackgroundColor = ConsoleColor.Black;
			Console.SetCursorPosition(leftUpCorner.x, leftUpCorner.y);
			foreach (var i in walls) {
				foreach (var j in i) {
					if (j == '-' || j == '|') {
						Console.ForegroundColor = ConsoleColor.Yellow;
						Console.BackgroundColor = ConsoleColor.Black;
					}
					if (j == '#') {
						Console.ForegroundColor = ConsoleColor.Black;
						Console.BackgroundColor = ConsoleColor.White;
					}
					if(j != ' ')
						Console.Write(j);
					else
						Console.Write('.');

					if (j == '-' || j == '|' || j == '#') {
						Console.ForegroundColor = ConsoleColor.DarkGray;
						Console.BackgroundColor = ConsoleColor.Black;
					}
				}
				Console.CursorLeft = leftUpCorner.x;
				++Console.CursorTop;
			}
		}

		public void AddPlace(Place place) => places.Add(place);

		public void ClientsEat() {
			foreach (var i in places)
				i.client?.Eat();
		}

		public void Print() {
			foreach (var i in places)
				i.Print(leftUpCorner);
		}

		public bool NearTable(Coord pos) {
			foreach (var i in places)
				if (Math.Abs(i.refPos.x - pos.x) <= 3 && Math.Abs(i.refPos.y - pos.y) <= 3)
					return true;
			return false;
		}

		public Place GetFreePlace(byte humanCnt) {
			foreach (var i in places)
				if (i.isFree && i.ChairsCnt >= humanCnt)
					return i;
			return null;
			
		}

		public Place GetPlaceById(int id) {
			return places[id];
		}

	}
}
