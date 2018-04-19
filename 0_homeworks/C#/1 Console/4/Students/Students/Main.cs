using System;

namespace Students{
    class Student {
        public static string numberPrefix;
        string Phone;

        public string name { get; set; }
        public string surname { get; set; }
        public string phone {
            get {return Phone;}
            set {
                if (value.Substring(0, (numberPrefix.Length)) != numberPrefix)
                    throw new ArgumentException("Bad numberPrefix");
                Phone = value;
            }
        }
    }

    class Journal{
        static public string[] lessons;

        Student[] std;
        //0 - Н
        //6 - прийшов, але без оцінки
        // інше оцінки
        byte[,] marks;
        UInt16 size;


        public Journal(){
            size = 0;
            std = new Student[10];
            marks = new byte[10, lessons.Length];
        }

        public void AddStudent(Student s){
            if (size == std.Length) {
                Student[] tmp = std;
                byte[,] tmpM = marks;
                std = new Student[size + 2];
                marks = new byte[size + 2, lessons.Length];
                for (UInt16 i = 0; i < size; ++i) {
                    std[i] = tmp[i];
                    for (byte j = 0; j < lessons.Length; ++j)
                        marks[i, j] = tmpM[i, j];
                }
            }
            std[size++] = s;
        }

        public bool AddMarks(UInt16 id, byte[] mark){
            if (id < 0 || id > size)
                return false;
            for (UInt16 i = 0; i < mark.Length && i < marks.GetLength(1); ++i)
                marks[id, i] = mark[i];
            return true;
        }

        private void PrintMark(byte mark){
            ConsoleColor prev = Console.ForegroundColor;
            switch (mark) {
                case 0:
                    Console.ForegroundColor = ConsoleColor.White;
                    break;
                case 6:
                    Console.ForegroundColor = Console.BackgroundColor;
                    break;
                case 1:
                    Console.ForegroundColor = ConsoleColor.Red;
                    break;
                case 2:
                    Console.ForegroundColor = ConsoleColor.DarkYellow;
                    break;
                case 3:
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    break;
                case 4:
                    Console.ForegroundColor = ConsoleColor.DarkGreen;
                    break;
                case 5:
                    Console.ForegroundColor = ConsoleColor.Green;
                    break;
            }
            if(mark != 0)
                Console.Write($"{mark,-5}");
            else
                Console.Write($"Н    ");
            Console.ForegroundColor = prev;
        }

        private double CalcAvgMark(UInt16 id){
            if (id < 0 || id > size)
                return -1;
            double avg = 0;
            int cnt = 0;
            byte curr;
            for (UInt16 i = 0; i < marks.GetLength(1); ++i)
            {
                curr = marks[id,i];
                if (curr != 0 && curr != 6)
                {
                    ++cnt;
                    avg += curr;
                }
            }
            return avg / cnt;
        }

        public void Print() {
            Console.Write("|  Id  |\tName\t|\tSurname\t|");
            for (byte i = 0; i < lessons.Length; ++i)
                Console.Write($" {lessons[i],-5} |");
            Console.Write(" Average |");
            int pos = Console.CursorLeft;
            Console.WriteLine();

            for (byte i = 0; i < pos; ++i)
                Console.Write("-");
            Console.WriteLine();

            for (UInt16 i = 0; i < size; ++i) {
                Console.Write("| {0,4} | {1,-14} | {2, -13} | ", i+1, std[i].name, std[i].surname);
                for (UInt16 j = 0; j < marks.GetLength(1); ++j) {
                    PrintMark(marks[i,j]);
                    Console.Write(" | ");
                }
                Console.Write("{0:0.##}\t| ", CalcAvgMark(i));
                Console.WriteLine();
            }
        }

        public bool GetFullInfo(UInt16 id)
        {
            if (id < 0 || id > size)
                return false;
            Console.WriteLine($"{std[id].name} {std[id].surname}");
            Console.WriteLine($"{std[id].phone,-15}");
            for (UInt16 j = 0; j < marks.GetLength(1); ++j){
                Console.Write($" {lessons[j]}:\t");
                PrintMark(marks[id, j]);
                Console.WriteLine();
            }
            Console.Write(" Avg:\t{0}", CalcAvgMark(id));
            return true;
        }
    }

    class FactoryStudent{
        static public Random r;
        static public string[] bName, gName, surname;

        public FactoryStudent(){
            //r = new Random();
        }

        public Student Create(){
            string tel = Student.numberPrefix + "98";
            for (int i = 0; i < 7; ++i)
                tel += r.Next(9);

            return new Student() { name = (r.Next(2) == 1 ? bName[r.Next(bName.Length)] : gName[r.Next(gName.Length)]),
                surname = surname[r.Next(surname.Length)],
                phone = tel
            };
        }

    }

    struct CInit{
        public void Init() {
            Console.SetWindowSize(150, 50);
            Console.ForegroundColor = ConsoleColor.White;
            Console.BackgroundColor = ConsoleColor.DarkMagenta;
            Console.Clear();
            //Console.SetWindowPosition(5, 5);

            Student.numberPrefix = "+380";


            FactoryStudent.bName = new string[] { "Vitaliy", "Sergiy", "Alexey", "Vlad", "Timofey" };
            FactoryStudent.gName = new string[] { "Alisa", "Yulia", "Dasha", "Diana", "Anna", "Nastya" };
            FactoryStudent.surname = new string[] { "Lesna", "Alpak", "Juma", "Naominacu", "Yaroshak" };
            FactoryStudent.r = new Random();

            Journal.lessons = new string[] {"Math","Lang","Chem","C#","Math"};
        }
    }

    class StudentsMain{
        static void Main(string[] args){
            {CInit init;
            init.Init();}

            Journal std = new Journal();

            FactoryStudent fct = new FactoryStudent();
            for (UInt16 i = 0; i < 15; ++i) {
                std.AddStudent(fct.Create());
                byte[] arr = new byte[Journal.lessons.Length];
                for (UInt16 j = 0; j < Journal.lessons.Length; ++j)
                    arr[j] =(byte)FactoryStudent.r.Next(7);
                std.AddMarks(i, arr);
            }

            System.UInt16 input;
            do
            {
                std.Print();
                Console.Write("=>");

                while(!System.UInt16.TryParse(Console.ReadLine(), out input));
                while (!std.GetFullInfo((UInt16)(input-1)));

                Console.ReadKey();
                Console.Clear();
            } while (true);

            
        }
    }
}

/*
+Генератор студентов
+Середній бал
+Кількість студентів
+Ид студента
+Телефон
+Відвідування
+Масив з предметами(0 - н, число - оцінка)
+Оцінки в цвете вивод

	ид имя  оцінки
	...
	...

	=> лупиш ид
	Вилазить инфа про студента

*/
