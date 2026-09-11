#include<bits/stdc++.h>
using namespace std;

// 快速排序的划分函数，返回分界元素最终位置（从1开始计数）
int partition(int arr[], int low, int high) {
    int pivot = arr[low];  // 选择第一个元素作为分界元素
    int i = low;
    int j = high;
    
    while (i < j) {
        // 从右向左找小于pivot的元素
        while (i < j && arr[j] >= pivot) {
            j--;
        }
        if (i < j) {
            arr[i] = arr[j];
            i++;
        }
        
        // 从左向右找大于pivot的元素
        while (i < j && arr[i] <= pivot) {
            i++;
        }
        if (i < j) {
            arr[j] = arr[i];
            j--;
        }
    }
    
    arr[i] = pivot;
    return i + 1;  // 返回从1开始的位置
}

// 快速排序
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotPos = partition(arr, low, high);
        quickSort(arr, low, pivotPos - 2);  // pivotPos是1-based，转换为0-based要减1，再减1是左半部分
        quickSort(arr, pivotPos, high);     // 从pivotPos开始是右半部分（0-based）
    }
}

// 修正的快速排序，使用0-based索引
void quickSortHelper(int arr[], int low, int high) {
    if (low < high) {
        // 手动实现划分
        int pivot = arr[low];
        int i = low;
        int j = high;
        
        while (i < j) {
            while (i < j && arr[j] >= pivot) j--;
            if (i < j) arr[i++] = arr[j];
            while (i < j && arr[i] <= pivot) i++;
            if (i < j) arr[j--] = arr[i];
        }
        arr[i] = pivot;
        
        quickSortHelper(arr, low, i - 1);
        quickSortHelper(arr, i + 1, high);
    }
}

int main() {
    int n;
    cin >> n;
    
    int arr[1000];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // 第一次划分，获取分界元素位置
    int firstPivotPos = partition(arr, 0, n - 1);
    
    // 输出第一次划分后分界元素的位置
    cout << firstPivotPos << " ";
    
    // 重新读取数据进行完整排序
    // 由于partition已经修改了数组，我们需要重新读取或使用副本
    // 但根据题目，第一次划分后数组已经改变，我们需要在此基础上完成排序
    
    // 实际上，partition已经修改了数组，我们在此基础上继续排序
    // 先找到pivot的0-based位置
    int pivotIdx = firstPivotPos - 1;
    
    // 对左右两部分分别排序
    quickSortHelper(arr, 0, pivotIdx - 1);
    quickSortHelper(arr, pivotIdx + 1, n - 1);
    
    // 输出最终排序结果
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
    
    return 0;
}
