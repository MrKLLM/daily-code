#include<iostream>
#include<climits>
#include<string>
using namespace std;
#ifndef DEBUG
	#define DEBUG (0)
#endif
#ifndef MAX
	#define MAX ()
#endif

int main() {
	int n=0;
    long long A=0,B=0;
    cin>>n>>A>>B;
    string s;
    cin>>s;

    long long min_cost = LLONG_MAX;
    for (int k = 0; k < n; k++)
    {
        // string tmp_s = s.substr(k) + s.substr(0,k);
        long long cost = k * A;
        int diff = 0;

        for (int i = 0; i < n/2; i++)
        {
            int j = n - i - 1;
            char c1 = s[(i+k)%n];
            char c2 = s[(j+k)%n];
            if (c1 != c2)
            {
                diff ++;
            }
        }
        cost += (long long)diff * B;
        if (min_cost > cost)
        {
            min_cost = cost;
        }
        
    }
    
    cout << min_cost << endl; 
	return 0;
}
