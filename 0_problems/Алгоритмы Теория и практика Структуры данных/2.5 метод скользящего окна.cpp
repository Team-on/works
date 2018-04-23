#define _CRT_DISABLE_PERFCRIT_LOCKS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <list>
using namespace std; 

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(NULL);
	
	unsigned int arrSize, frameSize, i = 0;

	//arrSize = _getchar_nolock();
	scanf("%d", &arrSize);
	unsigned int *arr = new unsigned int[arrSize];
	for (; i < arrSize; ++i) {
		//arr[i] = _getchar_nolock();
		scanf("%d", arr + i);
	}
	//frameSize = _getchar_nolock();
	scanf("%d", &frameSize);

	if (frameSize == 1) {
		for (i = 0; i < arrSize; ++i) {
			printf("%d",*arr);
			putchar(' ');
			//_putchar_nolock(' ');
			++arr;
		}
		return 0;
	}
	if (frameSize == arrSize) {
		int max = *arr++;
		for (i = 1; i < arrSize; ++i, ++arr)
			if (max < *arr)
				max = *arr;
		printf("%d", max);
		return 0;
	}


	list<unsigned int> frame;
	i = frameSize;
	while (i--) {
		frame.push_back(*arr);
		++arr;
	}
	i = frame.back();
	list<unsigned int>::reverse_iterator iter = frame.rbegin()++;
	for (; iter != frame.rend(); ++iter)
		if (*iter < i)
			*iter = i;
		else if (*iter != i) {
			i = *iter;
			continue;
		}
	printf("%d", frame.front());

	i = arrSize - frameSize;
	while (i--) {
		frame.pop_front();
		for (iter = frame.rbegin(); iter != frame.rend(); ++iter)
			if (*iter < *arr)
				*iter = *arr;
			else if (*iter != *arr)
				break;
		frame.push_back(*arr);
		++arr;
		putchar(' ');
		printf("%d", frame.front());
		//_putchar_nolock(' ');
	}
	
	//cout << endl;
	//system("pause");
	return 0;
}