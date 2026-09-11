#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	int n = 0;
	cin >> n;
	
	long long rep = 0;
	vector<long long>reps;
	for(int i=1;i<=12;i++){
		rep += pow(10,i-1);
		reps.push_back(rep);
	}
	
	set<long long>sum;
	for(long long a : reps){
		for(long long b : reps){
			for(long long c : reps){
				sum.insert(a+b+c);
			}
		}
	}
	
	vector<long long>sum_1(sum.begin(),sum.end());
	sort(sum_1.begin(),sum_1.end());
	
	cout << sum_1[n-1];
	
	return 0;
}
