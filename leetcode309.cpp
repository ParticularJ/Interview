class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int f[3] = { 0, 1 << 31, 1 << 31 };
		//0:nothing, 1: buy, 2:cooldown
		for (auto i : prices) {
			int g[3];
			// cooldown ，什么都不干
			g[0] = max(f[0], f[2]);
			// buy完要sell
			g[1] = max(f[0] - i, f[1]);
			// cooldown 完要buy
			g[2] = f[1] + i;
			f[0] = g[0];
			f[1] = g[1];
			f[2] = g[2];
		}
		return max(max(f[0], f[1]), f[2]);
	}
};

/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times) with the following restrictions:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
Example:

Input: [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]
*/

class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int size = prices.size();
		if (size < 2)
			return 0;
		// 拿到手里的是多少
		// 第一次要买，那么开始为-的
		vector<int> hold(size, INT_MIN);
		// 得到手的现金是多少
		vector<int> cash(size, 0);
		// 初始化hold, 第一天买
		hold[0] = -prices[0];
		// 第二天买
		hold[1] = max(hold[0], -prices[1]);

		// 第一天买，第二天卖
		cash[1] = max(cash[0], hold[0] + prices[1]);

		for (int i = 2; i < size; i++) {
			// 现在的现金就是，昨天到手的现金和昨天买，今天卖掉的价格
			cash[i] = max(cash[i - 1], hold[i - 1] + prices[i]);
			// 昨天买的价格，或者上一次到手之后的价格，经过cooldown再买的价格
			hold[i] = max(hold[i - 1], cash[i-2]-prices[i]);
		}
		return cash.back();

	}
};