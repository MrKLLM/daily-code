#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif

struct TreeNode{
    char val;
    TreeNode* left;
    TreeNode* right;
};

int idx = 0;
string str;

//建树
TreeNode* buildTree(){
    if (idx >= str.size()) {
        return NULL;  // 防止越界
    }
    char x = str[idx];
    idx++;
    if (x == '0') {
        return NULL;   // 空节点
    }
    TreeNode* node = new TreeNode();
    node->val = x;
    node->left = buildTree();
    node->right = buildTree();
    return node;
}
//获取深度
int getDeepth(TreeNode* root){
    if (root == NULL)
    {
        return 0;
    }
    return 1 + max(getDeepth(root->left),getDeepth(root->right));
}

//先序遍历
void PrePrint(TreeNode* root){
    if (root == NULL)
    {
        return;
    }
    cout << root->val;
    PrePrint(root->left);
    PrePrint(root->right);
}

//中序遍历
void InPrint(TreeNode* root){
    if (root == NULL)
    {
        return;
    }
    InPrint(root->left);
    cout << root->val;
    InPrint(root->right);
}

//后序遍历
void PostPrint(TreeNode* root){
    if (root == NULL)
    {
        return;
    }
    PostPrint(root->left);
    PostPrint(root->right);
    cout << root->val;
}

//计算结点个数
int countNodes(TreeNode* root){
    if (root == NULL){
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

//计算叶子结点个数
int countLeaves(TreeNode* root){
    if (root == NULL){
        return 0;
    }
    if (root->left == NULL && root->right == NULL){
        return 1;
    }
    return countLeaves(root->left) + countLeaves(root->right);
}
int main() {
	cin >> str;
	TreeNode* root = buildTree();
    PrePrint(root);
    cout << endl;
    InPrint(root);
    cout << endl;
    PostPrint(root);
    cout << endl;
    
    cout << countNodes(root) << " ";
    cout << countLeaves(root) << " ";
    cout << getDeepth(root) << " ";
	
	return 0;
}
