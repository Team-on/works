using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace DualHttp {
	[ServiceContract(CallbackContract = typeof(IClientCallback))]
	public interface IService1 {
		[OperationContract(IsOneWay =true)]
		void Login(string name);

		[OperationContract(IsOneWay =true)]
		void SendText(string text);

		[OperationContract(IsOneWay =true)]
		void Logout(string name);
	}
}
