#include<bits/stdc++.h>
using namespace std;

int main(){
	float n=0;
	float sum=0;
	float mol=2;
	float den=1;
	
	cin >> n;
	for(float i=1; i<=n; i++){
		float tmp =(mol /den);
		sum +=tmp;
		float new_mol =mol +den;
		float new_den =mol;
		mol =new_mol;
		den =new_den;
	}
	cout <<sum;
	return 0;
}
