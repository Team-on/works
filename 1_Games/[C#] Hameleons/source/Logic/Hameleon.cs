using System;

namespace Hameleons {
	class Hameleon {
		Random r = new Random();

		public ConsoleColor Color { get; set; }
		public Point Pos => pos;

		Point pos;
		Point move;
		short currCnt;
		short cntToMove;

		public Hameleon(ConsoleColor color, Point pos, Point move, short cntToMove) {
			this.currCnt = 0;

			Color = color;
			this.pos = pos;
			this.move = move;
			this.cntToMove = cntToMove;
		}

		public void StartLogic() {
			SharedMutex.console.WaitOne();
			Console.CursorLeft = pos.x;
			Console.CursorTop = pos.y;
			Console.ForegroundColor = Color;
			Console.BackgroundColor = ConsoleColor.Black;
			Console.Write('@');
			SharedMutex.console.ReleaseMutex();

			while (true) {
				++currCnt;
				Log.log.LogNewLine("Logic! " + Color.ToString() + "\t\t" + currCnt.ToString() + "/" + cntToMove.ToString());

				if (currCnt == cntToMove) {
					currCnt = 0;

					SharedMutex.console.WaitOne();

					Console.CursorLeft = pos.x;
					Console.CursorTop = pos.y;
					Console.Write(' ');

					pos.x += move.x;
					pos.y += move.y;

					Console.CursorLeft = pos.x;
					Console.CursorTop = pos.y;
					Console.ForegroundColor = Color;
					Console.Write('@');

					SharedMutex.console.ReleaseMutex();
				}

				if (pos.x == 80 && move.x > 0) {
					move.x = (short)-move.x;
					move.y = (short)-move.y;

					//HameleonCommander.meatingSpot.WaitOne();

					//Wait another hameleon and change color
					//--HameleonCommander.MeatingCounter;

					//HameleonCommander.meatingSpot.Release();
				}

				if(pos.x == 10 && move.x < 0) {
					move.x = (short)-move.x;
					move.y = (short)-move.y;
				}

				if (HameleonCommander.MeatingCounter == 0) {
					//Console.Write("abort");
					System.Threading.Thread.CurrentThread.Abort();
				}

				int pause = r.Next(0, 10);
				if(pause >= 7) 
					System.Threading.Thread.Sleep(r.Next(0, 100));
				else if(pause >= 3) 
					System.Threading.Thread.Sleep(r.Next(50, 500));
				else 
					System.Threading.Thread.Sleep(r.Next(400, 1000));
			}
		}
	}
}
