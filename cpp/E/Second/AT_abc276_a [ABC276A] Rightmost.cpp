#include<bits/stdc++.h>
using namespace std;
#ifndef DEBUG
	#define DEBUG (0)
#endif

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	string s;
    cin >> s;
    for (int i = s.length()-1; i >= 0; i--)
    {
        if (s[i] == 'a')
        {
            cout << i+1;
            return 0;
            /* code */
        }
        
        /* code */
    }
    cout << -1;
	return 0;
}
