#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif
int main(){
	
	int n ,m ,p;
	cin >> n >> m >> p;
	
	int surplus_days = n-m;
	int freq = 0;
	if(surplus_days < 0){
		cout << 0;
	}else{
		freq++;
		for(int i=surplus_days;i>=p;i-=p){
			
			freq++;
		}
		cout << freq;
	}
	return 0;
	
}
