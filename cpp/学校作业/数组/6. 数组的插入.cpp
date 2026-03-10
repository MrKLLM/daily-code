#include<bits/stdc++.h>
using namespace std;

int main(){
	int n = 0;
	cin >> n;
	vector<int>nums;
	for(int i=0;i<=(n-1);i++){
		int a = 0;
		cin >> a;
		nums.push_back(a);
	}
	
	int insert = 0;
	cin >> insert;
	nums.push_back(insert);
	sort(nums.begin(),nums.end());
	
	for(int i=0;i<=n;i++){
		cout << nums[i] << ' ';
	}
	return 0;
}
