#include <stdio.h>
#include <queue>
#include <vector>
 
int N, M, K;
 
std::vector<std::pair<int, int>> Links [200000];
 
bool PPDist[200000][20];
bool PDist[200000][20];
int Dist[200000][20];
 
void bfs() {
	std::priority_queue<std::pair<std::pair<int, int>, int>> opens;
	opens.push({{0, 0}, 1});
	PDist[1][0] = true;
	while (!opens.empty()){
		int d = -opens.top().first.first;
		int k = opens.top().first.second;
		int p = opens.top().second;
		opens.pop();
		if (PPDist[p][k]) continue;
		PPDist[p][k] = true;
		for (auto l : Links[p]){
			int nd = d + l.second;
			if (!PDist[l.first][k] || Dist[l.first][k] > nd) {
				Dist[l.first][k] = nd;
				PDist[l.first][k] = true;
				opens.push({{-nd, k}, l.first});
			}
			if (k < K && (!PDist[l.first][k+1] || Dist[l.first][k+1] > d)) {
				Dist[l.first][k+1] = d;
				PDist[l.first][k+1] = true;
				opens.push({{-d, k+1}, l.first});
			}
		}
	}
}
 
int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < M; i++) {
		int a, b, w;
		scanf("%d %d %d", &a, &b, &w);
		Links[a].push_back({b, w});
		Links[b].push_back({a, w});
	}
	bfs();
	for (int i = 1; i <= N; i++) {
		int min = Dist[i][0];
		for (int k = 1; k <= K; k++) {
			min = std::min(min, Dist[i][k]);
		}
		printf("%d ", min);
	}
	return 0;
}
/*Test Case:    5 6 1
				1 2 2
				1 3 6
				2 4 6
				2 5 8
				3 5 4
				4 5 1
  Ans: 0 0 0 2 2
  Explanation:
		For City 1 , we are already there charge is 0.
		For City 2 , we can reach with charge 0, by using 1 special offer for road 1 - 2.
		For City 3 , we can reach with charge 0, by using 1 special offer for road 1 - 3.
		For City 4 , we can reach with charge 2, by using path 1 - 2 - 4 , and using 1 offer for road 2 - 4.
		For City 5 , we can readh with charge 2, by using path 1 - 2 - 5 , and using 1 offer for road 2 - 5.
*/
