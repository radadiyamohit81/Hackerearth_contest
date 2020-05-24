#include <stdio.h>
#include <algorithm>
 
int Mat[1000][1000][3];
int N, M;
 
int Count[1000][1000][3][3][2];
 
int main() {
    scanf("%d %d", &N, &M);
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < M; col++) {
            long long v;
            scanf("%lld", &v);
            while (v%107ll == 0) {
                if (++Mat[row][col][0]==2) break;
                v /= 107ll;
            }
            while (v%1361ll == 0) {
                if (++Mat[row][col][1]==2) break;
                v /= 1361ll;
            }
            while (v%10000019ll == 0) {
                Mat[row][col][2]++;
                v /= 10000019ll;
                break;
            }
        }
    }
    const int mod = 1000000007;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < M; col++) {
            const int A = Mat[row][col][0];
            const int B = Mat[row][col][1];
            const int C = Mat[row][col][2];
            // printf("%d %d - %d %d %d\n", row, col, A, B, C);
            if (row == 0 && col == 0) {
                Count[row][col][A][B][C] = 1;
            } else {
                if (col > 0) {
                    for (int a = 0; a <= 2; a++) {
                        for (int b = 0; b <= 2; b++) {
                            for (int c = 0; c <= 1; c++) {
                                Count[row][col][std::min(2, A+a)][std::min(2, B+b)][std::min(1, C+c)] = 
                                    (Count[row][col][std::min(2, A+a)][std::min(2, B+b)][std::min(1, C+c)] +
                                     Count[row][col-1][a][b][c]) % mod;
                            }
                        }
                    }
                }
                if (row > 0) {
                    for (int a = 0; a <= 2; a++) {
                        for (int b = 0; b <= 2; b++) {
                            for (int c = 0; c <= 1; c++) {
                                Count[row][col][std::min(2, A+a)][std::min(2, B+b)][std::min(1, C+c)] = 
                                    (Count[row][col][std::min(2, A+a)][std::min(2, B+b)][std::min(1, C+c)] +
                                     Count[row-1][col][a][b][c]) % mod;
                            }
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int a = 0; a <= 2; a++) {
        for (int b = 0; b <= 2; b++) {
            for (int c = 0; c <= 1; c++) {
                if (a+b+c == 5) continue;
                ans = (ans + Count[N-1][M-1][a][b][c]) % mod;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
/* Test Case :  2 2
				1 212072634227239451
				1 1
   Ans : 1
   Explaination : There are two paths in this matrix :   

				(1,1) -> (1,2) -> (2,2)  : Product of path is 1 * 212072634227239451 * 1 =  212072634227239451 which is not safe.

				(1,1) -> (2,1) -> (2,2) :  Product of path is 1 * 1 * 1 =  1 which is safe and can be taken.

				Hence total no of safe paths modulo 109 + 7   =  1
*/
