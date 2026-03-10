#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif
int main() {
	int n = 0;
	cin >> n;
	int nums[100];

	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		nums[i] = a;
	}

	int cishu = 0;
	for (int i = 0; i < n; i++) {
		bool sorted = false;
		for (int j = 0; j < n - 1 - i; j++) {
			if(nums[j] < nums[j+1]){
				int tmp = nums[j];
				nums[j] = nums[j+1];
				nums[j + 1] = tmp;
				sorted = true;
			}
		}
		if(sorted){
			cishu ++;
		}
		
	}
	
	
	if(cishu != n-1){
		cishu+=1;
	}
	for(int i=0;i<n;i++){
		cout << nums[i];
		if(i!=n-1){
			cout << ' ';
		}else{
			cout << endl;
		}
	}
	cout << cishu;
	return 0;
}
