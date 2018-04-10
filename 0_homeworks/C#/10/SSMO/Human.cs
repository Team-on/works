namespace SSMO {
	class Human {
		public string Name { get; protected set; }
		public string Surname { get; protected set; }

		public static string GenerateName() {
			string golosni = "aaaeeeiiouyy";
			string prigolosni = "bbbcdddffgghjkllmmmnnnppqrrssstttvwxz";
			string newName = "";
			string currArr = Rand.rand.Next(0, 100) < 40 ? golosni : prigolosni;
			byte nameLength = (byte)Rand.rand.Next(2, 12);
			for (byte i = 0; i < nameLength; i++) {
				newName += currArr[Rand.rand.Next(0, currArr.Length)];
				if (Rand.rand.Next(0, 100) < 10 && nameLength != i + 1) {
					newName += currArr[Rand.rand.Next(0, currArr.Length)];
					i++;
				}
				currArr = currArr == golosni ? prigolosni : golosni;
			}
			return newName;
		}
	}
}
