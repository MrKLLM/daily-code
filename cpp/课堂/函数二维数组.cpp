#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif

void f3(int* a, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int i = 0; i < n; i++) {
			cout << *(a + i * n + j) <<" ";
		}
		cout << endl;
	}
}
int main() {


	return 0;
}
