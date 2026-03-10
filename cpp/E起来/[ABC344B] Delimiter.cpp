#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	vector <int> A;
	int num=0;
	while(1){
		cin >> num;
		A.push_back(num);
		if(num==0){
			break;
		}
	}
	
	reverse(A.begin(),A.end());
	
	for(int a : A){
		cout << a <<endl;
	}
	
	return 0;
}
