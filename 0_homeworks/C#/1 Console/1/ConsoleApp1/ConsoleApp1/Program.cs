using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1{
    class Program{

        static  void z1() {
            Console.Write("Str: ");
            string str = "";
            int tmp;
            int space = 0;
            while ((tmp = Console.Read()) != '.'){
                if (tmp == ' ')
                    ++space;
                str += (char)tmp;
            }

            Console.WriteLine(str);
            Console.WriteLine($"Space: {space}");
        }

        static void z2()
        {
            Console.Write("6-digit: ");
            int tmp;
            while (!System.Int32.TryParse(Console.ReadLine(), out tmp)) ;
            if (tmp < 100000 || tmp > 999999)
                return;
            Console.WriteLine(tmp % 10 + tmp % 100 / 10 + tmp % 1000 / 100 == tmp / 1000 % 10 + tmp / 10000 % 10 + tmp / 100000 % 10);
        }

        static void z3()
        {
            Console.Write("Symbols: ");
            string tmp = "";
            for (int buff = Console.Read(); buff != '\n'; buff = Console.Read())
            {
                if (char.IsLower((char)buff))
                    tmp += char.ToUpper((char)buff);
                else if (char.IsUpper((char)buff))
                    tmp += char.ToLower((char)buff);
                else
                    tmp += (char)buff;
            }
            Console.WriteLine(tmp);
        }

        static void z4()
        {
            System.Int32 a, b;
            Console.Write("A: ");
            while (!System.Int32.TryParse(Console.ReadLine(), out a));
            Console.Write("B: ");
            while (!System.Int32.TryParse(Console.ReadLine(), out b)) ;
            if(a > b)
            {
                System.Int32 tmp = a;
                a = b;
                b = tmp;
            }
                
            ++b;
            for (System.Int32 i; a != b; ++a){
                for (i = 0; i < a; ++i)
                    Console.Write("{0}  ", a);
                Console.WriteLine();
            }
        }

        static void z5()
        {
            string tmp;
            Console.Write("Number: ");
            tmp = Console.ReadLine();
            Console.Write("Rev: ");
            for (int i = tmp.Length - 1; i >= 0; --i)
                Console.Write(tmp[i]);
            Console.WriteLine();
        }

        static void Main(string[] args){
            //z1(); Console.WriteLine();
            //z2(); Console.WriteLine();
            //z3(); Console.WriteLine();
            //z4(); Console.WriteLine();
            //z5(); Console.WriteLine();


        }
    }
}
