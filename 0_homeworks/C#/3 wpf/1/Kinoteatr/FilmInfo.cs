using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1{
    class FilmInfo{
		public ZalInfo Zal { get; private set; }
		public DateTime Time { get; private set; }
		public string Name { get; private set; }
		public string ImageSrc { get; private set; }
		public Dictionary<PlaceTypes, ushort> Prices { get; private set; }
		public Place[][] places { get; private set; }

		public bool GetPlaceState(int i, int j) => places[i][j].isFree;
		public void SetPlaceState(int i, int j, bool isFree) => places[i][j].isFree = isFree;

		public FilmInfo(ZalInfo zal, DateTime time, string name, string imageSrc, Dictionary<PlaceTypes, ushort> prices) {
			Zal = zal;
			Time = time;
			Name = name;
			ImageSrc = imageSrc;
			Prices = prices;
			places = new Place[Settings.placesInRow.Length][];
			for (byte i = 0; i < places.Length; ++i) {
				places[i] = new Place[Settings.placesInRow[i]];
				for (byte j = 0; j < places[i].Length; ++j)
					places[i][j] = new Place();
			}
			SetVipRow(4);
			SetVipRow(5);
		}

		public ushort GetPriceByPlace(int row, int col) => Prices[places[row][col].type];

		public void SetVipRow(byte row) {
			foreach (var i in places[row]) 
				i.type = PlaceTypes.Vip;
		}

		public void SetVipPlace(byte row, byte col) => places[row][col].type = PlaceTypes.Vip;
	}
}
