#include<bits/stdc++.h>
using namespace std;

int dp[100][100];//记忆化数组

int max_tri_path_sum(int arr[][100],int n,int i, int j){
	
	if(i == n-1){
		return arr[i][j];
	}
	if(dp[i][j] != -1){
		return dp[i][j];
	}
	int left =max_tri_path_sum(arr,n,i+1,j);
	int right =max_tri_path_sum(arr,n,i+1,j+1);
	
	dp[i][j] = arr[i][j]+max(left,right);
	return dp[i][j];
	
}

int main() {
	int n;
	int A[100][100]={0};
	memset(dp,-1,sizeof(dp));
	cin >> n;
	for(int i=0;i<n;i++){
		for(int j=0;j<i+1;j++){
			cin >> A[i][j];
		}
		
	}
	int res = max_tri_path_sum(A,n,0,0);
	cout << res;
	return 0;
}
