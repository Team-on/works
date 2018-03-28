using System;

namespace TeamCommander {
	class Program {
		static void Main(string[] args) {
			Output.Output screen = new Output.Output(new Support.Coord(5,5), new Support.Coord(100, 40));
			for (short i = 0; i < 40; ++i)
				for (short j = 0; j < 100; ++j)
					screen[i, j] = new Output.OutputObj('_', new Output.DColor());
			

			Elements.ElementsDirector director = new Elements.ElementsDirector(screen);

			Elements.ElementText text = new Elements.ElementText();
			Output.OutputObj[] tmp = new Output.OutputObj[20];
			for (int i = 0; i < tmp.Length; ++i)
				tmp[i] = new Output.OutputObj('*');
			tmp[5].sym = '\n';

			text.SetElement(tmp, new Support.Coord(0, 10), 5);

			director.AddElement(text);
			director.AddElement(new Elements.ElementHLine(40, new Output.OutputObj('╟'), new Support.Coord(10, 0), 3));

			director.Init();
			director.PrintElementsEternal();
			director.PrintElements();

			director.PrintScreen();

			//director.ClearElements();
			director.PrintScreen();
		}
	}
}
