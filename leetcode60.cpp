class Solution {
public:
	string getPermutation(int n, int k) {
		string res="";
		if (n == 0)return res;
		vector<int> nums(n, 0);
		for (int i = 1; i <= n; i++) {
			nums[i] = i;
		}
		
		int count = 1;
		while (1) {
			int ascend = n - 1;
			while (ascend != 0 && nums[ascend - 1] > nums[ascend])
				ascend--;

			int mini = nums[ascend - 1];
			for (int j = n - 1; j >= ascend; j--) {
				if (nums[j] > mini) {
					swap(nums[j], nums[ascend - 1]);
					break;
				}
			}

			for (int i = ascend, j = size - 1; i <= j; i++, j--) {
				swap(nums[i], nums[j]);
			}
			count++;
			if (count == k)return to_string(nums);
		}


	}
};