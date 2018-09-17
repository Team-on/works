using System;
using System.IO;
using System.Text;
using System.Collections.Generic;
using System.Threading;

using ConsoleOOPMenu;

namespace Bank {
    class MainState : MenuState {
        const int seconds = 10;

        private Dictionary<int, MenuItem> _menus = new Dictionary<int, MenuItem>() {
            {1, new MenuItem(){Text = "Add money instantly"}},
            {2, new MenuItem(){Text = $"Add money during {seconds} sec"}},
            {3, new MenuItem(){Text = "Take money instantly"}},
            {4, new MenuItem(){Text = $"Take money during {seconds} sec"}},
            {0, new MenuItem(){Text = "Exit"}},
        };
        protected override Dictionary<int, MenuItem> Menus => _menus;

        public override IState RunState() {
            Console.Clear();
            return base.RunState();
        }

        Bank bank;

        public MainState() {
            bank = new Bank();

            System.Timers.Timer t = new System.Timers.Timer() {
                Interval = 100,
                AutoReset = true,
            };
            t.Elapsed += (a, b) => {
                var prevl = Console.CursorLeft;
                var prevt = Console.CursorTop;
                Console.CursorLeft = Console.CursorTop = 0;
                Console.Write($"Money: {bank.BalanceUnsync}");
                Console.CursorTop = prevt;
                Console.CursorLeft = prevl;
            };
            t.Start();
        }

        protected override IState NextState(KeyValuePair<int, MenuItem> selectedMenu) {
            if (selectedMenu.Key == 0) return null;

            int money;
            do
                Console.Write("Money count: ");
            while (!int.TryParse(Console.ReadLine(), out money));

            if (selectedMenu.Key == 1) {
                bank.AddMoney(money, 0);
                return this;
            }
            if (selectedMenu.Key == 2) {
                bank.AddMoney(money, seconds);
                return this;
            }
            if (selectedMenu.Key == 3) {
                bank.TakeMoney(money, 0);
                return this;
            }
            if (selectedMenu.Key == 4) {
                bank.TakeMoney(money, seconds);
                return this;
            }
            return this;
        }
    }

    class Bank {
        ThreadLocker.ThreadLocker locker = new ThreadLocker.ThreadLocker();
        int balance;
        public int Balance {
            get {
                locker.Lock();
                int rez = balance;
                locker.Unlock();
                return rez;
            }
            set {
                locker.Lock();
                balance = value;
                locker.Unlock();
            }
        }

        public int BalanceUnsync => balance;

        string filename = @".\bank.txt";

        public Bank() {
            locker.Lock();
            ReadFile();
            locker.Unlock();
        }

        //Синхронізує через свойство
        public void TakeMoney(int count, int time) {
            Thread t = new Thread(() => {
                if (locker.IsUsed()) {
                    new MenuItem() {Text = "Error. Already used", TextColor=ConsoleColor.Red }.Print();
                    return;
                }

                locker.Lock();
                if (time == 0)
                    balance -= count;
                else {
                    int timeout = (int)(time / 10.0 * 1000);
                    for (byte i = 0; i < 10; ++i) {
                        balance -= count / 10;
                        Thread.Sleep(timeout);
                    }
                }

                WriteFile();
                locker.Unlock();
            });
            t.Start();
        }

        //Синхронізує в обход свойства
        public void AddMoney(int count, int time) {
            Thread t = new Thread(() => {
                if (locker.IsUsed()) {
                    new MenuItem() { Text = "Error. Already used", TextColor = ConsoleColor.Red }.Print();
                    return;
                }

                locker.Lock();

                if (time == 0) {
                    balance += count;
                }
                else {
                    int timeout = (int)(time / 10.0 * 1000);
                    for (byte i = 0; i < 10; ++i) {
                        balance += count / 10;
                        Thread.Sleep(timeout);
                    }
                }

                WriteFile();
                locker.Unlock();
            });
            t.Start();
        }

        void ReadFile() {
            int val = 0;
            using (var sr = new StreamReader(filename))
                val = int.Parse(DeCrypt(sr.ReadToEnd()));

            balance = val;
        }

        void WriteFile() {
            var val = balance;

            using (var sw = new StreamWriter(filename, false))
                sw.Write(Crypt(val.ToString()));
        }

        Random random = new Random();
        string key = "Hk~m1^ASnjj/*_ASVIaisg";

        //Шифрування через XOR
        // Додаю 1 випадковий символ на початок і 2 в кінець
        string Crypt(string a) {
            StringBuilder encrypt = new StringBuilder(a.Length + 3, a.Length + 3);
            encrypt.Append((char)random.Next(2, 130));
            for (byte i = 0; i < a.Length; i++)
                encrypt.Append((char)(a[i] ^ key[i % key.Length]));
            encrypt.Append((char)random.Next(0, 255));
            encrypt.Append((char)random.Next(130, 200));
            return encrypt.ToString();
        }

        string DeCrypt(string a) {
            StringBuilder decrypt = new StringBuilder(a.Length - 3, a.Length - 3);
            for (byte i = 0; i < a.Length - 3; i++)
                decrypt.Append((char)(a[i + 1] ^ key[i % key.Length]));
            return decrypt.ToString();
        }
    }

    class Program {
        static void Main(string[] args) {
            IState startState = new MainState();
            while (startState != null)
                startState = startState.RunState();
        }
    }
}
