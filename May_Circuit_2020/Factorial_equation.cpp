#include <stdio.h>
int main() {
    long long X, N;
    scanf("%lld %lld", &X, &N);
    if (N >= 5ll || N == 0ll) printf("1\n");
    else {
        int fact = 1;
        for (int i = 1; i <= N; i++) fact *= i;
        long long res = 1;
        for (int i = 0; i < fact; i++) {
            res = (res * X) % 10;
        }
        printf("%lld", res);
    }
}
/* Test Case: 5 2
 * Ans : 5
 * Explaination : factorial of (2) is 2*1=2  ,So 5^2=25 the last digit in 25 is 5
 */
