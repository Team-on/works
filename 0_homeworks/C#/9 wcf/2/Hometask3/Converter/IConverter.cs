using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace Converter {
	[ServiceContract]
	public interface IConverter {
		[OperationContract]
		ConvertedUnits LinearMeasure(double meters);

		[OperationContract]
		ConvertedUnits CelsiusToFahrenheit(double c);

		[OperationContract]
		ConvertedUnits FahrenheitToCelsius(double f);
	}
}
