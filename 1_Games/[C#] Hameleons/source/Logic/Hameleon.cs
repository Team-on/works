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
				//Log.log.LogNewLine("Logic! " + Color.ToString() + "\t\t" + currCnt.ToString() + "/" + cntToMove.ToString());

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

					if (HameleonCommander.meatingSpot1 != null) {
						HameleonCommander.meatingSpot2 = this;
					}
					else {
						HameleonCommander.meatingSpot1 = this;
						while (HameleonCommander.meatingSpot2 == null) ;

						ConsoleColor c1 = HameleonCommander.meatingSpot1.Color, c2 = HameleonCommander.meatingSpot2.Color;
						/*
							Blue
							Red
							White
							Yellow
						 */
						if (c1.ToString()[0] > c2.ToString()[0]) {
							var tmp = c2;
							c2 = c1;
							c1 = tmp;
						}
						if (c1 == ConsoleColor.Blue && c2 == ConsoleColor.Blue)
							HameleonCommander.meatingSpot1.Color = HameleonCommander.meatingSpot2.Color = ConsoleColor.Red;
						else if (c1 == ConsoleColor.Blue && c2 == ConsoleColor.Red)
							HameleonCommander.meatingSpot1.Color = HameleonCommander.meatingSpot2.Color = ConsoleColor.White;
						else if (c1 == ConsoleColor.Blue && c2 == ConsoleColor.White)
							HameleonCommander.meatingSpot1.Color = HameleonCommander.meatingSpot2.Color = ConsoleColor.Yellow;
						else if (c1 == ConsoleColor.Blue && c2 == ConsoleColor.Yellow)
							HameleonCommander.meatingSpot1.Color = HameleonCommander.meatingSpot2.Color = ConsoleColor.Yellow;

						else if (c1 == ConsoleColor.Red && c2 == ConsoleColor.Red)
							HameleonCommander.meatingSpot1.Color = HameleonCommander.meatingSpot2.Color = ConsoleColor.White;
						else if (c1 == ConsoleColor.Red && c2 == ConsoleColor.White)
							HameleonCommander.meatingSpot1.Color = HameleonCommander.meatingSpot2.Color = ConsoleColor.Yellow;
						else if (c1 == ConsoleColor.Red && c2 == ConsoleColor.Yellow)
							HameleonCommander.meatingSpot1.Color = HameleonCommander.meatingSpot2.Color = ConsoleColor.Blue;

						else if (c1 == ConsoleColor.White && c2 == ConsoleColor.White)
							HameleonCommander.meatingSpot1.Color = HameleonCommander.meatingSpot2.Color = ConsoleColor.Yellow;
						else if (c1 == ConsoleColor.White && c2 == ConsoleColor.Yellow)
							HameleonCommander.meatingSpot1.Color = HameleonCommander.meatingSpot2.Color = ConsoleColor.Red;

						else if (c1 == ConsoleColor.Yellow && c2 == ConsoleColor.Yellow)
							HameleonCommander.meatingSpot1.Color = HameleonCommander.meatingSpot2.Color = ConsoleColor.Blue;
						else
							HameleonCommander.meatingSpot1.Color = HameleonCommander.meatingSpot2.Color = ConsoleColor.Green;/*Bug color*/

						SharedMutex.console.WaitOne();
						foreach (var i in new[] { HameleonCommander.meatingSpot1, HameleonCommander.meatingSpot2 }) {
							Console.CursorLeft = i.pos.x;
							Console.CursorTop = i.pos.y;
							Console.ForegroundColor = i.Color;
							Console.Write('@');
						}
						SharedMutex.console.ReleaseMutex();

						HameleonCommander.meatingSpot1 = HameleonCommander.meatingSpot2 = null;
						--HameleonCommander.MeatingCounter;
					}
				}

				if (pos.x == 10 && move.x < 0) {
					move.x = (short)-move.x;
					move.y = (short)-move.y;
				}

				if (HameleonCommander.MeatingCounter == 0) {
					//Console.Write("abort");
					System.Threading.Thread.CurrentThread.Abort();
				}


				//int pause = r.Next(0, 100);
				//if (pause >= 20)
				System.Threading.Thread.Sleep(r.Next(0, 100));
				//else //if (pause >= 50)
				//	System.Threading.Thread.Sleep(r.Next(100, 300));
				//else if (pause >= 20)
				//	System.Threading.Thread.Sleep(r.Next(50, 400));
				//else
				//	System.Threading.Thread.Sleep(r.Next(400, 1000));
			}
		}
	}
}
