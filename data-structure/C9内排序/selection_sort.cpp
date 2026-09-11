#include<iostream>
using namespace std;

// 选择排序函数
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // 找到从 i 到 n-1 范围内的最小元素的索引
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // 将找到的最小元素与当前位置 i 的元素交换
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

int main() {
    int n = 0;
    int arr[1000];  // 假设最大数组大小为 1000
    
    // 读取输入
    int num;
    while (cin >> num) {
        arr[n] = num;
        n++;
    }
    
    // 执行选择排序
    selectionSort(arr, n);
    
    // 输出排序后的结果
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            cout << " ";
        }
        cout << arr[i];
    }
    cout << endl;
    
    return 0;
}
