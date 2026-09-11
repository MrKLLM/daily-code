#include<bits/stdc++.h>
using namespace std;

int main(){
	int num;
	cin >> num;
	
	int max_digit = 0;  // 存储最大数字，初始为0
	int temp = num;     // 临时变量，用于提取数字
	
	// 循环提取每位数字并比较
	while (temp > 0) {
		int digit = temp % 10;  // 取最后一位数字（如1423%10=3）
		if (digit > max_digit) {  // 更新最大值
			max_digit = digit;
		}
		temp = temp / 10;  // 去掉最后一位（如1423/10=142）
	}
	
	cout << max_digit << endl;
	return 0;
}
//废稿
//#include<bits/stdc++.h>
//using namespace std;
//
//int main(){
//	int num =0;
//	cin >>num;
//	
//	int val[num];
//	int tmp1 =num;
//	int tmp2=0;
//	int i=1;
//	int n=1;
//	
//	while(tmp1 >=1){
//		val[i] =tmp1%10;
//		tmp1/=10;
//		i++;
//	}
//	
//	for( ;i>0 ;i--){
//		if(tmp2 <=val[n]){
//			tmp2=val[n];}
//		n++;
//	}
//	cout <<tmp2;
//	return 0;
//}
