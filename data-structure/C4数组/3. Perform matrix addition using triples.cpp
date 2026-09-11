#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif

struct triples{
    int row;
    int col;
    int val;
};

int main() {
	int m,n;
	cin>>m>>n;
	triples A[100];
    triples B[100];
	triples result[100];
    //三指针
    int i = 0;//A指针
    int j = 0;//B指针
    int k = 0;//C指针

    for (int i = 0; i < m; i++)
    {
        cin >> A[i].row >> A[i].col >> A[i].val ;
    }

    for (int i = 0; i < n; i++)
    {
        cin >> B[i].row >> B[i].col >> B[i].val ;
    }
    //重置指针，指向开头
    i = 0;
    j = 0;

    while (i<m && j<n)
    {
        //比较行号，小在前
        if (A[i].row < B[j].row)
        {
            result[k++]=A[i++];
            
        }
        else if (B[j].row < A[i].row)
        {
            result[k++]=B[j++];
            
        }
        else//行号相同，比较列号
        {   
            if (A[i].col < B[j].col)
            {
                result[k++]=A[i++];
                
            }
            else if (B[j].col < A[i].col)
            {
                result[k++]=B[j++];
                
            }
            else
            {
                int sum = A[i].val + B[j].val;//可能为0
                if (sum != 0)
                {
                    result[k].row = A[i].row;
                    result[k].col = A[i].col;
                    result[k].val = sum;
                    k++;
                }
                i++;
                j++;
            }
            
            
        }
        
        
    }
    while (i<m)
    {
        result[k++]=A[i++];
    }
    while (j<n)
    {
        result[k++]=B[j++];
    }
    if (k == 0)
    {
        printf("-1 -1 -1\n");
    }
    else
    {
        for (int i = 0; i < k; i++)
        {
            cin >> result[i].row >> result[i].col >> result[i].val;
        }
    }
    
	return 0;
}
