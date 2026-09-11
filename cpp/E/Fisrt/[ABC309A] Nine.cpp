#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int a ,b;
	cin  >> a >> b;
	
	bool is_same_row = false;
	if(1 <= a && a <=3 
	   && 1 <= b && b <=3){
		is_same_row = true;
	}else if(4 <= a && a <=6 
			&& 4 <= b && b <=6){
		is_same_row = true;
	}else if(7 <= a && a <=9 
			&& 7 <= b && b <=9){
		is_same_row = true;
	}
	
	if(is_same_row){
		
		if(1 == abs(a - b)){
			cout << "Yes";
		}else{
			cout << "No";
		}
	}else{
		cout << "No";	
	}
	
	return 0;
}
