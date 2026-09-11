#include<bits/stdc++.h>
using namespace std;

int main(){
	int N=0;
	int K=0;
	cin >> N >> K;
	
	vector <int> series ;
	int num;
	for(int i=1;i<=N;i++){//存and筛
		int x=0;
		if(i==900){
			x=x;
		}
		cin >> num;
		if(num%K==0){
			series.push_back(num/K);
		}
	}
	
	sort(series.begin(),series.end());//升序排
	
	for(vector <int>::size_type i=0;i<series.size();i++){
		cout << series[i] << ' ';
	}
	return 0;
}
