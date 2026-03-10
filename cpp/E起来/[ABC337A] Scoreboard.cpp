#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	int N = 0;
	cin >> N;
	int* Takahashi_score = new int [N];
	int* Aoki_score = new int [N];
	
	for(int i=0;i<N;i++){
		cin >> Takahashi_score[i] >> Aoki_score[i];
	}
	
	int Takahashi_sum = accumulate(Takahashi_score, Takahashi_score+N, 0);
	int Aoki_sum = accumulate(Aoki_score, Aoki_score+N, 0);
	
	if(Takahashi_sum > Aoki_sum){
		cout << "Takahashi";
	}else if(Takahashi_sum < Aoki_sum){
		cout << "Aoki";
	}else{
		cout << "Draw";
	}
	
	return 0;
}
