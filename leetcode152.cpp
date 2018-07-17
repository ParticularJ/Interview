/*
   ¶¯Ì¬¹æ»®
*/
class Solution {
public:
	int maxProduct(vector<int>& nums) {
		int size = nums.size();
		if (size == 0)return 0;
		long long res = INT_MIN;
		for (int i = 0; i < size; i++) {
			res = max(res, (long long)nums[i]);
		}
		vector<long long> maxi(size, 0);
		vector<long long> mini(size, 0);
		maxi[0] = max(0, nums[0]);
		mini[0] = min(0, nums[0]);
		for (int i = 1; i < size; i++) {
			long long a = max(max(max(0ll, (long long)nums[i]), maxi[i - 1] * nums[i]), mini[i - 1] * nums[i]);
			maxi[i] = a;
			long long b = min(min(min(0ll, (long long)nums[i]), maxi[i - 1] * nums[i]), mini[i - 1] * nums[i]);
			mini[i] = b;
			if (maxi[i] > res)res = maxi[i];
		}
		return res;
	}
};