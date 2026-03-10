#include <iostream>
#include <cmath>
using namespace std;
#ifndef MAX
	#define MAX  (5)
#endif
#ifndef NULL
	#define NULL  (0)
#endif
int main() {
	int *p = NULL;
	int a = 10;
	int b = 20;
	p = &a;
	p = &b;
	cout << "sizeof(p)" << sizeof(p) << endl;
	cout << (*p) << endl;
	int arr[MAX] {1, 2, 3};
	p = arr;
	cout << (*(p + 0));
	cout << (*(p + 1));
	cout << (*(p + 2));
	int *q = p;
	q = arr + 1;
	q = p + 2;
}
