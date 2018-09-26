using System.Threading;

namespace Hameleons {
	static class SharedMutex {
		static public Mutex console = new Mutex();
	}
}
