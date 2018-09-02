using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleOOPMenu {
	public class AutoConfigurableMenuState : ConfigurableMenuState {
		private int currMaxId;

		public AutoConfigurableMenuState() {
			currMaxId = 0;
		}

		public void AddMenuItem(MenuItem menu, Func<IState> nextState) {
			base.AddMenuItem(++currMaxId, menu, nextState);
		}

		private new void AddMenuItem(int id, MenuItem menu, Func<IState> nextState) {
			base.AddMenuItem(id, menu, nextState);
		}
	}
}
