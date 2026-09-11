#include <iostream>
using namespace std;

const int MAXN = 1000;

// 二叉树节点
struct Node {
	int data;
	Node* left;
	Node* right;
};

// 创建新节点
Node* newNode(int val) {
	Node* node = new Node;
	node->data = val;
	node->left = NULL;
	node->right = NULL;
	return node;
}

// 插入到二叉搜索树
Node* insert(Node* root, int val) {
	if (root == NULL) {
		return newNode(val);
	}
	if (val < root->data) {
		root->left = insert(root->left, val);
	} else {
		root->right = insert(root->right, val);
	}
	return root;
}

// 中序遍历并输出
void inorder(Node* root) {
	if (root == NULL) return;
	inorder(root->left);
	cout << root->data << " ";
	inorder(root->right);
}

// 释放树
void freeTree(Node* root) {
	if (root == NULL) return;
	freeTree(root->left);
	freeTree(root->right);
	delete root;
}

int main() {
	int n;
	int arr[MAXN];
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	
	Node* root = NULL;
	for (int i = 0; i < n; i++) {
		root = insert(root, arr[i]);
	}
	
	inorder(root);
	cout << endl;
	
	freeTree(root);
	return 0;
}
