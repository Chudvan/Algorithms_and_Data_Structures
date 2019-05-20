#pragma once

#include <iostream>
#include <queue>
#include "Node.h"
using namespace std;

template <class T>
class Tree
{
public:
	Tree();                                                 
	void insertNode(const T &);
	void insertNode(TreeNode<T>*);
	void deleteNode(const T &);
	void inorderWalk(TreeNode<T>*, queue<T> &);             
	TreeNode<T>* findMax(TreeNode<T>*);
	TreeNode<T>* findMin(TreeNode<T>*);
	TreeNode<T>* findNode(TreeNode<T>*, const T &);
	TreeNode<T>* findSuccessor(const T &);
	TreeNode<T> *getRoot();
	Tree<T>* getSubTree(const T &);
	Tree<T>* mergeTrees(Tree<T> &);
	void widthWalk(TreeNode<T>*, queue<T> &);
	void createFromQueue(queue<T> &);
	void RootLRWalk(TreeNode<T>*, queue<T> &);
	void RLRootWalk(TreeNode<T>*, queue<T> &);
	Tree<T>* where(bool (*f)(TreeNode<T>*));
	template <class T2>
	Tree<T2>* map(T2(*f)(TreeNode<T>*));
 private:
	TreeNode<T> *root;
};

template<class T>
Tree<T>::Tree()
{
	root = 0;          
}
template<class T>
void Tree<T>::insertNode(const T &x)
{
	TreeNode<T>* n = new TreeNode<T>(x);
	insertNode(n);
}

template<class T>
void Tree<T>::insertNode(TreeNode<T>* x) {
	TreeNode<T>* ptr;
	TreeNode<T>* ptr1 = 0;

	ptr = root;
	while (ptr != 0)                 
	{
		ptr1 = ptr;                
		if (x->getData() < ptr->getData())
			ptr = ptr->left;
		else
			ptr = ptr->right;  
	}
	x->parent = ptr1;
	if (ptr1 == 0)                    
		root = x;
	else
	{
		if (x->getData() < ptr1->getData())
			ptr1->left = x;
		else
			ptr1->right = x;
	}
}

template<class T>
void Tree<T>::deleteNode(const T& val)
{
	TreeNode<T> *z = findNode(root, val);
	if (!z) {
		cout << "Node is not exist." << endl;
		return;
	}
	TreeNode<T>* y;
	TreeNode<T>* x;
	if (z->left == 0 || z->right == 0)       
		y = z;
	else
		y = findSuccessor(z->getData());
	if (y->left != 0)                               
		x = y->left;
	else
		x = y->right;
	if (x != 0)                                       
		x->parent = y->parent;
	if (y->parent == 0)
		root = x;
	else
	{
		if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
	}
	if (y != z)                                    
		z->data = y->getData();
}
template<class T>
TreeNode<T>* Tree<T>::findMax(TreeNode<T>* x)
{
	while (x->right != 0)                             
		x = x->right;
	return x;
}

template<class T>
TreeNode<T>* Tree<T>::findMin(TreeNode<T>* x)
{
	while (x->left != 0)
		x = x->left;
	return x;
}

template<class T>
TreeNode<T>* Tree<T>::findSuccessor(const T &val)
{
	TreeNode<T>* x = findNode(root, val);                 
	TreeNode<T>* y = 0;
	if (x == 0)
		return 0;
	if (x->right != 0)                                              
	y = x->parent;
	while (y != 0 && x == y->right)                               
	{
		x = y;
		y = y->parent;
	}
	return y;
}
template<class T>
TreeNode<T>* Tree<T>::findNode(TreeNode<T>* n, const T &val)
{
	if (n == 0 || val == n->getData())
		return n;
	if (val > n->getData())
		return findNode(n->right, val);
	else
		return findNode(n->left, val);
}
template<class T>
void Tree<T>::inorderWalk(TreeNode<T>* n, queue<T> &bufQueueT)
{
	if (n != 0)
	{
		inorderWalk(n->left, bufQueueT);
		//cout << n->getData() << endl;
		bufQueueT.push(n->getData());
		inorderWalk(n->right, bufQueueT);
	}
}

