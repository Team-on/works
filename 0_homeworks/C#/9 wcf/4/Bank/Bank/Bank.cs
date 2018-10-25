using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace DualHttp {
	[ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
	public class Bank : IBank {
		int lastNum = 0;
		Dictionary<int, int> list = new Dictionary<int, int>();

		public int CreateAccount(int m) {
			list.Add(++lastNum, m);
			return lastNum;
		}

		public int GetAccountInfo(int number) {
			return list.ContainsKey(number) ? list[number] : 0;
		}

		public void Withdraw(int m, int number) {
			if (list.ContainsKey(number) && list[number] >= m) {
				list[number] -= m;
				OperationContext.Current.GetCallbackChannel<IClientCallback>().Balance(list[number]);
			}
		}
	}
}
