#pragma once

#include "TreeNode.h"
#include "Stack.h"

#include "Dictionary.h"

template <typename T>
class Tree {
	TreeNode <T> *root;

	void Add(TreeNode <T> *Root, T value) {
		StackArr <TreeNode <T> *> p;
		do {
			if (root == nullptr) {
				root = new TreeNode <T>(value);
				root->left = nullptr;
				root->right = nullptr;
				return;
			}
			p.push(Root);
			if (Root->value < value) {	
				if (Root->right != nullptr)
					Root = Root->right;
				else {
					Root->right = new TreeNode <T>(value);
					return;
				}
			}
			else {
				if (Root->left != nullptr)
					Root = Root->left;
				else {
					Root->left = new TreeNode <T>(value);
					return;
				}
			}
		} while (!p.isEmpty());
	}
	void ShowLRoR(TreeNode <T> *Root) const {
		/*StackArr <TreeNode <T> *> p;
		do {
			p.push(Root);
			if (Root->left != nullptr)
				Root = Root->left;
			else {
				cout << Root->value << ' ';
				Root = p.pop();
			}
			cout << Root->value << ' ';
			if (Root->right != nullptr)
				Root = Root->right;
			else {
				cout << Root->value << ' ';
				Root = p.pop();
			}
		} while (!p.isEmpty());
		*/
		if (Root == nullptr)
			return;
		ShowLRoR(Root->left);
		cout << Root->value << endl;
		ShowLRoR(Root->right);

	}
	TreeNode <T> * Find(TreeNode <T> *Root, T value) const {
		do {
			if (Root->value == value) {
				//Root->value.callTimes++;
				return Root;
			}
			if (Root->value < value) {
				if (Root->right != nullptr)
					Root = Root->right;
				else 
					return nullptr;
			}
			else {
				if (Root->left != nullptr)
					Root = Root->left;
				else 
					return nullptr;
			}
		} while (1);
	}
public:
	Tree() : root(nullptr) {}
	Tree(T val) : root(new TreeNode <T>(val, nullptr, nullptr)) { }
	~Tree() {}
	void Add(T value) {
		Add(root, value);
	}
	void ShowLRoR() const {
		ShowLRoR(root);
	}
	TreeNode <T> * Find(T value) const {
		return Find(root, value);
	}
};

template<> 
class Tree<DictionaryWord> {
	TreeNode <DictionaryWord> *root;

	void Add(TreeNode <DictionaryWord> *Root, DictionaryWord value) {
		StackArr <TreeNode <DictionaryWord> *> p;
		do {
			if (root == nullptr) {
				root = new TreeNode <DictionaryWord>(value);
				root->left = nullptr;
				root->right = nullptr;
				return;
			}
			p.push(Root);
			if (Root->value < value) {
				if (Root->right != nullptr)
					Root = Root->right;
				else {
					Root->right = new TreeNode <DictionaryWord>(value);
					return;
				}
			}
			else {
				if (Root->left != nullptr)
					Root = Root->left;
				else {
					Root->left = new TreeNode <DictionaryWord>(value);
					return;
				}
			}
		} while (!p.isEmpty());
	}
	void ShowLRoR(TreeNode <DictionaryWord> *Root) const {
		if (Root == nullptr)
			return;
		ShowLRoR(Root->left);
		cout << Root->value << endl;
		ShowLRoR(Root->right);
	}
	TreeNode <DictionaryWord> * Find(TreeNode <DictionaryWord> *Root, DictionaryWord value) const {
		do {
			if (Root->value == value) {
				Root->value.SetCallTimes(Root->value.GetCallTimes() + 1);
				return Root;
			}
			if (Root->value < value) {
				if (Root->right != nullptr)
					Root = Root->right;
				else
					return nullptr;
			}
			else {
				if (Root->left != nullptr)
					Root = Root->left;
				else
					return nullptr;
			}
		} while (1);
	}

	void SaveDic(ofstream &fout,TreeNode <DictionaryWord> *Root) const {
		if (Root == nullptr)
			return;

		fout << Root->value << endl;
		SaveDic(fout, Root->left);
		SaveDic(fout, Root->right);
	}

	template <typename T>
	static void ArrSort(T *arr, int size) {
		for (int i = 0; i < size; ++i) {
			int min = i;
			for (int j = i; j < size; ++j)
				if (arr[min] > arr[j])
					min = j;
			if (min != i)
				swap(arr[min], arr[i]);
		}
	}
	void top3_help(TreeNode <DictionaryWord> *Root, DictionaryWord * rez) {
		if (Root == nullptr)
			return;

		top3_help(Root->right, rez);
		if (Root->value.GetCallTimes() > rez[0].GetCallTimes()) {
			if (Root->value.GetCallTimes() > rez[2].GetCallTimes()) {
				rez[0] = rez[1];
				rez[1] = rez[2];
				rez[2] = Root->value;
			}
			else if (Root->value.GetCallTimes() > rez[1].GetCallTimes()) {
				rez[0] = rez[1];
				rez[1] = Root->value;
			}
			else if (Root->value.GetCallTimes() > rez[0].GetCallTimes()) {
				rez[0] = Root->value;
			}
		}
		top3_help(Root->left, rez);
	}
	void untop3_help(TreeNode <DictionaryWord> *Root, DictionaryWord * rez) {
		if (Root == nullptr)
			return;

		untop3_help(Root->right, rez);
		if (Root->value.GetCallTimes() < rez[0].GetCallTimes()) {
			if (Root->value.GetCallTimes() < rez[2].GetCallTimes()) {
				rez[0] = rez[1];
				rez[1] = rez[2];
				rez[2] = Root->value;
			}
			else if (Root->value.GetCallTimes() < rez[1].GetCallTimes()) {
				rez[0] = rez[1];
				rez[1] = Root->value;
			}
			else if (Root->value.GetCallTimes() < rez[0].GetCallTimes()) {
				rez[0] = Root->value;
			}
		}
		untop3_help(Root->left, rez);
	}
public:
	Tree() : root(nullptr) {}
	Tree(DictionaryWord val) : root(new TreeNode <DictionaryWord>(val, nullptr, nullptr)) { }
	~Tree() {}
	void Add(DictionaryWord value) {
		Add(root, value);
	}
	void ShowLRoR() const {
		ShowLRoR(root);
	}
	TreeNode <DictionaryWord> * Find(DictionaryWord value) const {
		return Find(root, value);
	}

	void SaveDic(ofstream &fout) const {
		SaveDic(fout,root);
	}

	DictionaryWord *Top3() {
		DictionaryWord * rez = new DictionaryWord[3];
		rez[0] = root->value;
		rez[1] = root->left->value;
		rez[2] = root->right->value;
		ArrSort(rez, 3);

		//якщо вкинути просто root, то можуть бути повторенн€, €кщо максимум це root->left чи root->right
		top3_help(root->left->right, rez);
		top3_help(root->left->left, rez);
		top3_help(root->right->right, rez);
		top3_help(root->right->left, rez);
		return rez;
	}
	DictionaryWord *UnTop3() {
		DictionaryWord * rez = new DictionaryWord[3];
		rez[0] = root->value;
		rez[1] = root->left->value;
		rez[2] = root->right->value;
		ArrSort(rez, 3);

		//якщо вкинути просто root, то можуть бути повторенн€, €кщо максимум це root->left чи root->right
		untop3_help(root->left->right, rez);
		untop3_help(root->left->left, rez);
		untop3_help(root->right->right, rez);
		untop3_help(root->right->left, rez);
		return rez;
	}
};