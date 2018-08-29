using System;
using System.Collections.Generic;

namespace ConsoleOOPMenu{
	public abstract class MenuState : IState {
		protected abstract Dictionary<int, MenuItem> Menus { get; }

		protected MenuItem PreReadMessage;
		protected MenuItem ErrorNonexist;
		protected MenuItem ErrorNonnumber;

		public MenuState() {
			PreReadMessage = new MenuItem() {
				Text = "\nPlease, select option:\n"
			};

			ErrorNonexist = new MenuItem() {
				Text = "Selected item notexists.\n",
				PreText = "ERROR:",
				PreTextColor = ConsoleColor.Red,
			};

			ErrorNonnumber = new MenuItem() {
				Text = "Selected item not a number.\n",
				PreText = "ERROR:",
				PreTextColor = ConsoleColor.Red,
			};
		}

		protected virtual void ShowMenu() {
			foreach(var m in Menus) {
				Console.Write($"[{m.Key}] - ");
				m.Value.Print();
				Console.WriteLine();
			}
		}

		protected virtual KeyValuePair<int, MenuItem> ReadOption() {
			PreReadMessage.Print();
			ShowMenu();

			var str = Console.ReadLine();
			Console.WriteLine();

			if(byte.TryParse(str, out byte answerId)) {
				if(!Menus.ContainsKey(answerId)) {
					ErrorNonexist.Print();
					return ReadOption();
				}
				return new KeyValuePair<int, MenuItem>(answerId, Menus[answerId]);
			}
			else {
				ErrorNonnumber.Print();
				return ReadOption();
			}
		}

		public virtual IState RunState() {
			var option = ReadOption();
			return NextState(option);
		}

		protected abstract IState NextState(KeyValuePair<int, MenuItem> selectedMenu);
	}
}
