using System;
using System.Collections.Generic;

namespace ConsoleOOPMenu{
	public abstract class MenuState : IState {
		protected abstract Dictionary<int, MenuItem> Menus { get; }

		protected virtual void ShowMenu() {
			foreach(var m in Menus)
				Console.WriteLine($"[{m.Key}] - {m.Value.Text}");
		}

		protected virtual KeyValuePair<int, MenuItem> ReadOption() {
			Console.WriteLine("\nPlease, select option:");
			ShowMenu();

			var str = Console.ReadLine();
			Console.WriteLine();

			if(byte.TryParse(str, out byte answerId)) {
				if(!Menus.ContainsKey(answerId)) {
					Console.WriteLine("ERROR: Selected item notexists.");
					return ReadOption();
				}
				return new KeyValuePair<int, MenuItem>(answerId, Menus[answerId]);
			}
			else {
				Console.WriteLine("ERROR: Selected item not a number.");
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
