using System;
using System.Collections;

namespace homm {
	class logBattle {
		ArrayList log;

		public logBattle() {
			log = new ArrayList(32);
		}

		public void LogNewLine(object o) {
			if (log.Count >= 30)
				log.RemoveRange(0, 10);
			log.Add(o.ToString());
		}

		public void LogAddToLine(object o) {
			log[log.Count - 1] = log[log.Count - 1].ToString() + o.ToString();
		}

		public void PrintLog(Coord pos, byte cnt, byte maxLength) {
			Console.ForegroundColor = ConsoleColor.White;
			Console.BackgroundColor = ConsoleColor.Black;

			++cnt;
			Console.SetCursorPosition(pos.x, pos.y);
			for (byte i = 1; i < cnt; ++i) {
				if (log.Count - i < 0)
					return;
				if (((string)log[log.Count - i]).Length > maxLength)
					Console.Write(((string)log[log.Count - i]).Substring(0, maxLength));
				else {
					Console.Write(log[log.Count - i]);
					Console.Write(new string(' ', 50 - ((string)log[log.Count - i]).Length));
				}
				Console.SetCursorPosition(pos.x, ++pos.y);
			}
		}

		public void Clear() {
			log.Clear();
		}
	}

	class SingleLogBattle {
		static public logBattle log { private set; get; }

		static SingleLogBattle() {
			log = new logBattle();
		}
	}
}
