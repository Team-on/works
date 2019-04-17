# ThreadLocker
 My spinlock realisation
 
## API
 * class ThreadLocker - object of this class responsible for synchronization
	* void Lock()
	* void Unlock()
	* bool IsUsed()
	
## Plan
 * Переписати ThreadLocker щоб всередині використовував чергу(з пріорітетами)
 * Реалізувати ThreadLocker статичним класом
 * Реалізувати Interlocked_____, як в С++.
 * Реалізувати семафор
 
## Made with
 * С#
