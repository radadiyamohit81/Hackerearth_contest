#include <stdio.h>
#include <algorithm>
 
long long A, B;
 
long long maxi(long long n) {
	long long ans = 1;
	while (n) {
		n /= 2ll;
		ans = 2ll*ans;
	}
	return ans;
}
 
long long solve(long long a, long long b) {
	if (a == b) return 1;
	long long p2 = 1;
	for (int i = 61; i >= 0; i--) p2 *= 2ll;
	for (;(a&p2) == (b&p2); p2 /= 2ll) {
		if (a&p2) {
			a -= p2;
			b -= p2;
		}
	}
	long long n1 = maxi(b - p2);
	long long n2 = p2-a;
	long long s = n1 + n2;
	if (s >= p2) return p2 + n2;
	return n2 + s;
}
 
int main() {
	scanf("%lld %lld", &A, &B);
	printf("%lld", solve(A, B));
}
/*Test Case: 7
			 9
  Ans: 4
  Explaination:
		In this case, A=7 and B=9. There are four integers that can be generated doing the bitwise OR of a non-empty subset of {7, 8, 9}: 7, 8, 9 and 15
*/
