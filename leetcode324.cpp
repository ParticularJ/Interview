/*
	¿ìÅÅ
*/

class Solution {
public:

	int mysort(vector<int>& nums, int l, int r, int K) {
		int L = l, R = r;
		int base = nums[l + (rand() % (r - l + 1))];
		for (; L <= R;) {
			for (; L <= R&&nums[R] > base)R--;
			for (; L <= R&&nums[L] < base)L++;
			if (L <= R) {
				swap(nums[L++], nums[R--]);
			}
		}

		if (R - l + 1 >= K)return mysort(nums, l, R, K);
		else if (L - 1 - l + 1 >= K)return base;
		else return mysort(nums, L, r, K - (L - 1 - l + 1));
	}

	void wiggleSort(vector<int>& nums) {
		int size = nums.size();
		if (size == 0)return;
		sort(nums.begin(), nums.end());
		int mid = (size + 1) / 2;
		int mid_num = nums[mid];
		for (int i = mid, j = 1; i<size; i = i + 1, j = j + 2) {
			nums.insert(nums.begin() + j, nums[i]);
			nums.erase(nums.begin() + i + 1);
		}

		for (int i = 0, j = 0; i < size; i += 2) {
			if (nums[i] == mid_num) {
				swap(nums[i], nums[j]);
				j += 2;
			}
		}

		for (int i = 1, j = size - 1 - ((size - 1) % 2 == 0); i < mid; i += 2) {
			cout << nums[i] << " " << nums[mid] << endl;
			if (nums[i] == mid_num) {
				swap(nums[i], nums[j]);
				j = j - 2;
			}
		}
	}
};


