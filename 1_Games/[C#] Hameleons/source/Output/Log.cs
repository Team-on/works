using System;
using System.Collections;

namespace Hameleons {
	class Log {
		static public logBattle log { private set; get; }

		static Log() {
			log = new logBattle();
		}
	}

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

		public void PrintLog(Point pos, byte cnt, byte maxLength) {
			Point startPos = pos;
			Console.ForegroundColor = ConsoleColor.White;
			Console.BackgroundColor = ConsoleColor.Black;

			++cnt;
			Console.SetCursorPosition(pos.x, pos.y);
			for (byte i = 1; i < cnt; ++i) {
				if (pos.y - startPos.y == cnt)
					break;
				if (log.Count - i < 0)
					return;
				if (((string)log[log.Count - i]).Length > maxLength) {
					Console.Write(((string)log[log.Count - i]).Substring(0, maxLength));
					Console.SetCursorPosition(pos.x, ++pos.y);
					Console.Write(((string)log[log.Count - i]).Substring(maxLength, ((string)log[log.Count - i]).Length - maxLength));
					Console.Write(new string(' ', maxLength - (((string)log[log.Count - i]).Length - maxLength)));
				}
				else {
					Console.Write(log[log.Count - i]);
					Console.Write(new string(' ', maxLength - ((string)log[log.Count - i]).Length));
				}
				Console.SetCursorPosition(pos.x, ++pos.y);
			}
		}

		public void Clear() {
			log.Clear();
		}
	}

}
