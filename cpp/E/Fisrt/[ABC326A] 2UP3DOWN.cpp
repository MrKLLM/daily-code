#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif
int main(){
	int x = 0;
	int y = 0;
	cin >> x >> y;
	if((x-y) < 0
	   &&(abs(x-y) <= 2)){
		cout << "Yes";
	}else if((x-y) > 0
		&&(abs(x-y) <= 3)){
		cout << "Yes";
	}else{
		cout << "No";
	}
	
	return 0;
}
