#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
int main() {
    int n;
    cin >> n;
    int pr = 5003;
    int arr[n+1];
    int i;
    for(i=0;i<n+1;i++)
        arr[i] = 2*pr*i + (i*i)%pr;
    int ans[n];
    ans[0] = arr[0];
    for(i=1;i<n+1;i++)
        ans[i] = arr[i] - arr[i-1];
    for(i=1;i<=n;i++)
        cout << ans[i] << " ";
        
}s
/* Test Case : 5
 * Ans : 1 2 4 8 16
 * Explaination : 1,2,4,8,16,3,7,15,31,6,14,30,12,28,24
 */