template<class T>
TreeNode<T>* Tree<T>::getRoot()
{
	return root;
}

template<class T>
Tree<T>* Tree<T>::getSubTree(const T &val) {
	TreeNode<T> *bufTreeNode = findNode(getRoot(), val);
	if (!bufTreeNode) {
		cout << "Node with " << val << " is not exist." << endl;
		return 0;
	}
	Tree<T> *bufTree = new Tree<T>;
	bufTree->root = bufTreeNode;
	return bufTree;
}

template<class T>
Tree<T>* Tree<T>::mergeTrees(Tree<T> &tree) {
	Tree<T>* bufTree = new Tree<T>;
	queue<T> bufQueue1;
	queue<T> bufQueue2;
	widthWalk(getRoot(), bufQueue1);
	widthWalk(tree.getRoot(), bufQueue2);
	while (!bufQueue1.empty() && !bufQueue2.empty()) {
		if (bufQueue1.front() > bufQueue2.front()) {
			bufTree->insertNode(bufQueue1.front());
			bufQueue1.pop();
		}
		else {
			bufTree->insertNode(bufQueue2.front());
			bufQueue2.pop();
		}
	}
	while (!bufQueue1.empty()) {
		bufTree->insertNode(bufQueue1.front());
		bufQueue1.pop();
	}
	while (!bufQueue2.empty()) {
		bufTree->insertNode(bufQueue2.front());
		bufQueue2.pop();
	}
	return bufTree;
}

template<class T>
void Tree<T>::widthWalk(TreeNode<T>* n, queue<T> &bufQueueT)
{
	queue<TreeNode<T>*> bufQueueNode;
	TreeNode<T>* bufNode;
	bufQueueNode.push(n);
	while (!bufQueueNode.empty()) {
		bufNode = bufQueueNode.front();
		bufQueueT.push(bufNode->getData());
		if(bufNode->left)
			bufQueueNode.push(bufNode->left);
		if (bufNode->right)
			bufQueueNode.push(bufNode->right);
		bufQueueNode.pop();
	}
}

template <class T>
void Tree<T>::createFromQueue(queue<T> &bufQueue) {
	while (!bufQueue.empty()) {
		insertNode(bufQueue.front());
		bufQueue.pop();
	}
}

template<class T>
void Tree<T>::RootLRWalk(TreeNode<T>* n, queue<T> &bufQueueT)
{
	if (n != 0)
	{
		bufQueueT.push(n->getData());
		RLRWalk(n->left, bufQueueT);
		RLRWalk(n->right, bufQueueT);
	}
}

template<class T>
void Tree<T>::RLRootWalk(TreeNode<T>* n, queue<T> &bufQueueT)
{
	if (n != 0)
	{
		RLRWalk(n->right, bufQueueT);
		RLRWalk(n->left, bufQueueT);
		bufQueueT.push(n->getData());
	}
}

template <class T>
Tree<T>* Tree<T>::where(bool (*f)(TreeNode<T>* )) {
	Tree<T>* bufTree = new Tree<T>;
	queue<TreeNode<T>*> bufQueueNode;
	TreeNode<T>* bufNode;
	bufQueueNode.push(root);
	while (!bufQueueNode.empty()) {
		bufNode = bufQueueNode.front();
		if (f(bufNode))
			bufTree->insertNode(bufNode->getData());
		if (bufNode->left)
			bufQueueNode.push(bufNode->left);
		if (bufNode->right)
			bufQueueNode.push(bufNode->right);
		bufQueueNode.pop();
	}
	return bufTree;
}

template <class T>
template <class T2>
Tree<T2>* Tree<T>::map(T2 (*f)(TreeNode<T>*)) {
	Tree<T2>* bufTree = new Tree<T>;
	queue<TreeNode<T>*> bufQueueNode;
	TreeNode<T>* bufNode;
	bufQueueNode.push(root);
	while (!bufQueueNode.empty()) {
		bufNode = bufQueueNode.front();
		bufTree->insertNode(f(bufNode));
		if (bufNode->left)
			bufQueueNode.push(bufNode->left);
		if (bufNode->right)
			bufQueueNode.push(bufNode->right);
		bufQueueNode.pop();
	}
	return bufTree;
}