#include<bits/stdc++.h>
using namespace std;

int main(){
	int n = 0;
	cin >> n;
	int nums[n+5];
	for(int i=0;i<n-1;i++){
		int a = 0;
		cin >> a;
		nums[i] = a;
	}
	
	int pass_count = 0;
	
	for(int i=0;i<n-1;i++){
		bool sorted = false;
		for(int j=0;j<n-1-i;j++){
		
			if(nums[j] < nums[j+1]){
				int tmp = nums[j];
				nums[j] = nums[j+1];
				nums[j+1] = tmp;
				sorted = true;
			}
			
		}
		if(sorted){
			pass_count++;
		}
	}
	
	for(int i=0;i<n-1;i++){
		cout << nums[i] << ' ';
		if(i == (n-1)){
			cout << endl;
		}
	}
	if((n-1) > pass_count){
		pass_count+=1;
	}
	
	cout << pass_count;
	return 0;
}

