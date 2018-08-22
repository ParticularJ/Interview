class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int f[3] = { 0, 1 << 31, 1 << 31 };
		//0:nothing, 1: buy, 2:cooldown
		for (auto i : prices) {
			int g[3];
			// cooldown ��ʲô������
			g[0] = max(f[0], f[2]);
			// buy��Ҫsell
			g[1] = max(f[0] - i, f[1]);
			// cooldown ��Ҫbuy
			g[2] = f[1] + i;
			f[0] = g[0];
			f[1] = g[1];
			f[2] = g[2];
		}
		return max(max(f[0], f[1]), f[2]);
	}
};