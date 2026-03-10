#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif
#ifndef DEBUG
	#define DEBUG (0)
#endif
int main() {
	string s;
	int k;
	cin >> s >> k;
	int len = s.length();
	char* chas = new char[len];

	for (size_t i = 0; i < s.length(); i++) {
		char cha = s[i];
		if ('A' <= cha && cha <= 'Z') {
			chas[i] = char(cha + ('a' - 'A'));

			if (DEBUG) {
				cout << chas[i];
			}
		} else {
			chas[i] = char(cha - ('a' - 'A'));

			if (DEBUG) {
				cout << chas[i];
			}
		}
	}

	for (int i = 0; i < len; i++) {

		int dist = 0;
		if (('a' <= chas[i]) && (chas[i] <= 'z')) {

			dist = 'z' - chas[i];

			if (dist >= k) {
				cout << (char)(chas[i] + k);
			} else {
				cout << (char)(('a' - 1) + ( k - dist ));

			}
		} else if (('A' <= chas[i]) && (chas[i] <= 'Z')) {

			dist = 'Z' - chas[i];

			if (dist >= k) {
				cout << (char)(chas[i] + k);
			} else {
				cout << (char)(('A' - 1) + ( k - dist ));

			}
		}
	}

	return 0;
}
