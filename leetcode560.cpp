/*
前缀和的思想, 维护一个前缀和
如果满足一次前缀和等于K,那么(k+前缀和)也存在那么就满足
下一次。
*/


class Solution {
public:
	int subarraySum(vector<int>& nums, int k) {
		int sum = 0;
		unordered_map<int, int> cnt;
		cnt[0] = 1;
		int prefix = 0;
		int res = 0;
		for (auto i : nums) {
			prefix += i;
			res += cnt[prefix - k];
			cnt[prefix] += 1;
		}
		return res;
	}
};