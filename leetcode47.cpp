/*
思想，排序之后，不停交换，直到满足条件
*/

class Solution {
public:
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		vector<vector<int> > res;
		int size = nums.size();
		sort(nums.begin(), nums.end());
		while (1) {
			res.push_back(nums);
			if (size == 0)return res;
			// 跳出循环条件，数组从大到小已经排列好
			int ascend = size - 1;
			while (ascend != 0 && nums[ascend - 1] >= nums[ascend])
				ascend--;
			if (ascend == 0)
				break;

			//交换最后两位
			int mini = nums[ascend-1];
			for (int i = size - 1; i >= ascend; i--) {
				if (nums[i] > mini) {
					swap(nums[i], nums[ascend-1]);
					break;
				}
			}
			// 从ascend往后，交换顺序,确保不会提前结束
			// 因为，通过上一步，假如例子是123，一定会先得到321，这样
			// 就会缺少312， 所以要先将ascend后面进行交换。
			for (int i = ascend, j = size - 1; i <= j; i++, j--) {
				swap(nums[i], nums[j]);
			}
		}
		return res;
	}
};