#include <iostream>
using namespace std;

int p(int n,int m){
	if(n<1 || m<1){
		return 0;
	}
	if(m == 1){
		return 1;
	}
	if(n < m ){
		return p(n,n);
	}
	if(n == m){
		return 1 + p(n,n-1);
	}
	if(n > m){
		return p(n-m,m)+p(n,m-1);//用了m + 用了小于m
	}
	return 0;
		
}

int main() {
	int n;
	cin >> n;
	cout << p(n,n);
	return 0;
}
