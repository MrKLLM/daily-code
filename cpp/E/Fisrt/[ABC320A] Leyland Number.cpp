#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif
int main(){
	int A ,B;
	cin >> A >> B;
	int sum = pow(A,B) + pow(B,A);
	cout << sum;
	return 0;
	
}
