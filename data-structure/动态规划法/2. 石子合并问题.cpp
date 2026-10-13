#include<bits/stdc++.h>
using namespace std;
#include<bits/stdc++.h>
using namespace std;

#ifndef MAX
#define MAX (100)
#endif

int main() {
	int n;
	cin >> n;
	int p[MAX];
	for(int i=0;i<n;i++){
		cin >> p[i];
	}
	//前缀和
	int s[MAX]{0};
	for(int i=1;i<=n;i++){
		if(i==1){
			s[i]=p[0];
		}else{
			s[i]=s[i-1]+p[i-1];
		}
	}
	int m[MAX][MAX];
	for(int i=1;i<=n;i++){
		m[i][i] = 0;
	}
	//填表
	for(int r=2;r<=n;r++){
		for(int i=1;i<=n-r+1;i++){
			int j=i+r-1;
			//k=i;
			m[i][j]=0+m[i+1][j]+(s[j]-s[i-1]);
			for(int k=i+1;k<j;k++){
				int u=m[i][k]+m[k+1][j]+(s[j]-s[i-1]);
				if(u<m[i][j]){
					m[i][j] = u;
				}
			}
		}
		
	}
	cout << m[1][n];
	return 0;
}
