namespace TeamCommander {
	namespace Support {

		class Coord {
			public short x, y;

			public Coord() {
				x = y = 0;
			}

			public Coord(short X, short Y) {
				x = X;
				y = Y;
			}
			public Coord(int X, int Y) {
				x = (short)X;
				y = (short)Y;
			}
		}
	}
}
