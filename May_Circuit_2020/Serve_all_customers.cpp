#include <bits/stdc++.h>
#include <sys/time.h>
 
const int MAXA = 100000;
const int MAXB = 10000;
const int MAXC = 10000;
const int MAXN = 10000;
const int MAXT = 1000000000;
 
int N, K;
int A[MAXN];
int B[MAXN];
int C[MAXN];
const int RNG = 1905;
 
static inline double get_time() {
	timeval tv;
	gettimeofday(&tv, 0);
	return tv.tv_sec + tv.tv_usec * 1e-6;
}
double start_time = get_time();
double end_time = start_time + 0.9;
 
std::vector<int> order;
int ST[MAXN];
unsigned long long BST[MAXN];
long long BEST;
 
int QUEUE[32*1024];
 
void init() {
	std::memset(QUEUE, 0, 4*(K+1));
}
 
inline int top() {
	return QUEUE[1];
}
 
void FixAssignment() {
	std::vector<std::vector<int>> schedules(K);
	std::priority_queue<std::pair<int, int>> queues;
	queues.push({-MAXT, -1});
	std::vector<int> available;
	for (int i = 0; i < K; i++) available.push_back(i);
	std::vector<int> list;
	for (int i = 0; i < N; i++) list.push_back(i);
	std::sort(list.begin(), list.end(), [&](int a, int b) {
		if (BST[a] < 0) return false;
		return BST[a] < BST[b];
	});
	long long sc = 0;
	for (int i = 0; i < N; i++) {
		const int a = list[i];
		while (!queues.empty() && queues.top().first >= -BST[a]) {
			available.push_back(queues.top().second);
			queues.pop();
		}
		if (queues.empty()) break;
		int n = rand() % available.size();
		int k = available[n];
		available[n] = available.back();
		available.pop_back();
		schedules[k].push_back(a);
		queues.push({-(BST[a] + B[a]), k});
		sc += (long long)C[a] * (BST[a] + B[a] - A[a]);
	}
	// fprintf(stderr, "Score:    %lld\n", sc);
	sc = 0;
	for (int k = 0; k < K; k++) {
		int curr = 0;
		for (int i : schedules[k]) {
			BST[i] = std::max(A[i], curr);
			curr = BST[i] + B[i];
			sc += (long long)C[i] * (BST[i] + B[i] - A[i]);
		}
	}
	// fprintf(stderr, "After:    %lld\n", sc);
	BEST = sc;
}
 
void Check() {
	std::vector<std::pair<int, int>> list;
	for (int i = 0; i < N; i++) {
		list.push_back({ST[i], 1});
		list.push_back({ST[i] + B[i], -1});
		if (ST[i] < A[i]) {
			printf("Error too early %d vs %d (%d)\n", ST[i], A[i], i);
			while (1);
		}
	}
	std::sort(list.begin(), list.end());
	int cc = 0;
	for (auto l : list) {
		cc += l.second;
		if (cc > K) {
			printf("Too many (%d)\n", l.first);
			while (1);
		}
	}
}
 
void replace(int t, int pos = 1) {
	while (true) {
		const int pp = pos * 2;
		if (QUEUE[pp] <= QUEUE[pp+1]) {
			if (t <= QUEUE[pp]) {
				QUEUE[pos] = t;
				return;
			}
			QUEUE[pos] = QUEUE[pp];
			pos = pp;
		} 
		else {
			if (t <= QUEUE[pp+1]) {
				QUEUE[pos] = t;
				return;
			}
			QUEUE[pos] = QUEUE[pp+1];
			pos = pp+1;
		}
	}
}
 
