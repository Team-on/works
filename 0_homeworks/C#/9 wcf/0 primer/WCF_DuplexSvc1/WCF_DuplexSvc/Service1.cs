using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Threading;

namespace WCF_DuplexSvc
{
    public class DuplexSvc : IDuplexSvc
    {
       
        public void ReturnTime(int period, int number)
        {
            DataValues src = new DataValues();

            src.callback = OperationContext.Current.GetCallbackChannel<IClientCallback>();


            Thread t = new Thread( new  ParameterizedThreadStart(  src.SendTimeToCLient));
            t.IsBackground = true;
            List<int> parameters = new List<int>();
            parameters.Add(period);
            parameters.Add(number);
            t.Start(parameters);
        }
    }
   


    public class DataValues
    {
       
        public IClientCallback callback = null;
        public void SendTimeToCLient(object data)
        {
            
           
            
            List<int> parameters = (List<int>)data;
            int period = parameters[0];
            int number = parameters[1];
            
            for (int i = 0; i < number; i++)
            {
                try
                {
                    
                    Thread.Sleep(period * 1000);
                   

                    callback.ReceiveTime(DateTime.Now.ToLongTimeString().ToString());
                }
                catch (Exception ex)
                {
                }
            }
        }
    }
}
