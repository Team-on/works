using System;
using System.Threading;

namespace ThreadLocker {
    public class ThreadLocker {
        bool used = false;

        public void Lock() {
            while (used) Thread.Sleep(10);
            used = true;
        }

        public void Unlock() {
            used = false;
        }

        public bool IsUsed() => used;
    }
}
