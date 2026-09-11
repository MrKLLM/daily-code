#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#ifndef DEBUG
	#define DEBUG (0)
#endif
#ifndef MAX
	#define MAX ()
#endif

int main() {
    int n=0,p=0,q=0 ,r=0,s=0;
    cin >> n >> p>>q>>r>>s;
    vector<int> A(n,0);
    for(int i=0;i<n;i++){
        cin >> A[i];
    } 
    vector<int> tmp(q-p+1,0);
	for(int i=0;i<q-p+1;i++){
		tmp[i] = A[p+i-1];
	}

    swap_ranges(A.begin()+p-1,A.begin()+q,A.begin()+r-1);//左闭右开区间，[a,b)

    // int len = q-p+1;
    // for(int i=0;i<len;i++){
    //     swap(A[p+i-1],A[r+i-1]);
    // }

	// for(int i=0;i<q-p+1;i++){
	// 	A[p+i-1] = A[r+i-1];
	// }
	// for(int i=0;i<q-p+1;i++){
	// 	A[r+i-1] = tmp[i];
	// }

   for(int x:A){
        cout << x <<" ";
   } 
    cout << endl;
    
	return 0;
}
