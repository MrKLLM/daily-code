#include<bits/stdc++.h>
using namespace std;
#ifndef DEBUG
	#define DEBUG (0)
#endif

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	int n,x;
	cin>>n>>x;
    for (size_t i = 1; i <= n; i++)
    {
        int tmp;
        cin >> tmp;
        if (tmp == x)
        {
            cout << i;
            return 0;
            /* code */
        }
        
        /* code */
    }


    
	return 0;
}
