#include<iostream>
#include<cmath>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif

float func(float x) {
	float y = 0;
	if (x <= 0) {
		y = sin(x) +1;
	} else if (x >= 10) {
		y = sqrt(x+4);
	} else {
		y = pow(x, 2) +3 / x;
		
	}
	return y;
}
int main() {
	float x = 0;
	cin >> x;
	float y = func(x);
	cout << y;

	return 0;
}
