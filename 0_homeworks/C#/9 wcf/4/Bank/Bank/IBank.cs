using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace DualHttp {
	[ServiceContract(CallbackContract = typeof(IClientCallback))]
	public interface IBank {
		[OperationContract]
		int CreateAccount(int m);

		[OperationContract(IsOneWay =true)]
        void Withdraw(int m, int number);

		[OperationContract]
        int GetAccountInfo(int number);
    }
}
