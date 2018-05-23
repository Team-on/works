using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1 {
	static class Settings {
		public static byte[] placesInRow;

		static Settings() {
			placesInRow = new byte[6];
			placesInRow[0] = 8;
			placesInRow[1] = 8;
			placesInRow[2] = 10;
			placesInRow[3] = 10;
			placesInRow[4] = 12;
			placesInRow[5] = 12;
		}
	}
}
