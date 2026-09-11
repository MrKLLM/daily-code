#include<iostream>
#include<cmath>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif

double calProgression(int n) {
	double per_dig = (pow(-1, n + 1) / (n * (n + 1)));
	return per_dig;
}
int main() {
	int k;
	cin >> k;
	double sums = 0;
	for (int i = k; i > 0; i--) {
		sums += calProgression(i);
	}
	cout << sums;
	return 0;
}
