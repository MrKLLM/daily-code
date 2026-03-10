#include<bits/stdc++.h>
using namespace std;
//#ifndef MAX
//#define MAX ()
//#endif

bool jdgPrime(int n){

	if(n == 2){
		return true;
	}
	
	if(n <= 1 || n % 2 == 0){
		return false;
	}else{
		
		bool isPrime = true;
		for(int i=3;i * i <= n;i+=2){//得等于sqrt n
			if(n % i == 0){
				isPrime = false;
				break;
			}else{
				continue;
			}
		}
		if(isPrime){
			return true;
		}else{
			return false;
		}
	}
	
}
int main() {
	
	int num;
	cin >> num;
	int a = 0;
	int b = 0;
	
	for(int i=2;i<=(num / 2);i++){//过半对称，必须等于一半
		a = i;
		b = num - a;
		bool conform_to_conj = jdgPrime(a) && jdgPrime(b);
		if(conform_to_conj){
			cout << num << '=' << a << '+' << b;
			return 0;
		}
	}
	return 0;
}
