#include<bits/stdc++.h>

using namespace std;

#ifndef MAX
#define MAX (100)
#endif

int main(){
	string x,y;
	cin >> x >> y;
	/*
	C[m][n]=
	C[m-1][n-1]+1,x[m] == y[n]
	max(C[m-1][n],C[m][n-1]),x[m] != x[n]
	*/
	int C[100][100];
	for(int i=0;i<=x.size();i++){
		for(int j=0;j<=y.size();j++){
			if(i == 0 || j == 0){
				C[i][j]=0;
			}else if(x[i-1] == y[j-1]){
				C[i][j] = 1 + C[i-1][j-1];
			}else{
				C[i][j] = max(C[i-1][j],C[i][j-1]);
			}
			
		}
	}
	cout << C[x.size()][y.size()];
}
