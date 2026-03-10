#include<iostream>
#include<cmath>
using namespace std;

int main(){
	double pi=3.14;
	double r,h,c,ccls,sphs,v;
	cin>>r>>h;
	c=2*pi*r;
	ccls=pi*pow(r,2);
	sphs=4*pi*pow(r,2);
	v=h*pi*pow(r,2);
	cout<<c<<" "<<ccls<<" "<<sphs<<" "<<v;
	return 0;
}

