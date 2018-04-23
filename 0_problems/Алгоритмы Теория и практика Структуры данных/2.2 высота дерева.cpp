#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <map>
using namespace std; 

int *tree;
map<int, int> hight;

int Height(int *elem) {
	auto f = hight.find(elem - tree);
	if (f != hight.end()) 
		return f->second;

	int h = 1;
	if (*elem != -1) 
		h += Height(tree + *elem);
	hight.emplace(elem - tree, h);
	return h;
}

int main() {
	int size;
	scanf("%d", &size);
	tree = new int[size];
	int *last = tree + size, *i = tree;
	for(; i < last; ++i)
		scanf("%d", i);

	for (i = tree; i < last; ++i) 
		Height(i);

	int max = 1, tmp;
	for (auto &i: hight) 
		if (max < i.second)
			max = i.second;
	printf("%d", max);


	//printf("\n");
	//system("pause");
	return 0;
}