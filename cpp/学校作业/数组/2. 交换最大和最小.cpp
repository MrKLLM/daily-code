#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
	int n = 0;
	cin >> n;
	vector<int>arr;
	
	for(int i=0;i<n;i++){
		int a = 0;
		cin >> a;
		arr.push_back(a);
	}
	
	vector<int>::iterator max_it = max_element(arr.begin(),arr.end());
	int max_val = *max_it;
	
	vector<int>::iterator min_it = min_element(arr.begin(),arr.end());
	int min_val = *min_it;
	
	for(long long unsigned int i=0;i<arr.size();i++){
		if(arr[i] == max_val){
			arr[i] = min_val;
		}else if(arr[i] == min_val){
			arr[i] = max_val;
		}
	}
	
	for(long long unsigned int j=0;j<arr.size();j++){
		cout << arr[j] << ' ';
	}
	
	return 0;
}
