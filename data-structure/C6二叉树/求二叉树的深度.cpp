#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
};
//建树
TreeNode* buildTree(){
    int x;
    cin >> x;
    if (x == 0) {
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


int main() {
	TreeNode* root = buildTree();
    cout << getDeepth(root) << endl;
	
	return 0;
}
