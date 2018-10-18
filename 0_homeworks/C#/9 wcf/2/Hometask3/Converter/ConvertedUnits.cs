using System;
using System.Runtime.Serialization;
using System.ServiceModel;

namespace Converter {
	[DataContract]
	public class ConvertedUnits {
		internal const double InchInMeter = 39.3701;
		internal const double FootInMeter = 3.28084;
		internal const double YardInMeter = 1.09361;

		[DataMember]
		public double Inch { get; set; }

		[DataMember]
		public double Foot { get; set; }

		[DataMember]
		public double Yard { get; set; }

		[DataMember]
		public double Celsius { get; set; }

		[DataMember]
		public double Fahrenheit { get; set; }

		public ConvertedUnits() {

		}
	}
}
