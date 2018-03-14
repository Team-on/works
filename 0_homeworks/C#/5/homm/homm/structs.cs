namespace homm {
	struct Coord {
		public int x, y;
		public Coord(int X, int Y) { x = X; y = Y; }
	}

	struct DMG {
		public short max, min;
		public DMG(short Max, short Min) { max = Max; min = Min; }
	}

	struct Stat {
		public byte baseStat;
		public short heroBonus;
		short CurrValue;
		public short currValue {get { return CurrValue;}}

		public Stat(byte BaseStat, short HeroBonus = 0) {
			baseStat = BaseStat;
			heroBonus = HeroBonus;
			CurrValue = (short)(heroBonus + baseStat);
		}
		
		public void ChangeHeroBonus(short HeroBonus) {
			heroBonus = HeroBonus;
			CurrValue = (short)(heroBonus + baseStat);
		}
	}
}
