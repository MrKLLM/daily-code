#include<bits/stdc++.h>
using namespace std;

int main(){
	int m, n;
	cin >> m >> n;
	int num = 0;
	double sum = 0;//求素数总和
	bool havePrime=false;//判断有没有质数
	for(int i=m;i<=n;i++){//从m到n遍历
		//筛选质数
		if(i <= 1 
		   || (i % 2==0 && i != 2)){// 小于等于1的数不是质数,偶数不是质数（除了2）
			continue;
		}else if(i==2){
			havePrime =true;//找到质数了！
			sum+=i;
			num++;
		}else{
			bool isPrime = true;
			for(int j= 3 ; j*j<=i ; j+=2){// 只需检查到√i，且步长为2（只查奇数）
				if(i%j==0){
					isPrime = false;//排除不是素数的数
					break;
				}
			}
			if(isPrime){
				havePrime = true;
				sum +=i;
				num++;
			}
		}
	}
	if(havePrime == false){//没找到
		cout << "no";
	}else{//找到并输出素数个数和平均值
		cout << num << " " << sum/num;
	}
	return 0;
}
