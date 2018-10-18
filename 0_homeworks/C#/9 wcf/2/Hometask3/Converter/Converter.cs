using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace Converter {
	// NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in both code and config file together.
	public class Converter : IConverter {
		public ConvertedUnits CelsiusToFahrenheit(double c) {
			return new ConvertedUnits() {
				Celsius = c,
				Fahrenheit = c * 9 / 5 + 32,
			};
		}

		public ConvertedUnits FahrenheitToCelsius(double f) {
			return new ConvertedUnits() {
				Celsius = (f - 32) * 5 / 9,
				Fahrenheit = f,
			};
		}

		public ConvertedUnits LinearMeasure(double meters) {
			return new ConvertedUnits() {
				Foot = meters * ConvertedUnits.FootInMeter,
				Inch = meters * ConvertedUnits.InchInMeter,
				Yard = meters * ConvertedUnits.YardInMeter,
			};
		}
	}
}
