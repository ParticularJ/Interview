#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
private:
	vector<vector<int>> memo;
	int findValue(vector<int>& w, vector<int>& v, int index, int C) {
		// 递归终止条件
		// index 可以取到0，
		if (index < 0 || C <= 0) {
			return 0;
		}
		//判断是否计算过
		if (memo[index][C] != -1)
			return memo[index][C];


		// 不管当前的结果
		int res = findValue(w, v, index - 1, C);
		// 判断是否能放下
		if (C >= w[index]) {
			// 不管当前和放下当前的结果大小
			res = max(res, v[index] + findValue(w, v, index - 1, C - w[index]));
		}
		memo[index][C] = res;

		return res;
	}

public:
	int packet(vector<int>& w, vector<int>& v, int C) {
		int size = w.size();
		memo = vector<vector<int>>(size, vector<int>(C + 1, -1));
		for (int i = 0; i <= C; i++)
			memo[0][i] = i > w[i] ? v[0] : 0;
		// 传入w, v, 遍历到的元素，以及容量
		return findValue(w, v, size - 1, C);
	}
};


int main()
{

	// weight 每个物体的重量， 价值，以及背包的容积
	vector<int> w, v;
	w = { 1, 2, 3 };
	v = { 6, 10, 12 };
	int C = 5;
	Solution pack;
	int res = pack.packet(w, v, C);
	cout << res;
	return 0;
}
