#include<bits/stdc++.h>
using namespace std;

int main(){
	int N = 0;
	int sum = 0;
	int An=0;
	cin >> N;
	int A[100];
	for(int i=0;i<N-1;i++){
		cin >> A[i];
	}
	for(int i=0;i<N-1;i++){
		sum+=A[i];
	}
	An=-sum;
	cout << An;
	return 0;
}
