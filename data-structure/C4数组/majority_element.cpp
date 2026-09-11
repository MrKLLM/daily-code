/**摩尔投票法
*候选人和计数器
*计数器为0则选候选人
*不为零时，下一个数相同则计数器加1，不同则减1
*/
#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif



int main() {
	int a[15];
	int tmp;
	int num_cnt = 0;
	while(cin >> tmp){
		a[num_cnt++] = tmp;
	}

	int candidate = a[0];
	int cnt = 1;
	for (int i = 1; i < num_cnt; i++)
	{	if(cnt == 0)
		{
			candidate = a[i];
			cnt = 1;
		}
		else if (a[i] == candidate)
		{
			cnt++;
		}
		else
		{
			cnt--;
			
		}		
	}
	
	int real_cnt = 0;
	for(int i=0;i<num_cnt;i++){
		if(a[i] == candidate){
			real_cnt ++;
		}
	}
	
	if (real_cnt > num_cnt/2)
	{
		cout << candidate;
		/* code */
	}
	else
	{
		cout << -1;
		/* code */
	}
	
	return 0;
}
