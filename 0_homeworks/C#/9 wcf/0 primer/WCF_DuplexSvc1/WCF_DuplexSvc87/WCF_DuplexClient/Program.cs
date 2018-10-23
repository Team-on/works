using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using WCF_DuplexClient.ServiceReference1;

namespace WCF_DuplexClient
{
    public class CallbackHandler : IDuplexSvcCallback
    {
        
        public void ReceiveTime(string str)
        {
            Console.WriteLine("Получено сообщение:\n" +str);
        }
    }
    class Program
    {
        static void Main(string[] args)
        {

            InstanceContext site = new InstanceContext(new CallbackHandler());
       
             DuplexSvcClient proxy = new DuplexSvcClient(site);
             proxy.ReturnTime(2, 5);

            Console.ReadKey();
        }
    }
}
