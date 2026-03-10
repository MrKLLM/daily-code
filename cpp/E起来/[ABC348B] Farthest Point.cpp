#include<bits/stdc++.h>
using namespace std;

struct Point{
	int x;
	int y;
};

int main(){
	int N;
	cin >> N;
	Point points[105];
	for(int i=0;i<N;i++){//标坐标，同时给点附上编号 (记住，[]里是编号)
		cin >> points[i].x >> points[i].y;
	}
	//遍历每个点，找最远点
	for(int i=0;i<N;i++){
		//放在循环里 每次都可以重置
		int max_d_sqr=-1;//声明最大距离的平方
		int farest_d_code=-1;//最远点编号
		for(int j=0;j<N;j++){//遍历其他点
			if(j==i){//跳过自己
				continue;
			}
			
			int dx=points[i].x-points[j].x;
			int dy=points[i].y-points[j].y;
			int d_sqr=dx*dx+dy*dy;
			
			if(d_sqr>max_d_sqr){
				max_d_sqr=d_sqr;
				farest_d_code=j+1;
			}else if(d_sqr==max_d_sqr){//距离相等
				if((j+1)>farest_d_code){
					farest_d_code=farest_d_code;
				};//取小标号
			}
		}
		cout << farest_d_code << endl;
	}
	return 0;
}
