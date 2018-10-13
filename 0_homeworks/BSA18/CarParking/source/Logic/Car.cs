namespace CarParking {
	class Car {
		static uint LastId;

		public uint Id { get; private set; }

		uint balance;
		public uint Balance { get => balance;  set {
				if (value < balance) {
					Parking.parking.AddIncome(balance - value);
					Parking.parking.AddTransaction(new Transaction(System.DateTime.Now, Transaction.CarIdCurrent, balance - value));
					Log.log.LogNewLine("[" + System.DateTime.Now.ToLongTimeString() + "]  Id: " + Transaction.CarIdCurrent.ToString().PadRight(4) + " Money: " + (balance - value).ToString() );
				}
				balance = value;
			}
		}
		public CarType Type { get; private set; }

		public uint Fine { get; set; }

		static Car() {
			LastId = 0;
		}

		public Car(uint id) {
			Id = id;
		}

		public Car(CarType type, uint balance) {
			Id = LastId++;
			Type = type;
			Balance = balance;
		}

		public override bool Equals(object obj) {
			if(obj is Car)
				return Id.Equals((obj as Car).Id);
			if (obj is int)
				return Id.Equals((int)obj);
			//return this.GetHashCode() == obj.GetHashCode();
			return false;
		}

		public override int GetHashCode() {
			return Id.GetHashCode();
		}
	}
}
