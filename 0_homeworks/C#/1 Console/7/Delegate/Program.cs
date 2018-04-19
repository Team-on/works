using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Delegate {
	/*Завдання. Розробити клас "Хак" який би генерував набір логінів ( логіни тільки генеруються із голосних букв, наперед відомо, що логін може містити від трьох до чотирьох символів) та паролів (паролі тільки генеруються із цифер, наперед відомо, що пароль може містити чотири цифри) та дозволяв би здійснювати їх комбінацію для брутфрсного взлому сервіса, робота якого описується в класі "Сервіс". Реалізувати відповідні методи, властивості, тощо для роботи з класом. Клас повинен обовязково містити метод розсилкі неправдивої інформації, яка повинна розповсюджуватися через взломаний сервіс.

Клас "Сервіс" містить в собі список розсилкі цінної інформації про фондові біржі. З сервісом можуть працювати два типи клієнтів: Клієнт який надає інформацію (інформація надається шляхом добавлення клієнтського медоду відправки Send  у груповий делегат) та клієнт який підписаний на розсилку (клієнт має метод Recv для зчитування інформації шляхом виклику переданого в параметрі групового делегату). Клас містить метод аутентифікації який приймає два параметри логін та пароль та повертає 1 якщо вірний лише логін, 2 якщо вірний лише пароль, 0 якщо вірний і логін і пароль. Доступ до функціоналу сервісу можливий лише тоді коли пройдено аутентифікацію. Якщо введено 10 раз не вірні дані сервіс повинен призупинити роботу на 3 секунди.Реалізувати відповідні методи, властивості, тощо для роботи з класом.

Класи клієнтів повинні містити відповідно методи send та recv і інші методи які забезпечували б їх нормальну роботу.

При написанні програми обовязково використовувати необхідні колекції, делегати...*/

	interface IServise {
		void Register(Client client, string login, string pass);
		byte Login(string login, string pass);
		void Logout();
	}

	class Service : IServise {
		public delegate void Message();
		Message message;
		bool isLogin;

		List<Client> clients;
		Dictionary<string, string> logins;

		byte invalideLoginsCnt;

		public Service() {
			clients = new List<Client>(25);
			logins = new Dictionary<string, string>(25);
		}

		public void Register(Client client, string login, string pass) {
			clients.Add(client);
			logins.Add(login, pass);
		}

		public byte Login(string login, string pass) {
			foreach(var i in logins) {
				if(i.Key == login && i.Value == pass) {
					isLogin = true;
					invalideLoginsCnt = 0;
					return 0;
				}
				if (i.Key == login) {
					++invalideLoginsCnt;
					return 1;
				}
				if (i.Value == pass) {
					++invalideLoginsCnt;
					return 2;
				}
			}
			return 255;
		}

		public void Logout() {
			isLogin = false;
		}

		public void AddMessage(Message toAdd) {
			if(isLogin)
				message += toAdd;
		}

		Message GetMessage() {
			if(isLogin)
				return message;
			return null;
		}

		public void SendClientsMessage() {
			if (!isLogin)
				return;
			foreach(var i in clients) 
				if (i is ClientSender)
					message += ((ClientSender)(i)).Send();
		}

		public void RecvClientsMessage() {
			if (!isLogin)
				return;
			foreach (var i in clients)
				if (i is ClientReciver)
					((ClientReciver)(i)).Recv(message);
		}

		public void PrintClientsMessage() {
			if (!isLogin)
				return;
			message = null;
			foreach (var i in clients)
				if (i is ClientReciver) {
					((ClientReciver)(i)).PrintRecv();
					Console.WriteLine();
				}
		}
	}

	class Client {
		static uint id;
		protected uint clientId;

		static Client() {
			id = 0;
		}

		public Client() {
			clientId = id++;
		}
	}

	class ClientSender : Client {
		public Service.Message Send() {
			return new Service.Message( () => Console.WriteLine("Message from" + base.clientId.ToString()));
		}
	}

	class ClientReciver : Client {
		Service.Message sms;
		public void Recv(Service.Message Sms) {
			sms += Sms;
		}

		public void PrintRecv() {
			Console.WriteLine(base.clientId.ToString() + " get this messages: ");
			sms();
		}
	}

	class Hack {
		string login;
		ushort pass;
		bool rLogin, rPass, loginWith4 = false;

		sbyte[] currLoginLet = new sbyte[4] {0,0,0,-1 };
		string golosni = "aeiouy";

		public void Brutforse(IServise serv) {
			login = golosni[currLoginLet[0]].ToString() + golosni[currLoginLet[1]].ToString() + golosni[currLoginLet[2]].ToString() + 
				(currLoginLet[3] != -1? golosni[currLoginLet[3]].ToString() : "" );
			pass = 1111;
			rLogin = rPass = false;

			byte rez = 255;
			do {
				rez = serv.Login(login, pass.ToString());
				if (rez == 1)
					rLogin = true;
				if (rez == 2)
					rPass = true;
				if (!rPass)
					++pass;
				if (!rLogin)
					ChangeLogin();
			} while (rez != 0);

			serv.Login(login, pass.ToString());
			((Service)(serv)).AddMessage(()=>Console.WriteLine("Hacker message"));
			serv.Logout();
		}

		void ChangeLogin() {
			if (currLoginLet[0] == golosni.Length - 1 && currLoginLet[1] == golosni.Length - 1 && currLoginLet[2] == golosni.Length - 1) {
				loginWith4 = true;
				currLoginLet = new sbyte[4] { 0, 0, 0, 0 };
			}
			if (!loginWith4) {
				++currLoginLet[2];
				for (int i = currLoginLet.Length - 1; i >= 0; --i) {
					if (currLoginLet[i] >= golosni.Length - 1) {
						++currLoginLet[i - 1];
						currLoginLet[i] = 0;
					}
				}
			}
			else {
				++currLoginLet[3];
				for (int i = currLoginLet.Length - 1; i >= 0 ; --i) {
					if (currLoginLet[i] >= golosni.Length - 1) {
						++currLoginLet[i - 1];
						currLoginLet[i] = 0;
					}
				}
			}

			login = golosni[currLoginLet[0]].ToString() + golosni[currLoginLet[1]].ToString() + golosni[currLoginLet[2]].ToString() +
				(currLoginLet[3] != -1 ? golosni[currLoginLet[3]].ToString() : "");
		}
	}

	class Program {
		static void Main(string[] args) {
			Random rnd = new Random();

			Service serv = new Service();
			serv.Register(new Client(), "admin", "admin");
			serv.Register(new Client(), "aae", "1122");

			Client[] clients = new Client[10];
			for(byte i = 0; i < clients.Length; ++i) {
				try {
					if (i < clients.Length - 3)
						clients[i] = new ClientSender();
					else
						clients[i] = new ClientReciver();
					string golosni = "aeiouy";
					serv.Register(clients[i], golosni[rnd.Next(0, golosni.Length)].ToString() + golosni[rnd.Next(0, golosni.Length)].ToString() + golosni[rnd.Next(0, golosni.Length)].ToString() + (rnd.Next(0, 2) == 0 ? golosni[rnd.Next(0, golosni.Length)].ToString() : ""), rnd.Next(1111, 9999).ToString());
				}
				catch(Exception exc) {

				}
			}

			Hack hack = new Hack();
			hack.Brutforse(serv);

			serv.Login("admin", "admin");
			serv.SendClientsMessage();
			serv.RecvClientsMessage();
			serv.PrintClientsMessage();
			serv.Logout();



		}
	}
}
