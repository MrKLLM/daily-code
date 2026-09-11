#include<bits/stdc++.h>
using namespace std;
#ifndef DEBUG
	#define DEBUG (0)
#endif
#ifndef MAX
	#define MAX ()
#endif

int main() {
	int n;
	cin >> n;
	
	int supl_pos[20]{0};
	supl_pos[0] = 0;
	int dist1 = 0;
	int dist2 = 0;
	for(int i=1;i<=20;i++){
		supl_pos[i] = i*5;
		if(supl_pos[i] >= n
		   && supl_pos[i-1] <= n){
			dist1 = abs(supl_pos[i-1] - n);
			dist2 = abs(supl_pos[i] - n);
			break;
		}
	}
	
	if(dist2 > dist1){
		cout << n-dist1;
	}else{
		cout << n+dist2;
	}
	
	return 0;
}
