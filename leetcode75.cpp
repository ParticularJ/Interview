class Solution {
public:
	void sortColors(vector<int>& nums) {
		//使用三路快排
		int zero = 0, int two = nums.size() - 1;
		for (int i = 0; i <= two; ) {
			if (nums[i] == 1)
				i++;
			else if (nums[i] < 1) {
				swap(nums[zero++], nums[i++]);
			}
			else
				swap(nums[two--], nums[i]);
		}

	}
};