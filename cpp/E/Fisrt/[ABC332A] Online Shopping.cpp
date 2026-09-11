#include<bits/stdc++.h>

using namespace std;
#ifndef MAX
#define MAX ()
#endif
int main(){
	int n,s,k;
	cin >> n >> s >> k;
	
	int gross_amount = 0;
	for(int i=0;i<=n-1;i++){
		int unit_price = 0;
		int q = 0;
		cin >> unit_price >> q;
		gross_amount += unit_price * q;
	}
	
	int final_amount = 0;
	if(s <=gross_amount){
		cout << gross_amount;
	}else{
		final_amount = gross_amount + k;
		cout << final_amount;
	}
	return 0;
}
