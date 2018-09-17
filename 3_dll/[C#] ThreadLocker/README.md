# ThreadLocker
Моя реалізація spinlock
 
## API
 * class ThreadLocker - обєкт цього класу відповідатиме за синхронізацію
	* void Lock()
	* void Unlock()
	* bool IsUsed()
	
## План
 * Переписати ThreadLocker щоб всередині використовував чергу(з пріорітетами)
 * Реалізувати ThreadLocker статичним класом
 * Реалізувати Interlocked_____, як в С++.
 * Реалізувати семафор
 
## Зроблено на
 * С#