#include<bits/stdc++.h>
using namespace std;
#ifndef DEBUG
	#define DEBUG (0)
#endif
#ifndef MAX
	#define MAX (100)
#endif

int main() {
    int n=0, m=0;
    cin >> n >> m;
    int A[MAX];
    int B[MAX];
    for (int i = 0; i < n; i++)
    {
        int tmp = 0;
        cin >> tmp;
        A[i] = tmp;
    }
    for (int i = 0; i < m; i++)
    {
        int tmp = 0;
        cin >> tmp;
        B[i] = tmp;
    }
    int sum = 0;
    for (int i = 0; i < m; i++)
    {
        sum+=A[B[i]-1];
    }
    cout << sum;
	
	return 0;
}
