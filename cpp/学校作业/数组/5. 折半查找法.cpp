#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif
int main(){
	int n = 0;
	cin >> n ;
	int* nums = new int [n];
	for(int i=0;i<=(n-1);i++){
		cin >> nums[i];
	}
	
	int target = 0;
	cin >> target;
	
	int low = 0;
	int high = n-1;
	int half ;//中值下标
	int freq = 0;
	bool result = false;
	
	while(low <= high){
		freq++;
		half = (low + high) / 2;
		if(nums[half] == target){
			result = true;
			cout << half << endl << freq;
			break;
		}else{
			if(nums[half] < target){
				low = half + 1;
			}else{
				high = half - 1;
			}
		}
	}
	
	if(!result){
		cout << "no" << endl << freq;
	}
	
	delete[] nums;
	
	return 0;
}
