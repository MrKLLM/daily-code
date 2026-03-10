#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif
int main(){
	
	int n = 0;
	cin >> n;
	vector<int> p;
	for(int i=0;i<n;i++){
		int a = 0;
		cin >> a;
		p.push_back(a);
	}
	
	int max = 0;
	for(int i=1;i<n;i++){
		
		if(max < p[i]){
			max = p[i];
		}
	}
	
	int x = 0;
	if(max < p[0]){
		x = 0;
	}else{
		x = max - p[0] + 1;
	}
	
	cout << x;
	return 0;
}
