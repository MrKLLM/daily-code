#include<bits/stdc++.h>
using namespace std;

int partition(int* arr,int l,int r){
	int pivot = arr[l];
	
	while(l<r){
		while(l<r && arr[r] >= pivot) r--;
		if(l < r){
			arr[l] = arr[r];
			l++;
		}
		while(l<r && arr[l] <= pivot) l++;
		if(l < r){
			arr[r] = arr[l];
			r--;
		}
		
	}
	arr[l] = pivot;
	return l;
}

void quickSort(int* arr,int l,int r){
	if(l >= r){
		return;
	}
	int pivot = partition(arr,l,r);
	quickSort(arr,l,pivot-1);
	quickSort(arr,pivot+1,r);
}

int main() {
	int n = 0;
	cin >> n;
	int arr1[100];
	for(int i=0;i<n;i++){
		cin >> arr1[i];
	}
	quickSort(arr1,0,n-1);
	for(int i=0;i<n;i++){
		cout << arr1[i] << ' ';
	}
	return 0;
}
