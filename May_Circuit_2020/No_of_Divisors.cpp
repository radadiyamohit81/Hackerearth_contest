#include <stdio.h>
#include <algorithm>
int N, K;
long long count(long long n, long long k) {
    if (n == 0) return 0;
    long long ans = n*(n+1)/2;
    n /= k;
    ans -= k * n*(n+1)/2;
    ans += count(n, k);
    return ans;
}
 
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &N, &K);
        printf("%lld\n", count(N, K));
    }
    return 0;
}
/* Test Case:   4
				10 3
				10 2
				10 5
				1000000000 97
   Ans :    41
			36
			43
			494897959532893312
   Explaination :   In the first test case, f (x) from 1 to 10 is [1, 2, 1, 4, 5, 2, 7, 8, 1, 10], sum of which is 41.
					In the second test case, f (x) from 1 to 10 is [1, 1, 3, 1, 5, 3, 7, 1, 9, 5].
					In the third test case, f (x) from 1 to 10 is [1, 2, 3, 4, 1, 6, 7, 8, 9, 2].
*/
