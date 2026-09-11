#include<bits/stdc++.h>
using namespace std;

int main(){
	int tmp=0;
	for(int i=0;i<=2;i++){
		int input;
		cin>>input;
		if(tmp<input){
			tmp=input;
		}
	}
	cout<<tmp;
	return 0;
}
