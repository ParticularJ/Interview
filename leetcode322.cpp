#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
// 完全背包问题，并且个数不限，我们只要能填满即可
// f[j]+1 判断背包现在的情况，将当前的重量放入背包，比较价值
// 0，1背包是从大往小取，完全背包是从小往大
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


/*
You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:

Input: coins = [1, 2, 5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1
Example 2:

Input: coins = [2], amount = 3
Output: -1

*/


class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		int size = coins.size();
		// 记录要多少个coins才能填满，最多就是amount个
		vector<int> memo(amount + 1, amount+1);
		// 第一个为0
		memo[0] = 0;
		for (int i = 1; i < amount + 1; i++) {
			for (int coin : coins) {
				if (i >= coin)


					// 如果能放下， 判别当前的重量和放下当前的重量看哪个小。
					memo[i] = min(memo[i], 1 + memo[i - coin]);
			}
		}

		return memo[amount] == amount + 1 ? -1 : memo[amount];

	}
};