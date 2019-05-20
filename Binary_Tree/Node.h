#pragma once

template <class T> class Tree;

template <class T> class TreeNode
{
	friend class Tree<T>;
public:
	TreeNode(const T &);
	T getData();
protected:
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
	T data;
};

template<class T>
TreeNode<T>::TreeNode(const T &a)
{
	data = a;
	parent = left = right = 0;
}
template <class T>
T TreeNode<T>::getData()
{
	return data;
}