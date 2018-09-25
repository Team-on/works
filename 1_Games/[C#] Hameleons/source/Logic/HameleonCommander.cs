using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace Hameleons {
	class HameleonCommander {
		public static Hameleon meatingSpot1;
		public static Hameleon meatingSpot2;

		public Hameleon[] hameleons;

		static Mutex meatingMutex;
		static ushort meatingCounter;
		public static ushort MeatingCounter {
			get {
				meatingMutex.WaitOne();
				ushort rez = meatingCounter;
				meatingMutex.ReleaseMutex();
				return rez;
			}
			set {
				meatingMutex.WaitOne();
				meatingCounter = value;
				meatingMutex.ReleaseMutex();
			}
		}

		static HameleonCommander() {
			meatingSpot1 = null;
			meatingSpot2 = null;
			meatingMutex = new Mutex();
			meatingCounter = 0;
		}

		public HameleonCommander() {
			hameleons = new Hameleon[] {
				new Hameleon(ConsoleColor.Red,      new Point(10, 2),   new Point(1, 0),    1),
				new Hameleon(ConsoleColor.Blue, new Point(10, 3), new Point(1, 0), 2),
				new Hameleon(ConsoleColor.Yellow, new Point(10, 4), new Point(1, 0), 1),
				new Hameleon(ConsoleColor.White, new Point(10, 5), new Point(1, 0), 2)
			};
		}

		public void Start(ushort meatingCounter) {
			HameleonCommander.meatingCounter = meatingCounter;

			foreach (var h in hameleons) {
				AddHameleon(h);
			}
		}

		void AddHameleon(Hameleon h) {
			//try {
			//System.Timers.Timer t = new System.Timers.Timer() {
			//	AutoReset = true,
			//	Interval = 100,
			//};
			//t.Elapsed += (a, b) => h.StartLogic();
			//t.Start();
			Thread t = new Thread(h.StartLogic);
			t.Start();
			//}
			//catch(Exception ex) {
			//Console.WriteLine(ex.Message);
			//}
		}
	}
}
