﻿using System;
using System.Collections.Generic;

namespace ClientLib {
	public class User {
		public enum ErrorName : byte{ None, BannedName, ContainsBannedCharacter}
		public enum ErrorColor : byte { None, BannedColor}

		const byte MAX_NAME_LENGTH = 16;
		Func<char, bool> IsBannedSymbol = (a) => !char.IsLetterOrDigit(a);
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

		public ErrorName IsAllowedName(string name) {
			if (bannedNames.Contains(name.ToLower()) || name.Length > MAX_NAME_LENGTH)
				return ErrorName.BannedName;

			for (byte i = 0; i < name.Length; ++i)
				if (IsBannedSymbol(name[i]))
					return ErrorName.ContainsBannedCharacter;

			return ErrorName.None;
		}

		public ErrorColor IsAllowedColor(ConsoleColor color) {
			if (bannedColors.Contains(color))
				return ErrorColor.BannedColor;

			return ErrorColor.None;
		}
	}
}