using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleOOPMenu {
	public class ConfigurableMenuState : MenuState {
		private Dictionary<int, MenuItem> menus = new Dictionary<int, MenuItem>();
		private Dictionary<int, Func<IState>> transitions = new Dictionary<int, Func<IState>>();

		protected override Dictionary<int, MenuItem> Menus => menus;

		protected override IState NextState(KeyValuePair<int, MenuItem> selectedMenu) {
			return transitions[selectedMenu.Key]();
		}

		public void AddMenuItem(int id, MenuItem menu, Func<IState> nextState) {
			menus.Add(id, menu);
			transitions.Add(id, nextState);
		}
	}
}
