using System.Collections;
using System.Collections.Generic;
using System.Timers;
using System.IO;

namespace CarParking {
	sealed class Parking {
		public static ParkingBase parking { get; private set; }

		static Parking() {
			parking = new ParkingBase();
		}
	}

	class ParkingBase : IEnumerable {
		double fineMultiple;
		ushort parkingSpace;
		byte timeout;
		Dictionary<CarType, byte> priceForTypes;

		Timer logWriter;
		Timer getMoneyFromCars;

		List<Car> cars;
		List<Transaction> transaction;
		ulong earnedMoney;

		public ushort ParkingSpaceAll { get => parkingSpace; }
		public ushort ParkingSpaceFree { get => (ushort)cars.Count; }
		public ulong EarnedMoney { get => earnedMoney; }
		public ulong Income { get => EarnedMoney; }

		public ParkingBase() {
			Settings.ReadFromXml();

			fineMultiple = Settings.Fine;
			parkingSpace = Settings.ParkingSpace;
			timeout = Settings.Timeout;
			priceForTypes = new Dictionary<CarType, byte>(Settings.Price);

			cars = new List<Car>();
			transaction = new List<Transaction>();
			earnedMoney = 0;

			getMoneyFromCars = new Timer(timeout * 1000);
			getMoneyFromCars.AutoReset = true;
			getMoneyFromCars.Elapsed += delegate (object sender, ElapsedEventArgs e) {
				uint price;
				foreach (var i in cars) {
					Transaction.CarIdCurrent = i.Id;
					price = priceForTypes[i.Type];
					if (i.Balance > price) {
						i.Balance -= price;
					}
					else if (i.Balance == 0)
						i.Fine += (uint)(fineMultiple * price);
					else {
						price -= i.Balance;
						i.Balance = 0;
						i.Fine += (uint)(fineMultiple * price);
					}

				}
			};

			logWriter = new Timer(60000);
			logWriter.AutoReset = true;
			logWriter.Elapsed += delegate (object sender, ElapsedEventArgs e) {
				using (StreamWriter file = new StreamWriter("transaction.log", true)) {
					ulong sum = 0;
					foreach (var i in transaction)
						sum += i.Money;
					file.Write(System.DateTime.Now.ToString());
					file.Write(' ');
					file.WriteLine(sum);
				}
				transaction.Clear();
				Log.log.LogNewLine("Save log");
			};
			logWriter.Start();
		}

		public void AddCar(Car car) {
			if (cars.Count == 0)
				getMoneyFromCars.Start();

			if(cars.Count < ParkingSpaceAll)
			cars.Add(car);

			Log.log.LogNewLine("Add new car. Id: " + car.Id.ToString());
		}

		public void DelCar(uint id) {
			if (cars.Find((Car a) => a.Id == id).Balance != 0) {
				cars.Remove(new Car(id));
				Log.log.LogNewLine("Delete car. Id: " + id.ToString());

				if (cars.Count == 0)
					getMoneyFromCars.Stop();
			}
		}

		public void DepositMoney(uint id, uint money) {
			var rez = cars.Find( (Car car) => car.Id == id );
			if (rez != null) {
				Log.log.LogNewLine("Deposit " + money.ToString() + "$ to car with id " + id.ToString());

				rez.Balance += money;
				if (rez.Balance <= rez.Fine) {
					rez.Fine -= rez.Balance;
					rez.Balance = 0;
				}
				else {
					rez.Balance -= rez.Fine;
					rez.Fine = 0;
				}
			}
		}

		public IEnumerator GetEnumerator() {
			return cars.GetEnumerator();
		}

		public void AddIncome(uint value) {
			this.earnedMoney += value;
		}

		public void AddTransaction(Transaction tr) {
			transaction.Add(tr);
		}
	}
}
