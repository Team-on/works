using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace WCF_DuplexSvc
{

    [ServiceContract(CallbackContract = typeof(IClientCallback))]
    public interface IDuplexSvc
    {
        [OperationContract(IsOneWay = true)]
        void ReturnTime(int period, int number);
    }
   

    public interface IClientCallback
    {
        [OperationContract(IsOneWay = true)]
        void ReceiveTime(string str);
    }
}
