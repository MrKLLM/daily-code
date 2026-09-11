#include<bits/stdc++.h>
using namespace std;

int main(){
	int N=0;
	cin >> N;
	vector <int> A;
	for(int i=0;i<N;i++){//存
		int x;
		cin >> x;
		A.push_back(x);
	}
	for(int i=0;i<(N-1);i++){//算
		int result = A[i] * A[i+1];
		cout << result << ' ';
	}
	return 0;
}
