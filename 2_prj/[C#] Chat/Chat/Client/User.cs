using System;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Collections.Generic;

namespace ClientLib {
	[Serializable]
	public class User {
		string name;
		ConsoleColor color;

		public string Name => name;
		public ConsoleColor Color => color;

		public User(string name = "Anon", ConsoleColor color = ConsoleColor.White) {
			switch (IsAllowedName(name)) {
				case ErrorName.None:
					this.name = name;
					break;
				case ErrorName.BannedName:
					throw new Exception("[" + name + "] is a banned name");
				case ErrorName.ContainsBannedCharacter:
					throw new Exception("[" + name + "] contains banned symbol. Use only letters and digits");
				case ErrorName.MustContainAtLeast1Letter:
					throw new Exception("[" + name + "] must contain at least 1 letter");
				default:
					throw new Exception("Unknow return code in IsAllowedName()");
			}

			switch (IsAllowedColor(color)) {
				case ErrorColor.None:
					this.color = color;
					break;
				case ErrorColor.BannedColor:
					throw new Exception("[" + color + "] is a banned color");
				default:
					throw new Exception("Unknow return code in IsAllowedColor()");
			}
		}

		static readonly Func<char, bool> IsBannedSymbol = (a) => !(char.IsLetterOrDigit(a) || a == '_' || a == '-' || a == '=');
		static readonly List<string> bannedNames = new List<string>(){
			"admin",
			"administrator",
			"moder",
			"moderator",
			"system",
			"system",
		};

		static readonly List<ConsoleColor> bannedColors = new List<ConsoleColor>(){
			ConsoleColor.Red,
			ConsoleColor.Yellow,
		};

		static public ErrorName IsAllowedName(string name) {
			if (bannedNames.Contains(name.ToLower()))
				return ErrorName.BannedName;

			bool haveLetter = false;
			for (byte i = 0; i < name.Length; ++i) {
				if (IsBannedSymbol(name[i]))
					return ErrorName.ContainsBannedCharacter;
				if (!haveLetter && char.IsLetter(name[i]))
					haveLetter = true;
			}

			if (!haveLetter)
				return ErrorName.MustContainAtLeast1Letter;

			return ErrorName.None;
		}

		static public ErrorColor IsAllowedColor(ConsoleColor color) {
			if (bannedColors.Contains(color))
				return ErrorColor.BannedColor;

			return ErrorColor.None;
		}


		static BinaryFormatter binaryFormatter = new BinaryFormatter();

		static public byte[] Serialize(User obj) {
			if (obj == null)
				return null;
			using (MemoryStream ms = new MemoryStream()) {
				binaryFormatter.Serialize(ms, obj);
				return ms.ToArray();
			}
		}

		static public User Deserialize(byte[] bytes) {
			if (bytes == null)
				return null;
			using (MemoryStream ms = new MemoryStream(bytes)) 
				return binaryFormatter.Deserialize(ms) as User;
		}
	}
}
