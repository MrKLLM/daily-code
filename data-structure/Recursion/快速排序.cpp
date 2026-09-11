#include<bits/stdc++.h>
using namespace std;

int position(int arr[],int l,int r){
	int pivot = arr[l];
	while(l<r){
		while(l<r && pivot<=arr[r]){
			r--;
		}
		if(l<r){
			arr[l] = arr[r];
		}
		while(l<r && pivot>=arr[l]){
			l++;
		}
		if(l<r){
			arr[r] = arr[l];
		}
	}
	//循环结束
	arr[l] = pivot;
	return l;
	
}

void quick_sort(int arr[], int l, int r){
	if (l>=r)
	{
		return;
	}
	int MediaIndex = position(arr, l, r);
	quick_sort( arr, MediaIndex+1, r);
	quick_sort( arr, l, MediaIndex-1);
}

int main() {
	int n;
	int arr1[10]{0};
	cin >> n;
	if (n < 0 || n > 10) {
		return 1;
	}
	for (int i = 0; i < n; i++)
	{
		int tmp = 0;
		cin >> tmp;
		arr1[i] = tmp;
	}
	quick_sort(arr1,0,n-1);
	for (int i = 0; i < n; i++)
	{
		cout << arr1[i] << ' ';
	}
	return 0;
}

