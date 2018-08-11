/*
当背包较小时使用动态规划
当比较大的时候使用dfs枚举。

*/


#include<iostream>
#include<vector>

using namespace std;

long long n, w, v;

vector<long long> V(33, 0);
long long cnt = 0;

void dfs(long long index, long long weight) {
	if (index == n) {
		cnt += 1;
		return;
	}
	if (weight + V[index] <= w) {
		dfs(index + 1, weight + V[index]);
	}
	dfs(index + 1, weight);
}


int main() {
	cin >> n >> w;
	for (long long i = 0; i < n; i++) {
		cin >> v;
		V[i] = v;
	}
	dfs(0ll, 0ll);
	cout << cnt;
	return 0;
}