using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ServiceModel;

namespace CSharpClient {
	class Program {
		[ServiceContract]
		interface IServiseTest {
			[OperationContract]
			int GetNumber();
		};


		static void Main(string[] args) {
			ChannelFactory<IServiseTest> factory = new ChannelFactory<IServiseTest>(new BasicHttpBinding(),
					new EndpointAddress("http://localhost:8733/Design_Time_Addresses/WCF_ServiseTest/ServiseTest/"));

			IServiseTest channel = factory.CreateChannel();

			int result = channel.GetNumber();
			Console.WriteLine("result: {0}", result);

			Console.ReadLine();
			factory.Close();
		}
	}
}
