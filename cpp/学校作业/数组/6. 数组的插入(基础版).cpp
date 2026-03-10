#include<bits/stdc++.h>
using namespace std;

int main(){
	int n = 0;
	cin >> n;
	int nums[10];
	for(int i=0;i<=(n-1);i++){
		int a = 0;
		cin >> a;
		nums[i] = a;
	}
	
	int index = 0;
	int insert;
	cin >> insert;
	for(int i=0;i<=(n-1);i++){//找插入位置
		if(nums[i] > insert){
			index = i;
		}
	}
	
	for(int i=n;i>index;i--){
		nums[n] = nums[n-1];
	}
	
	for(int i=0;i<n+1;i++){
		cout << nums[i] << ' ';
	}
	return 0;
}
