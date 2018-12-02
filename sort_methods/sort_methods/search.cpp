#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Search {
//µü´ú
public:
	int binary_search(vector<int>& nums, int target) {
		sort(nums.begin(), nums.end());
		int size = nums.size();
		int l = 0, r = size - 1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (nums[mid] == target)
				return mid;
			if (nums[mid] > target)
				r = mid - 1;
			else
				l = mid + 1;
		}
		return -1;
	}

//µİ¹é
public:
	int binary_search1(vector<int>& nums, int l, int r, int target) {
		
		if (l > r)
			return -1;
		int mid = (l + r) >> 1;
		if (nums[mid] == target)
			return mid;
		if (nums[mid] > target)
			return binary_search1(nums, l, mid - 1, target);
		else
			return binary_search1(nums, mid + 1, r, target);
	}
};



int main() {
	Search bn1;
	vector<int> arr1{ 3, 2, 23, 4, 56, 2, 1 };
	sort(arr1.begin(), arr1.end());
	int target = 23;
	cout<<bn1.binary_search(arr1, target);
	cout << bn1.binary_search1(arr1, 0, arr1.size() - 1, 3);


}