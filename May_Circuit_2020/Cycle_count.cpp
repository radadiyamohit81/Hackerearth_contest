#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    long long n;
    cin >> n;
    cout << n * (n - 1) + 1 << '\n';
  }
  return 0;
}
/*
 * Test case:   2
				3
				4
   Ans : 7 13
 */
