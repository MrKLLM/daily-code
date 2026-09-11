#include<bits/stdc++.h>
using namespace std;

int main(){
	long long N;
	cin >> N;
	
	long long A [N+5];
	for(long long i=0;i<N;i++){
		cin >> A [i]; 
	}
	
	long long S [N+5];
	long long T [N+5];
	for(long long i=0;i<N-1;i++){
		cin >> S [i] >> T [i];
	}
	
	long long haved_currency = A[0];//现在的有的国家的货币单位数
	for(long long i=0;i<(N-1);i++){
		long long new_get = 0;//用于换算货币的变量
		if(S[i] >= T [i]){
			new_get = (haved_currency /S [i])*T [i];
			haved_currency = A [i+1] + new_get;//新货币的储量
		}else{
			continue;
		}
	}
	
	cout << haved_currency;
}
