#include<bits/stdc++.h>
using namespace std;
#ifndef DEBUG
	#define DEBUG (0)
#endif

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
	vector<string> strs(n+5);
    for (int i = 1; i <= n; i++)
    {
        cin >> strs[i];
        /* code */
    }
    for (int i = 1; i <=n ; i++)
    {
        int k = n - i +1;
        cout << strs[k] << endl;
        /* code */
    }
    
    
	return 0;
}
  