#include<bits/stdc++.h>
using namespace std;

#ifndef MAX
	#define MAX ()
#endif
int main() {
	int n = 0;
	cin >> n;
	int size = n * 2 - 1;

	int * *arr = new int*[size];
	for (int i = 0; i <= (size - 1); i++) {
		arr[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++) {

			int min_dist = 0;
			min_dist = min(i, j);
			min_dist = min( min_dist, (size - i - 1));
			min_dist = min( min_dist, (size - j - 1));
			arr[i][j] = 1 + min_dist;
		}
	}

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++) {

			if (j != 0) {
				cout << ' ';
			}
			cout << arr[i][j];
		}
		cout << endl;
	}

	for (int j = 0; j < size; j++) {

		delete[] arr[j];
	}
	delete[] arr;
	return 0;
}
