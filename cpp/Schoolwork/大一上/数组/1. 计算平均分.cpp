#include<iostream>
#include<vector>

using namespace std;

int main(){
	vector <double> grade;
	double cin_num;
	cin >> cin_num;
	while(0 < cin_num){
		grade.push_back(cin_num);
		cin >> cin_num;
	}
	//算平均数
	double avg = 0;
	double sum = 0;
	for(long long unsigned int i=0;i<grade.size();i++){
		sum+=grade[i];
	}
	avg = (double)sum/grade.size();
	cout << avg << endl;
	//筛选低于平均值的数
	vector<double> under_avg;
	for(long long unsigned int i=0;i<grade.size();i++){
		double b = grade[i];
		if(0 < avg - b){
			cout << b << ' ';
		}
	}
	return 0;
}
