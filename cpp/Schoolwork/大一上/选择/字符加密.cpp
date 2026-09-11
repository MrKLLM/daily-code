#include<bits/stdc++.h>
using namespace std;

int main(){
	char ch;
	for(int i=0;i<5;i++){
		cin>>ch;
		if(ch>118){
			cout<<(char)(97+(ch-119));
			continue;
		}
		cout<<(char)(ch+4);
	}
	return 0;
}
