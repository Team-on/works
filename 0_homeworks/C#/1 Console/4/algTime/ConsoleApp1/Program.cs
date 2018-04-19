using System;
using System.Diagnostics;
using System.Threading;

namespace ConsoleApp1{

    class Program{

        static void Main(string[] args){
			double[,] b = new double[3, 4];
            
				Random r = new Random();
				for (byte i = 0; i < 3; ++i) {
					for (byte j = 0; j < 4; ++j) {
						b[i, j] = r.NextDouble() * 10;
						Console.Write($"{b[i, j]:N1} ");
					}
					Console.WriteLine();
				}
				Console.WriteLine();


            /*
            
            Stopwatch time = new Stopwatch();
            time.Start();
			for (byte i = 0; i < 3; ++i)
				for (byte j = 0; j < 4; ++j) 
					if (b[min >> 4, min & 0b00001111] > b[i, j])
						min = (byte)((i << 4) | j);

            time.Stop();
            Console.WriteLine(time.Elapsed);
			
            */

            const int testCnt = 1000000;
            byte mi = 0, mj = 0;
            byte min = 0;
            System.Int64 cnt = 0;
            Stopwatch time = new Stopwatch();
            for (int k = 0; k < testCnt; ++k){
                min = 0;
                mi = mj = 0;
                for (byte i = 0; i < 3; ++i)
                    for (byte j = 0; j < 4; ++j)
                        b[i, j] = r.NextDouble() * 10;
                time.Start();
                ///*
                for (byte i = 0; i < 3; ++i)
                    for (byte j = 0; j < 4; ++j)
                        if (b[mi, mj] > b[i, j])
                        {
                            mi = i;
                            mj = j;
                        }
                //*/
                /*
                for (byte i = 0; i < 3; ++i)
                    for (byte j = 0; j < 4; ++j)
                        if (b[min >> 4, min & 0b00001111] > b[i, j])
                            min = (byte)((i << 4) | j);
                */
                time.Stop();
                cnt += time.ElapsedMilliseconds;
                time.Restart();
                //Console.WriteLine(time.Elapsed);
                //Console.WriteLine("Min: {0:N1}", b[min >> 4, min & 0b00001111]);
                //Console.WriteLine("Min: {0:N1}", b[mi, mj]);
            }
            Console.WriteLine((double)(cnt) / testCnt);
        }
    }
}