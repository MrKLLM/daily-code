#include<bits/stdc++.h>
using namespace std;
const double PI=3.1415926;

int main(){
	double start=0;
	double end=0;
	double step=0;
	cin >> start >> end >> step;
	
	double per_area=0;
	double integal=0;
	
	for(double i=start;i<end;i+=step){
		per_area=(1.0/2.0)*step*(fabs(tan(i))+fabs(tan(i+step)));
		integal+=per_area;
	}
	
	cout << integal;
}
