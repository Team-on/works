using System;

namespace TeamCommander {
	namespace Settings {
		static class StandartColor {
			static public readonly Output.DColor color;

			static StandartColor() {
				color = new Output.DColor(ConsoleColor.White, ConsoleColor.Black);
			}
		}

		static class ScreenSettings {
			static public readonly Support.Coord size;

			static ScreenSettings() {
				size = new Support.Coord();
				size.x = (short)Console.LargestWindowWidth;
				size.y = (short)Console.LargestWindowHeight;
			}
		}
	}
}
