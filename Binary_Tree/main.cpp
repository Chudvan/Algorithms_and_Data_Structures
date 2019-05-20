#include <iostream>
#include <string>
#include "Tree.h"
using namespace std;

bool isMore5(TreeNode<double>* node) {
	return node->getData() > 5;
}

int main()
{
	/*
	Tree<int> tree1;
	int n;
	int cur;
	cout << "How many Nodes?" << endl;
	cin >> n;
	cout << "Write " << n << " int numbers." << endl;

	for (int i = 0; i < n; i++) {
		cin >> cur;
		tree1.insertNode(cur);
	}

	queue<int> bufQueue;
	cout << endl << "inorderWalk:" << endl;
	tree1.inorderWalk(tree1.getRoot(), bufQueue);
	while (!bufQueue.empty()) {
		cout << bufQueue.front() << endl;
		bufQueue.pop();
	}

	cout << endl << "Minimum is: " << tree1.findMin(tree1.getRoot())->getData() << endl;
	cout << "Maximum is: " << tree1.findMax(tree1.getRoot())->getData() << endl;

	cout << endl << "Enter node value U want to delete: ";
	cin >> cur;
	tree1.deleteNode(cur);
	cout << endl << "Now inorderWalk:" << endl;
	tree1.inorderWalk(tree1.getRoot(), bufQueue);
	while (!bufQueue.empty()) {
		cout << bufQueue.front() << endl;
		bufQueue.pop();
	}
	*/
	
	Tree<double> tree2;
	int n;
	double cur;
	cout << "How many Nodes?" << endl;
	cin >> n;
	cout << "Write " << n << " double numbers." << endl;

	for (int i = 0; i < n; i++) {
		cin >> cur;
		tree2.insertNode(cur);
	}

	cout << endl << "Test widthWalk:" << endl;
	queue<double> bufQueue;
	tree2.widthWalk(tree2.getRoot(), bufQueue);
	while(!bufQueue.empty()){
		cout << bufQueue.front() << endl;
		bufQueue.pop();
	}

	cout << endl << "inorderWalk:" << endl;
	tree2.inorderWalk(tree2.getRoot(), bufQueue);
	while (!bufQueue.empty()) {
		cout << bufQueue.front() << endl;
		bufQueue.pop();
	}


	cout << endl << "Write which node find: " << endl;
	cin >> cur;
	TreeNode<double> *bufNode = tree2.findNode(tree2.getRoot(), cur);
	if (bufNode)
		cout << "Node with " << bufNode->getData() << " is here: " << bufNode << endl;
	else
		cout << "Node with " << cur << " is not exist." << endl;
	
	cout << endl << "Get subtree: " << endl;
	cout << "Write which node is root: " << endl;
	cin >> cur;
	Tree<double> *newTree2 = tree2.getSubTree(cur);
	cout << endl << "inorderWalk in SubTree:" << endl;
	newTree2->inorderWalk(newTree2->getRoot(), bufQueue);
	while (!bufQueue.empty()) {
		cout << bufQueue.front() << endl;
		bufQueue.pop();
	}

	Tree<double> tree4;
	int n2;
	cout << endl << "How many Nodes?" << endl;
	cin >> n2;
	cout << "Write " << n2 << " double numbers." << endl;

	for (int i = 0; i < n2; i++) {
		cin >> cur;
		tree4.insertNode(cur);
	}

	cout << endl << "Test mergeTrees:" << endl;
	Tree<double> *tree5 = tree2.mergeTrees(tree4);
	cout << endl << "Test widthWalk in mergeTree:" << endl;
	tree5->widthWalk(tree5->getRoot(), bufQueue);
	while (!bufQueue.empty()) {
		cout << bufQueue.front() << endl;
		bufQueue.pop();
	}

	Tree<double> tree6;
	int n3;
	cout << endl << "Test createFromQueue:" << endl;
	cout << "How many Nodes?" << endl;
	cin >> n3;
	cout << "Write " << n3 << " double numbers." << endl;

	for (int i = 0; i < n3; i++) {
		cin >> cur;
		bufQueue.push(cur);
	}
	tree6.createFromQueue(bufQueue);
	cout << endl << "Test widthWalk in createFromQueueTree:" << endl;
	tree6.widthWalk(tree6.getRoot(), bufQueue);
	while (!bufQueue.empty()) {
		cout << bufQueue.front() << endl;
		bufQueue.pop();
	}

	Tree<double>* tree7 = tree6.where(isMore5);
	cout << endl << "Test widthWalk in whereTree:" << endl;
	tree7->widthWalk(tree7->getRoot(), bufQueue);
	while (!bufQueue.empty()) {
		cout << bufQueue.front() << endl;
		bufQueue.pop();
	}
	
	/*
	Tree<string> tree3;
	int n;
	string cur;
	cout << "How many Nodes?" << endl;
	cin >> n;
	cout << "Write " << n << " strings." << endl;

	for (int i = 0; i < n; i++) {
		cin >> cur;
		tree3.insertNode(cur);
	}

	queue<string> bufQueue;
	cout << endl << "inorderWalk:" << endl;
	tree3.inorderWalk(tree3.getRoot(), bufQueue);
	while (!bufQueue.empty()) {
		cout << bufQueue.front() << endl;
		bufQueue.pop();
	}

	cout << endl << "Minimum is: " << tree3.findMin(tree3.getRoot())->getData() << endl;
	cout << "Maximum is: " << tree3.findMax(tree3.getRoot())->getData() << endl;

	cout << endl << "Enter node value U want to delete: ";
	cin >> cur;
	tree3.deleteNode(cur);
	cout << endl << "Now inorderWalk:" << endl;
	tree3.inorderWalk(tree3.getRoot(), bufQueue);
	while (!bufQueue.empty()) {
		cout << bufQueue.front() << endl;
		bufQueue.pop();
	}
	*/
	system("pause>nul");
	return 0;
}