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

		public Chair(Coord refpos) {
			refPos = refpos;
		}

		public void Print() {
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
			base.Print(startPos);
			foreach (var i in tables) {
				Console.CursorLeft = startPos.x + i.x + refPos.x;
				Console.CursorTop = startPos.y + i.y + refPos.y;
				Console.BackgroundColor = ConsoleColor.Black;
				Console.ForegroundColor = ConsoleColor.DarkYellow;
				Console.Write(symbol);
			}
		}
	}

	class Hall {
		public Coord leftUpCorner;
		public Coord rightDownCorner;

		List<Place> places;

		public Hall(Coord _leftUpCorner, Coord _rightDownCorner) {
			leftUpCorner = _leftUpCorner;
			rightDownCorner = _rightDownCorner;
			places = new List<Place>();
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

		public Place GetFreePlace(byte humanCnt) {
			foreach (var i in places)
				if (i.isFree && i.ChairsCnt >= humanCnt)
					return i;
			return null;
			
		}

	}
}
