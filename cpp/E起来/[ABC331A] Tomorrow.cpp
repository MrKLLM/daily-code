#include<bits/stdc++.h>
using namespace std;

struct Date{
	int y;
	int m;
	int d;
};
int main(){
	int M,D;
	Date today;
	cin >> M >> D >> today.y >> today.m >> today.d;
	
	if (today.d < D) {
		today.d++;
	} else {
		today.d = 1;
		if (today.m < M) {
			today.m++;
		} else {
			today.m = 1;
			today.y++;
		}
	}	
	
	cout << today.y << ' ';
	cout << today.m << ' ';
	cout << today.d;
	return 0;
}
