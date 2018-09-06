using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace olxParser {
	class Flat {
		public string text1 { get; set; }
		public string text2 { get; set; }
		public string text3 { get; set; }
		public string text4 { get; set; }

		public Flat(string text1, string text2, string text3, string text4) {
			this.text1 = text1;
			this.text2 = text2;
			this.text3 = text3;
			this.text4 = text4;
		}
	}
}
