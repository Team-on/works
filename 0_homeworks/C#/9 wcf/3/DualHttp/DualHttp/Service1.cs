using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace DualHttp {
	[ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
	public class Service1 : IService1 {
		Dictionary<string, IClientCallback> list = new Dictionary<string, IClientCallback>();

		public void Login(string name) {
			list.Add(name, OperationContext.Current.GetCallbackChannel<IClientCallback>());
		}

		public void Logout(string name) {
			list.Remove(name);
		}

		public void SendText(string text) {
			if (!list.ContainsValue(OperationContext.Current.GetCallbackChannel<IClientCallback>()))
				return;
			foreach (var i in list) 
				i.Value.TextForUsers(text);
		}
	}
}
