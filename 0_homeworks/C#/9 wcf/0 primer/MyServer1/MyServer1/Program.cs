using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;

namespace MyServer1
{
    class Program
    {
        static void Main(string[] args)
        {
            ServiceHost sh = new ServiceHost(typeof(MyMath));
          //  sh.CloseTimeout = TimeSpan.FromSeconds(20);
           // sh.AddServiceEndpoint(typeof(IMyMath), new WSHttpBinding(), "http://localhost/MyMath/Ep1");

            sh.Open();

            Console.WriteLine("WCF Service Started");
            Console.ReadLine();
            sh.Close();

        }
    }
}
