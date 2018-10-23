using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using WCFBankClient.ServiceReference1;
namespace WCFBankClient
{
    class Program
    {
        static void Main(string[] args)
        {
            BankServiceClient proxy = new BankServiceClient();
            Console.WriteLine("Введіть суму:");
            double sum = Convert.ToDouble(Console.ReadLine());
            double result = 0;
            while (sum > 0)
            {
                proxy.ToDeposit(sum); result = proxy. GetBalance();

                Console.WriteLine("Депозит = {0}",result);
                Console.WriteLine("Введіть суму:");
                sum = Convert.ToDouble(Console.ReadLine());
            }
            
            Console.ReadLine();

        }
    }
}
