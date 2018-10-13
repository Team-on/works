using System;

namespace CarParking {

	[Serializable]
	class Transaction {
		public static uint CarIdCurrent;

		public DateTime Time { get; private set; }
		public uint CarId { get; private set; }
		public uint Money { get; private set; }

		public Transaction(DateTime time, uint carId, uint money) {
			Time = time;
			CarId = carId;
			Money = money;
		}
	}
}
