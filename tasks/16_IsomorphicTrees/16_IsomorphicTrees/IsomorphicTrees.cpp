#include <iostream>

using namespace std;

struct Node {
	int data;
	Node * left;
	Node * right;
	Node(int dat) : data(dat), left(nullptr), right(nullptr) {};
};
void insertNode(Node * &root, int data) {
	if (root == nullptr) { root = new Node(data); return; }

	if (data < root->data)
		if (root->left != nullptr)
			insertNode(root->left, data);
		else {
			Node * p = new Node(data);
			root->left = p;
		}
	if (data > root->data)
		if (root->right != nullptr)
			insertNode(root->right, data);
		else {
			Node * p = new Node(data);
			root->right = p;
		}

}
void deleteTree(Node * &root)
{
	if (root == nullptr) return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
	root = nullptr;
}



int main() {
	Node * root = nullptr;
	insertNode(root, 10);
	insertNode(root, 6);
	insertNode(root, 8);
	insertNode(root, 4);
	insertNode(root, 5);
	insertNode(root, 14);
	insertNode(root, 20);
	insertNode(root, 16);
	deleteTree(root);
	system("pause");
}