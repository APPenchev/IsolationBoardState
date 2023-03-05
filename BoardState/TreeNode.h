#pragma once
#include <vector>

template<typename T>
struct TreeNode {

	T val;
	std::vector<TreeNode*> children;

	TreeNode()
	{
		this->val = 0;
	}
	~TreeNode()
	{
		children.clear();
	}

	TreeNode(T bs)
	{
		this->val = bs;
	}
};