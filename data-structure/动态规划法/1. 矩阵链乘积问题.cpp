#include<bits/stdc++.h>
using namespace std;

#ifndef MAX
#define MAX (100)
#endif
int s[MAX][MAX];
void select_Matrix(int i,int j){
	if(i == j){
		cout << "A" << i;
		return;
	}
	if(j-i == 1){
		cout<<"(A"<<i<<"*"<<"A"<<j<<")";
		return;
	}
	int k = s[i][j];
	cout << "(";
	select_Matrix(i,k);
	cout << "*";
	select_Matrix(k+1,j);
	cout << ")";
	return;
}
int main() {
	int n,p[MAX];
	cin >> n;
	for(int i=0;i<=n;i++){
		cin >> p[i];
	}
	int m[MAX][MAX];
	for(int i=1;i<=n;i++){
		m[i][i] = 0;
	}
	for(int r=2;r<=n;r++){
		for(int i=1;i<=n-r+1;i++){
			int j = i+r-1;
			//k = i
			//赋初值，从头开始分割
			m[i][j]=0+m[i+1][j]+p[i-1]*p[i]*p[j];
			s[i][j]=i;
			for(int k=i+1;k<j;k++){
				int u=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(u < m[i][j]){
					m[i][j] = u;
					s[i][j] = k;
				}
			}
		}
		
	}
	cout << m[1][n] << endl;
	select_Matrix(1,n);
	return 0;
}
