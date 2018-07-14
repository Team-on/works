using System.Collections.Generic;
using System.Xml;
using System;

namespace CarParking {
	static class Settings {
		public static byte Timeout { get; private set; }
		public static ushort ParkingSpace { get; private set; }
		public static double Fine { get; private set; }
		public static Dictionary<CarType, byte> Price { get; private set; }

		public static void ReadFromXml() {
			try {
				Price = new Dictionary<CarType, byte>();

				XmlDocument xml = new XmlDocument();
				xml.Load("settings.xml");
				var root = xml.ChildNodes[1];

				//Console.WriteLine("");
				//Console.WriteLine("Start");

				foreach (XmlNode node in root.ChildNodes) {
					string name = node.Name.ToLower();
					if(name == "timeout") {
						Timeout = byte.Parse(node.InnerText);
						//Console.WriteLine("Load timeout");

					}
					else if (name == "finemultipler") {
						Fine = double.Parse(node.InnerText);
						//Console.WriteLine("Load finemultipler");
					}
					else if (name == "parkingspace") {
						ParkingSpace = ushort.Parse(node.InnerText);
						//Console.WriteLine("Load parkingspace");
					}
					else if (name == "pricelist") {
						CarType type = CarType.NONE;
						byte price = 0;

						foreach (XmlAttribute attr in node.Attributes) {
							name = attr.Name.ToLower();
							if (name == "type") {
								for (byte i = 0; i < (byte)CarType.NONE; ++i)
									if (attr.Value.ToLower() == ((CarType)(i)).ToString().ToLower()) {
										type = (CarType)i;
										break;
									}
							}
							else if (name == "price") 
								price = byte.Parse(attr.Value);
						}

						Price.Add(type, price);
					}
				}
			}
			catch(Exception ex) {
				Log.log.LogNewLine("Cant load settings.xml. Try to use standart values");
				Settings.ChangeSettings(1, 10, 1.5, new Dictionary<CarType, byte>	{	{ CarType.Bus, 2 },
																						{ CarType.Motorcycle, 1 },
																						{ CarType.Passenger, 3 },
																						{ CarType.Truck, 5 }
																					}
				);
			}
		}

		public static void ChangeSettings(byte timeout = 0, ushort parkingSpace = 0, double fine = -1, Dictionary<CarType, byte> price = null) {

			if(timeout != 0)
				Timeout = timeout;
			if (parkingSpace != 0)
				ParkingSpace = parkingSpace;
			if (fine != -1)
				Fine = fine;
			if (price != null)
				Price = price;
		}
	}
}
