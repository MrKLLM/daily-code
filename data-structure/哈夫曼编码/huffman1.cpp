#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

// 哈夫曼树节点结构体
struct TreeNode {
    char ch;              // 字符
    int freq;             // 频率
    TreeNode* left;       // 左子节点
    TreeNode* right;      // 右子节点
    
    TreeNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// 最小堆比较函数
struct Compare {
    bool operator()(TreeNode* a, TreeNode* b) {
        return a->freq > b->freq;  // 频率小的优先级高
    }
};

// 统计字符频率
map<char, int> countFrequency(const string& text) {
    map<char, int> freqMap;
    for (char c : text) {
        freqMap[c]++;
    }
    return freqMap;
}

// 构建哈夫曼树
TreeNode* buildHuffmanTree(const map<char, int>& freqMap) {
    priority_queue<TreeNode*, vector<TreeNode*>, Compare> minHeap;
    
    // 将所有字符节点加入最小堆
    for (auto& pair : freqMap) {
        minHeap.push(new TreeNode(pair.first, pair.second));
    }
    
    // 构建哈夫曼树
    while (minHeap.size() > 1) {
        // 取出两个频率最小的节点
        TreeNode* left = minHeap.top();
        minHeap.pop();
        TreeNode* right = minHeap.top();
        minHeap.pop();
        
        // 创建新的内部节点，频率为两个子节点频率之和
        TreeNode* parent = new TreeNode('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        
        // 将新节点加入最小堆
        minHeap.push(parent);
    }
    
    return minHeap.top();
}

// 生成哈夫曼编码表
void generateCodes(TreeNode* root, string code, map<char, string>& codes) {
    if (root == nullptr) return;
    
    // 叶子节点，记录编码
    if (root->left == nullptr && root->right == nullptr) {
        codes[root->ch] = code;
        return;
    }
    
    // 递归遍历左右子树
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

// 编码函数：将字符串转换为哈夫曼编码
string encode(const string& text, const map<char, string>& codes) {
    string result = "";
    for (char c : text) {
        result += codes.at(c);
    }
    return result;
}

// 解码函数：将哈夫曼编码转换为字符串
string decode(const string& encoded, TreeNode* root) {
    string result = "";
    TreeNode* current = root;
    
    for (char bit : encoded) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        
        // 到达叶子节点，输出字符
        if (current->left == nullptr && current->right == nullptr) {
            result += current->ch;
            current = root;  // 回到根节点继续解码
        }
    }
    
    return result;
}

// 释放哈夫曼树内存
void freeTree(TreeNode* root) {
    if (root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    // 优化输入输出速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string text, encodedText;
    
    // 读取输入
    if (!(cin >> text)) return 0;
    if (!(cin >> encodedText)) return 0;
    
    // 统计字符频率
    map<char, int> freqMap = countFrequency(text);
    
    // 构建哈夫曼树
    TreeNode* root = buildHuffmanTree(freqMap);
    
    // 生成编码表
    map<char, string> codes;
    generateCodes(root, "", codes);
    
    // 编码原始字符串
    string encoded = encode(text, codes);
    cout << encoded << endl;
    
    // 解码输入的编码串
    string decoded = decode(encodedText, root);
    cout << decoded << endl;
    
    // 释放内存
    freeTree(root);
    
    return 0;
}
