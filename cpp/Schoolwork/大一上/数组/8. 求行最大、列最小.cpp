#include<bits/stdc++.h>
using namespace std;

int main(){
	int m ,n;
	cin >> m >> n;
	int matrix[10][10];
	int max_elm = 0;
	int min_elm = 0;
	
	for(int i=0;i<=(m-1);i++){
		
		for(int j=0;j<=(n-1);j++){
			int a = 0;
			cin >> a;
			matrix[i][j] = a;
			
		}
	}
	
	for(int i=0;i<=(m-1);i++){
		max_elm = matrix[i][0];
		for(int j=0;j<=(n-1);j++){
			
			if(max_elm < matrix[i][j]){
				max_elm = matrix[i][j];
			}
		}
		cout << max_elm << ' ';
		
	}
	cout << endl;
	
	for(int j=0;j<=(n-1);j++){
		min_elm = matrix[0][j];
		for(int i=0;i<=(m-1);i++){
			
			if(min_elm > matrix[i][j]){
				min_elm = matrix[i][j];
			}
		}
		cout << min_elm << ' ';
	}
	
	return 0;
}
