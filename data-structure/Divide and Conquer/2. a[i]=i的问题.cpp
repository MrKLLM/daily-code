#include<bits/stdc++.h>
using namespace std;

static int idx = 0;
int solve(int* arr,int lo,int hi,int* ans){
	
	if(lo > hi){
		return idx;
	}
	if(arr[lo] > hi){
		return idx;
	}
	if(arr[hi] < lo){
		return idx;
	}
	if(lo == hi){
		if(arr[lo] == lo){
			ans[idx++] = lo;
		}
		return idx;
	}
	int mid = lo+(hi-lo)/2;
	solve(arr,lo,mid,ans);
	solve(arr,mid+1,hi,ans);
	return idx;
}

int main() {
	int n;
	int arr1[100];
	int ans[100];
	cin >> n;
	for(int i=0;i<n;i++){
		cin >>  arr1[i];
	}
	solve(arr1,0,n-1,ans);
	if(idx == 0){
		cout << -1;
	}else{
	for(int i=0;i<idx;i++){
		cout << ans[i] <<' ';
	}
	}
	return 0;
}
