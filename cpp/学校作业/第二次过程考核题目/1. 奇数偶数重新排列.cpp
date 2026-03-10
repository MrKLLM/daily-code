#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif
int main() {
	int n;
	cin >> n;
	int arr1[100];
	int arr2[100];
	int tmp1 = 0;
	int tmp2 = 0;
	for(int i=0;i<n;i++){
		int a = 0;
		cin >> a;
		if(a % 2 == 0){
			arr1[tmp1] = a;
			tmp1++;
		}else{
			arr2[tmp2] = a;
			tmp2++;
		}
	}
	
	for(int i=0;i<tmp2;i++){
		cout << arr2[i] << ' ';
	}
	for(int i=0;i<tmp1;i++){
		cout << arr1[i] ;
		if(i != tmp1-1){
			cout << ' ';
		}
	}
	return 0;
}
