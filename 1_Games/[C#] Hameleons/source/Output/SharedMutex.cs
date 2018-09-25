using System.Threading;

namespace Hameleons {
	static class SharedMutex {
		static public Mutex consoleMutex = new Mutex(false);
	}
}
