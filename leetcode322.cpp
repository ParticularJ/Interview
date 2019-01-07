#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
// ��ȫ�������⣬���Ҹ������ޣ�����ֻҪ����������
// f[j]+1 �жϱ������ڵ����������ǰ���������뱳�����Ƚϼ�ֵ
// 0��1�����ǴӴ���Сȡ����ȫ�����Ǵ�С����
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
		// ��¼Ҫ���ٸ�coins����������������amount��
		vector<int> memo(amount + 1, amount+1);
		// ��һ��Ϊ0
		memo[0] = 0;
		for (int i = 1; i < amount + 1; i++) {
			for (int coin : coins) {
				if (i >= coin)


					// ����ܷ��£� �б�ǰ�������ͷ��µ�ǰ���������ĸ�С��
					memo[i] = min(memo[i], 1 + memo[i - coin]);
			}
		}

		return memo[amount] == amount + 1 ? -1 : memo[amount];

	}
};