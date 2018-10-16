using System;
using System.Collections.Generic;
using System.Linq;

using System.ServiceModel;

namespace MyClient1
{
    class Program
    {
        [ServiceContract]
        public interface IMyMath
        {
            [OperationContract]
            int Add(int a, int b);
        }


        static void Main(string[] args)
        {
            ChannelFactory<IMyMath> factory = new ChannelFactory<IMyMath>(new BasicHttpBinding(),
                                              new EndpointAddress("http://localhost/MyMath"));
            IMyMath channel = factory.CreateChannel();

            int result = channel.Add(5, 3);
            Console.WriteLine("result: {0}",result);
            
            Console.ReadLine();
            factory.Close();
        }
    }
}
