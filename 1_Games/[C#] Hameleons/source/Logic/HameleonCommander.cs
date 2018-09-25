using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace Hameleons {
	class HameleonCommander {
		public static Mutex meatingSpot;

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
			meatingSpot = new Mutex();
			meatingMutex = new Mutex();
			meatingCounter = 0;
		}

		public void Start(ushort meatingCounter) {
			HameleonCommander.meatingCounter = meatingCounter;

			AddHameleon(new Hameleon(ConsoleColor.Red,		new Point(10, 2),	new Point(1, 0),	1));
			AddHameleon(new Hameleon(ConsoleColor.Blue,		new Point(10, 3),	new Point(1, 0),	2));
			AddHameleon(new Hameleon(ConsoleColor.Yellow,	new Point(10, 4),	new Point(1, 0),	1));
			AddHameleon(new Hameleon(ConsoleColor.White,	new Point(10, 5),	new Point(1, 0),	2));
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