long long smartScore() {
	std::list<std::pair<int, int>> dummy = {std::make_pair(MAXT, MAXT)};
	std::vector<std::list<std::pair<int, int>>> queues(K, {{0, 0}});
	long long sc = 0;
	for (int i : order) {
		auto best = dummy.begin();
		int bk = -1;
		if (K < 100) std::random_shuffle(queues.begin(), queues.end());
		for (int k = 0; k < K; k++) {
			int last = 0;
			auto it = std::next(queues[k].begin());
			while (it != queues[k].end()) {
				if (it->first <= A[i] + B[i] || it->first - last < B[i]) {
					last = it->second;
					++it;
					continue;
				}
				break;
			}
			auto c = std::prev(it);
			if (bk >= 0) {
				if (c->second > A[i]) {
					if (c->second > best->second) continue;
				} 
				else if (c->second < best->second) {
					continue;
				}
			}
			best = c;
			bk = k;
		}
		if (best->second >= A[i]) {
			ST[i] = best->second;
			sc += (long long)(ST[i] - A[i] + B[i]) * C[i];
			best->second += B[i];
		} 
		else {
			ST[i] = A[i];
			queues[bk].insert(++best, std::make_pair(A[i], A[i]+B[i]));
			if (best != queues[bk].end()) {
				if (best->first < A[i] + B[i]) {
					printf("NOOOOOOO\n");
				}
			}
			sc += (long long)(ST[i] - A[i] + B[i]) * C[i];
		}
	}
	return sc;
}
 
long long score() {
	init();
	long long sc = 0;
	for (int i : order) {
		int s = std::max(top(), A[i]);
		ST[i] = s;
		replace(s + B[i]);
		sc += (long long)(s - A[i] + B[i]) * C[i];
	}
	return sc;
}
 
void gen() {
	N = MAXN;
	K = 5;
	for (int i = 0; i < N; i++) {
		ST[i] = A[i] = rand()%MAXA + 1;
		B[i] = rand()%MAXB + 1;
		C[i] = rand()%MAXC + 1;
		order.push_back(i);
	}
}
 
int main() {
	long long sum = 0;
	#ifdef LOCAL
	gen();
	#else
	srand(RNG);
	scanf("%d%d", &N, &K);
	for (int i = 0; i < N; i++) {
		scanf("%d", &A[i]);
		order.push_back(i);
		ST[i] = A[i];
		BST[i] = -1;
	}
	for (int i = 0; i < N; i++) {
		scanf("%d", &B[i]);
	}
	for (int i = 0; i < N; i++) {
		scanf("%d", &C[i]);
		sum += C[i];
	}
	#endif
	for (int i = 0; i < 32 * 1024; i++) QUEUE[i] = MAXT;
	int it = 0;
	std::sort(order.begin(), order.end(), [&](int a, int b) {
		return C[a] * B[b] > C[b] * B[a];
	});
	long long best = smartScore();
	for (int i = 0; i < N; i++) BST[i] = ST[i];
	end_time -= get_time() - start_time;

	if (K == 1) {
		for (int i = 0; i < N; i++) {
			if (A[i] == MAXA && rand()%RNG == 0) BST[i] = -1;
		}
	} 
	else {
		while (get_time() < end_time) {
			std::sort(order.begin(), order.end(), [&](int a, int b) {
				if (ST[a] + B[a] <= A[b]) return true;
				if (ST[b] + B[b] <= A[a]) return false;
				return B[a] * C[b] < B[b] * C[a];
			});
			long long sc = smartScore();
			if (sc < best) {
				best = sc;
				for (int i = 0; i < N; i++) BST[i] = ST[i];
			}
		}
	}
	while (get_time() < start_time + 0.95) {
		FixAssignment();
	}
	// fprintf(stderr, "Final: %lld\n", best);
	// fprintf(stderr, "Final: %lld vs %lld\n", score(), smartScore());
	#ifndef LOCAL
	for (int i = 0; i < N; i++) printf("%llu ", BST[i]);
	#endif
	return 0;
}
/* Test Case :  5 2
				5 10 15 20 25
				11 11 5 2 4
				124 10 14 135 42
   Ans : 5 10 16 21 25
*/
