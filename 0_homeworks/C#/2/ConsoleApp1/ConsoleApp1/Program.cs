using System;

//http://www.bestprog.net/ru/2016/08/08/02-%D0%B1%D0%B0%D0%B7%D0%BE%D0%B2%D1%8B%D0%B5-%D1%81%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D0%BD%D1%8B%D0%B5-%D0%B8%D0%BB%D0%B8-%D1%82%D0%B8%D0%BF%D1%8B-%D0%B7%D0%BD%D0%B0%D1%87%D0%B5%D0%BD%D0%B8/
//https://0.30000000000000004.com/

namespace ConsoleApp1
{

	class Point {
		public byte x, y;
		public Point() {
			x = y = 0;
		}
	}

	class Program
	{
		static void z1()
		{
			Console.WriteLine("\t\t\tZ1");
			int[] a = new int[5];
			double[,] b = new double[3, 4];

			for (byte i = 0; i < a.Length; ++i)
			{
				Console.Write("A[{0}]: ", i);
				while (!System.Int32.TryParse(Console.ReadLine(), out a[i])) ;
				//a[i] = i;
			}

			for (byte i = 0; i < a.Length; ++i)
				Console.Write($"{a[i]} ");
			Console.WriteLine();
			Console.WriteLine();

			{
				Random r = new Random();
				for (byte i = 0; i < 3; ++i)
				{
					for (byte j = 0; j < 4; ++j)
					{
						b[i, j] = r.NextDouble() * 10;
						Console.Write($"{b[i, j]:N1} ");
					}
					Console.WriteLine();
				}
				Console.WriteLine();
			}

			byte max = 0, min = 0;
			double sum = a[0], mul = a[0], spec = 0;
			for (byte i = 1; i < a.Length; ++i)
			{
				if (a[max] < a[i])
					max = i;
				if (a[min] > a[i])
					min = i;
				sum += a[i];
				mul *= a[i];
				if (i % 2 == 0)
					spec += a[i];
			}
			Console.WriteLine("A:");
			Console.WriteLine("Sum: {0}", sum);
			Console.WriteLine("Mult: {0}", mul);
			Console.WriteLine("Min: {0}", a[min]);
			Console.WriteLine("Max: {0}", a[max]);
			Console.WriteLine("Sum even: {0}\n", spec);

			byte maxx = 0, minn = 0;
			sum = spec = max = min = 0;
			mul = 1;

			for (byte i = 0; i < 3; ++i)
			{
				for (byte j = 0; j < 4; ++j)
				{

					if (b[maxx, max] < b[i, j])
					{
						max = j;
						maxx = i;
					}
					if (b[minn, min] > b[i, j])
					{
						min = j;
						minn = i;
					}

					sum += b[i, j];
					mul *= b[i, j];
					if (i % 2 == 1)
						spec += b[i, j];
				}
			}

			Console.WriteLine("B:");
			Console.WriteLine("Sum: {0:N1}", sum);
			Console.WriteLine("Mult: {0:N1}", mul);
			Console.WriteLine("Min: {0:N1}", b[minn, min]);
			Console.WriteLine("Max: {0:N1}\n", b[maxx, max]);
		}

		static void z2()
		{
			Console.WriteLine("\t\t\tZ2");
			int[] a, b, c;
			byte cSize = 0;
			a = new int[10];
			b = new int[10];
			c = new int[(a.Length < b.Length ? b.Length : a.Length)];
			Console.WriteLine("A:");
			for (byte i = 0; i < a.Length; ++i)
			{
				//a[i] = i;
				//b[i] = i + 7;
				a[i] = i % 2;
				b[i] = i % 3;
				Console.Write($"{a[i]} ");
			}
			Console.WriteLine("\nB:");
			for (byte i = 0; i < b.Length; ++i)
				Console.Write($"{b[i]} ");
			Console.WriteLine();

			for (byte i = 0; i < a.Length; ++i)
				for (byte j = 0; j < b.Length; ++j)
				{
					if (a[i] == b[j])
					{
						bool unrepeat = true;
						for (byte k = 0; k < cSize; ++k)
							if (a[i] == c[k])
							{
								unrepeat = false;
								break;
							}
						if (unrepeat)
							c[cSize++] = a[i];
						break;
					}
				}

			Console.WriteLine("\nC:");
			for (byte i = 0; i < cSize; ++i)
				Console.Write($"{c[i]} ");
			Console.WriteLine();
		}

		static void z3()
		{
			Console.Write("\t\t\tZ3\nStr: ");
			string str = Console.ReadLine();
			for (int i = 0, len = str.Length; i < len; ++i)
				if (char.ToLower(str[i]) != char.ToLower(str[len - 1 - i]))
				{
					Console.WriteLine("Non palindrome");
					return;
				}
			Console.WriteLine("Palindrome");
		}

		static void z4(){
			Console.Write("\t\t\tZ4\nStr: ");
			string str = Console.ReadLine();
			str += ' ';
			uint cnt = 0;
			for (int i = 1, len = str.Length; i < len; ++i)
				if (char.IsWhiteSpace(str[i]) && char.IsLetterOrDigit(str[i - 1]))
					++cnt;
			Console.WriteLine($"Words: {cnt}");
		}

		static void z5() {
			Console.WriteLine("\t\t\tZ5");
			Random rnd = new Random();
			SByte[,] mtx = new SByte[5, 5];

			Point min = new Point(), max = new Point();

			for (byte i = 0; i < mtx.GetLength(0); ++i) {
				for (byte j = 0; j < mtx.GetLength(1); ++j) {
					mtx[i, j] = (SByte)rnd.Next(-100, 101);
					if (mtx[i, j] < mtx[min.y, min.x]) {
						min.x = j;
						min.y = i;
					}
					if (mtx[i, j] >= mtx[max.y, max.x]) {
						max.x = j;
						max.y = i;
					}
					Console.Write($"{mtx[i, j],5}");
				}
				Console.WriteLine();
			}
			Console.WriteLine($"Max: {mtx[max.y, max.x]}");
			Console.WriteLine($"Min: {mtx[min.y, min.x]}");

			int sum = 0;
			if (min.y < max.y) {
				for (byte j = min.x; j < mtx.GetLength(1); ++j)
					sum += mtx[min.y, j];
				for (byte j = max.x; j < mtx.GetLength(1); ++j)
					sum += mtx[max.y, j];
			}
			for (byte i = (byte)(min.y + 1); i < max.y; ++i)
				for (byte j = 0; j < mtx.GetLength(1); ++j)
					sum += mtx[i, j];

			Console.WriteLine($"Sum: {sum}");
		}	

		static void Main(string[] args)
		{
			z1();
			z2();
			z3();
			z4();
			z5();
		}

	}
}