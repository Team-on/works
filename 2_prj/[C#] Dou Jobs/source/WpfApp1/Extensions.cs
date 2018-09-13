using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1 {
	static class Extensions {
		public static char LastChar(this string s) {
			return s[s.Length - 1];
		}

		public static string ClearFromHTML(this string s) {
			return s.Replace("&amp;", "").Replace("&nbsp;", "");
		}
	}
}
