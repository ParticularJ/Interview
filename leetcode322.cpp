#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
// 完全背包问题，并且个数不限，我们只要能填满即可
// f[j]+1 判断背包现在的情况，将当前的重量放入背包，比较价值
class Solution{
public:
	int coinChange(vector<int>& coins, int amount) {
		vector<int> f(amount + 1, -1);
		f[0] = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j + coins[i] <= amount; j++) {
				if (f[j] != -1) {
					f[j + coins[i]] = min(f[j + coins[i]] == -1 ? (1 << 30) : f[j + coins[i]], f[j] + 1);
				}
			}
		}
		return f[amount];
	}
};
