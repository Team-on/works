using System;

namespace TeamCommander {
	namespace Settings {
		static class StandartColor {
			static public readonly Output.DColor color;

			static StandartColor() {
				color = new Output.DColor(ConsoleColor.White, ConsoleColor.Black);
			}
		}

	}
}
