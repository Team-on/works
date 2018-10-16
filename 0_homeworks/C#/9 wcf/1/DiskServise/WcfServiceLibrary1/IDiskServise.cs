using System.ServiceModel;

namespace DiskServise {
	[ServiceContract]
	public interface IDiskServise {
		[OperationContract]
		string[] GetDiskInfo(string path);
	}
}