#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif
int main(){
	int n, x;
	cin >> n >> x;
	int sum =0;
	for(int i=0;i<=(n-1);i++){
		int a = 0;
		cin >> a;
		if(a <= x){
			sum += a;
		}
		
	}
	
	cout << sum;
	return 0;
}
