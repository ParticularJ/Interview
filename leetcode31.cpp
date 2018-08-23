class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		int size = nums.size();
		if (size == 0)return;

		//如果已经是逆序，直接交换
		int i = size - 1;
		for (; i >= 0; i--) {
			if (nums[i] <= nums[i - 1])
				continue;
			break;
		}

		if (i == 0) {
			for (int j = size - 1, k = 0; k<j && j >= 0; j--, k++) {
				swap(nums[j], nums[k]);
			}
			return;
		}

		int larger = nums[i - 1];
		int j = size - 1;
		for (; j >= i; j--) {
			if (larger < nums[j]) {
				swap(nums[i - 1], nums[j]);
				break;
			}
		}
		cout << i;
		sort(nums.begin() + i, nums.end());
	}
};