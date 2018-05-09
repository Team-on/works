using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodeStudio {
	static class Settings {
		static public SettingsNonSingletone settings = new SettingsNonSingletone();
	}

	sealed class SettingsNonSingletone {
		public byte tabLength = 4;
	}
}
