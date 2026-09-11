#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <climits>

using namespace std;

//哈夫曼树节点结构体
typedef struct{
    int weight;
    int parent;
    int lchild;
    int rchild;
}HTNode,*HuffmanTree;

//select:选最小的两个节点
void Select(HuffmanTree HT,int end,int& s1,int& s2)
{
    int min1 = INT_MAX;//最小值
    int min2 = INT_MAX;//次小值
    
    s1 = s2 = 0;//节点从新开始遍历

    for (int i = 1; i <= end; i++)
    {
        if (HT[i].parent == 0)//只遍历无父节点的节点
        {
            if (HT[i].weight < min1)
            {
                min2 = min1;
                s2 = s1;
                min1 = HT[i].weight;
                s1 = i;
            }
            else if (HT[i].weight < min2)
            {
                min2 = HT[i].weight;
                s2 = i;   
            }   
        }   
    }
}
//创建哈夫曼树
void CreateHuffmanTree(HuffmanTree HT,int w[],int n)
{
    //初始化哈夫曼树
    int s1,s2;
    //前n个节点的父节点为0
    for (int i = 1; i <= n; i++)
    {
        HT[i].weight = w[i-1];
    }
    //构建哈夫曼树
    for (int i = n+1; i <= 2*n-1; i++)
    {
        Select(HT,i-1,s1,s2);
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}
//生成哈夫曼编码
void HuffmanCode(HuffmanTree HT,string code[],int n)
{
    for (int i = 1; i <= n; i++)
    {
        int c = i;//从叶子开始向上遍历
        int f = HT[i].parent;//当前节点的父节点
        string s = "";//重置

        while (f != 0)//没到根
        {
            if (HT[f].lchild == c)//当前节点是左孩子
            {
                s = "0" + s;//从上往下读
            }else//是右孩子
            {
                s = "1" + s;
            }
            c = f;//向上走
            f = HT[f].parent;
        }
        code[i] = s;
    }
}

int main(){
    /*
    一个字符串对应一颗哈夫曼树
    从而，对应一个哈夫曼编码表
    */

    char ch[300];//出现过的字符
    int w[300];//出现的权重（频率）
    string hc[300];//哈夫曼编码表
    int n = 0;//出现的字符种类数

    string text,encode;
    cin >> text >> encode;
    
    int cnt[256] = {0};
    //统计每个字符出现次数
    for (size_t i = 0; i < text.length(); i++)
    {
        char tmp_c = text[i];
        cnt[(unsigned char)tmp_c]++;
    }
    //准备好w[]和n
    for (int i = 0; i < 256; i++)
    {
        if (cnt[i] > 0)//出现过
        {
            ch[n] = (char)i;
            w[n] = cnt[i];//存储权重
            n++;
        }   
    }
    
    HuffmanTree HT;
    int m = 2*n - 1;
    HT = new HTNode[m + 1];//下标从 1 开始，所以要 m+1
    for (int i = 1; i <= m; i++)
    {
        HT[i].weight = 0;
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    CreateHuffmanTree(HT,w,n);//建树
    HuffmanCode(HT,hc,n);//建表
    
    //由表对原字符串编码
    string ans = "";
    for (size_t i = 0; i < text.length(); i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (ch[j] == text[i])//在字符串里找字母
            {
                ans += hc[j+1];//hc从1开始
                break;
            }
        }
    }
    cout << ans << endl;

    //由表译码
    string str2 = ""; 
    int p = m;//从上往下（根开始）
    
    for (size_t i = 0; i < encode.length(); i++)
    {   //向下
        if (encode[i] == '0')
        {
            p = HT[p].lchild;
        }
        else
        {
            p = HT[p].rchild;
        }
        //遇到叶子（左右孩子为0）
        if(HT[p].lchild == 0 && HT[p].rchild == 0)
        {
            str2 += ch[p-1];//ch从0开始
            //记住，哈夫曼树所有叶子的数字就是原字符串字母的下标
            p = m;
        }
    }
    cout << str2 << endl;
    delete[] HT;
    return 0;
}