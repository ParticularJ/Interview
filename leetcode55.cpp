
class Solution {
public:
	bool canJump(vector<int>& nums) {
		int size = nums.size();
		if (size == 0)return true;
		vector<int> m(size, 0);
		for (int i = 0; i < size; i++) {
			m[i] = i + nums[i];
		}
		int longest = 0;
		for (int i = 0; i<=longest&&longest < size - 1;i++) {
			longest = max(longest, m[i]);
		}
		return longest >= size - 1;
	}
};