#include<bits/stdc++.h>
using namespace std;
#ifndef DEBUG
#define DEBUG (0)
#endif

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int h,m;
	cin >> h >> m;
	while(1){
		int new_h = (h/10)*10 + m/10;
		int new_m = (h%10)*10 + m%10;
		
		
		if(new_h < 24 && new_m < 60){
			cout << h << ' ' << m;
			return 0;//TODO
		}
		m++;
		if(m==60){
			m = 0;
			h = (h+1)%24;
		}
	}
	
}
