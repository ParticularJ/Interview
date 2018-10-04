/*
记忆化搜索， 动态规划可以分为两种实现方式，一种为记忆化搜索，另一种为递推的方式

*/


class Solution {
public:
	// 2 存能赢， 1存输
	vector<int> flag;

	int dfs(int status, int maxi int sum, int dt) {
		if (flag[status] != 0)
			return flag[status] - 1;
		if (sum >= dt)return 0;

		for (int i = 0; i < maxi; i++) {
			// 如果还没有被取
			if ((status & (1 << i)) == 0) {
				// 自己会不会赢
				int temp = dfs(status | (1 << i), maxi, sum + i + 1, dt)^1;
				// 先手 找到了赢的路
				if (temp == 1) {
					flag[status] = 2;
					return 1;
				}
			}
		}
		flag[status] = 1;
		return 0;
	}

	bool canIWin(int mc, int dt) {
		if ((mc + 1)*mc / 2 < dt)return false;
		if (dt == 0)return true;
		// 所有的状态
		flag = vector<int>(1 << mc);
		return dfs(0, mc, 0, dt);
	}
};