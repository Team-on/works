#pragma once
//#include "Tree.h"

template <typename T>
class TreeNode {
public:
	TreeNode *right, *left;
	T value;

	//friend class Tree;  //ERROR

	TreeNode() : right(nullptr), left(nullptr) { }
	TreeNode(T val) : right(nullptr), left(nullptr), value(val) { }
	TreeNode(T val, TreeNode *r, TreeNode *l) : value(val), right(r), left(l) { }
	~TreeNode() { }

};