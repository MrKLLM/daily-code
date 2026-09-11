#include<bits/stdc++.h>
using namespace std;

int main(){
	long double X;
	cin >> X;
	long long Y=0;
	if(X>=0){
		Y=(X+9)/10;
	}else{
		Y=X/10;
	}
	cout << Y;
	return 0;
} 
