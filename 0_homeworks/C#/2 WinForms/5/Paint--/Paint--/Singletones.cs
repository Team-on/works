using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Paint__ {
	static class Singletones {
		public static PalitreColor palitreColor = new PalitreColor();
		public static PalitrePickFigure palitrePickFigure = new PalitrePickFigure();
		public static FigureLayers figureLayers = new FigureLayers();
		public static PaintWindow mainWindow;

	}
}
