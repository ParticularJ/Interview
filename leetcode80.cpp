/*
维护两个位置，
*/

class Solution {
public:
	int get_next(vector<int>& nums, int index) {
		for (int i = index; i < nums.size(); i++) {
			if (nums[i] != nums[index])
				return i;
		}
		return nums.size();
	}

	int removeDuplicates(vector<int>& nums) {
		int size = nums.size();
		if (size == 0)return 0;
		int k = 0;
		for (int i = 0; i < size;) {
			//返回第一个不相等的位置
			int index = get_next(nums, i);
			// 长度，最多只能存储两个
			int len = min(2, index - i);
			for (int j = 0; j < len; j++) {
				nums[k+j] = nums[i];
			}
			 // i就到下一次不重复 的数字
			i = index;
			// 维护新的数组，指向下一个位置
			k = k + len;
		}
		return k;
	}
};