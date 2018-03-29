using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TeamCommander {
	namespace Elements {
		class ElementsDirector {
			Output.Output screen;

			System.Collections.Generic.List<Elements.Element> elements;

			public ElementsDirector(Output.Output Screen) {
				elements = new System.Collections.Generic.List<Elements.Element>(10);
				screen = Screen;
			}

			public void Init() {
				screen.Init();
			}

			public void AddElement(Elements.Element elem) {
				elem.OnPassIntoDirector(screen);
				elements.Add(elem);
			}

			public void PrintScreen() {
				screen.Print();
			}

			public void PrintElementsEternal() {
				foreach (var i in elements)
					if (i is EternalElement)
						i.Print();
			}

			public void PrintElements() {
				foreach (var i in elements)
					if (!(i is EternalElement))
						i.Print();
			}

			public void ClearElements() {
				foreach (var i in elements)
					if (!(i is EternalElement))
						i.Clear();
			}

		}
	}
}
