#include<bits/stdc++.h>
using namespace std;

int main(){
	int N,K;
	cin >> N >> K;
	unordered_set<int> appear_num;
	
	for(int i=0;i<N;i++){
		int x=0;
		cin >> x;
		if(x >= 1 && x <= K){ 
			appear_num.insert(x);
		}
	}
	
	long long appear_sum=0;
	for(int num:appear_num){
		appear_sum += num;//出现的数的和
	}
	
	long long sum =(long long)K*(K+1)/2;//1~k总和
	long long disappear_sum = sum - appear_sum;
	cout << disappear_sum;
	return 0;
}
