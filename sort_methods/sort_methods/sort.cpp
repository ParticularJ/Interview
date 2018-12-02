#include<iostream>
#include<vector>
#include<ctime>
#include<cassert>
#include<ctime>
#include<algorithm>
#include<functional>


using namespace std;

class Sort_methods {
//快排

public:

	int __quick_sort(vector<int>&nums, int l, int r) {
		int k = rand() % (r - l + 1) + l;
		swap(nums[l], nums[k]);
		int base = nums[l];
		int i = l + 1, j = r;
		while (1) {
			while (i<=r && nums[i] > base) {
				i++;
			}
			while (j>=l+1 && nums[j] < base) {
				j--;
			}
			
			if (i > j)
				break;

			swap(nums[i], nums[j]);
			i++;
			j--;
		}
		swap(nums[j], nums[l]);
		return j;
	}

	void _insert_sort(vector<int>& nums, int l, int r) {
		for (int i = l+1; i <= r; i++) {
			int j;
			int temp = nums[i];
			for (j = i; j > l; j--) {
				if (nums[j-1] < temp)
					nums[j] = nums[j - 1];
				else
					break;
			}
			nums[j] = temp;
		}
		return;
	}

	void _quick_sort(vector<int>& nums, int l, int r) {
		if (r - l <= 3) {
			_insert_sort(nums, l, r);
			return;
		}
		int p = __quick_sort(nums, l, r);
		_quick_sort(nums, l, p - 1);
		_quick_sort(nums, p + 1, r);


	}
	vector<int> quick_sort(vector<int>& nums) {
		srand(time(NULL));
		int size = nums.size();
		_quick_sort(nums, 0, size - 1);
		return nums;
	}





// 归并排序
public:
	void merge(vector<int>& nums, int l, int mid, int r) {
		vector<int> temp(r - l + 1, 0);
		for (int i = l; i <= r; i++) {
			temp[i - l] = nums[i];
		}
		int i = l, j = mid + 1;
		for (int k = l; k <= r; k++) {
			if (i > mid) {
				nums[k] = temp[j - l];
				j++;
			}
			else if(j > r){
				nums[k] = temp[i - l];
				i++;
			}else if (temp[i - l] < temp[j - l]) {
				nums[k] = temp[j - l];
				j++;
			}
			else {
				nums[k] = temp[i - l];
				i++;
			}
		}
	}

	void _insert(vector<int>& nums, int l, int r) {
		for (int i = l+1; i <= r; i++) {
			int temp = nums[i];
			int j;
			for (j = i; j > l; j--) {
				if (nums[j - 1] < temp)
					nums[j] = nums[j - 1];
				else
					break;
			}
			nums[j] = temp;
		}
		return;
	}

	void dfs(vector<int>& nums, int l, int r) {
		if (r - l <= 3) {
			_insert(nums, l, r);
			return;
		}
		int mid = l + (r - l) / 2;
		dfs(nums, l, mid);
		dfs(nums, mid + 1, r);
		if(nums[mid]<nums[mid+1])
			merge(nums, l, mid, r);
	}

	vector<int> merge_sort(vector<int> & nums) {
		int size = nums.size();
		dfs(nums, 0, size - 1);
		return nums;
	}



//冒泡排序
public:
	vector<int> bubble(vector<int>& nums) {
		int size = nums.size();
		for (int i = 0; i < size; i++) {
			for (int j = i; j < size; j++) {
				if (nums[i] < nums[j])
					swap(nums[i], nums[j]);
			}
		}
		return nums;
	}


//选择排序
public:
	vector<int> select(vector<int>& nums) {
		int size = nums.size();
		for (int i = 0; i < size; i++) {
			int min = i;
			for (int j = i+1; j < size; j++) {
				if (nums[j] > nums[min])
					min = j;
			}
			swap(nums[i], nums[min]);
		}
		return nums;
	}


// 插入排序
public:
	vector<int> insert_sort(vector<int>& nums) {
		int size = nums.size();
		for (int i = 1; i < size; i++) {
			int temp = nums[i];
			int j;
			for (j = i; j > 0; j--) {
				if (nums[j - 1] < temp)
					nums[j] = nums[j - 1];
				else
					break;
			}
			nums[j] = temp;
		}
		return nums;
	}


// 希尔排序
public:
	vector<int> shell_sort(vector<int> & nums) {
		int size = nums.size();
		int h = 1;
		// 相对来说比较好的增量
		while (h < size / 3)
			h = h * 3 + 1;
		while ( h > 0 ) {
			for (int i = h; i < size; i++) {
				int temp = nums[i];
				int j;
				for (j = i; j >= h; j -= h) {
					if (nums[j - h] < temp)
						nums[j] = nums[j - h];
					else
						break;
				}
				nums[j] = temp;
			}
			h /= 3;
		}
		return nums;
	}
};

bool cmp(int a, int b) {
	return a > b;
}

//int main() {
//	Sort_methods b, s, i, sh, m, q;
//	vector<int> arr1 = { 3, 5, 6, 4, 2, 9 };
//	vector<int> arr2 = { 3, 5, 6, 4, 2, 9 };
//	vector<int> arr3 = { 3, 5, 6, 4, 2, 9 };
//	vector<int> arr4 = { 3, 5, 6, 4, 2, 9 };
//	vector<int> arr5 = { 3, 5, 6, 4, 2, 9 };
//	vector<int> arr6 = { 3, 5, 6, 4, 2, 9, 1, 3, 4 ,5,6,4,2 };
//	vector<int> arr7 = { 3, 5, 6, 4, 2, 9, 1, 3, 4 ,5,6,4,2 };
//
//	make_heap(arr7.begin(), arr7.end(), greater<int>());
//	sort_heap(arr7.begin(), arr7.end(), greater<int>());
//	for (vector<int>::iterator iter = arr7.begin(); iter != arr7.end(); iter++) {
//		cout << *(iter); 
//	}
//	cout << endl;
//
//	vector<int> br, sr, ir, shr, mr, qr;
//	br = b.bubble(arr1);
//	for (auto i : br)
//		cout << i;
//	cout << endl;
//
//	sr = s.select(arr2);
//	for (auto i : sr)
//		cout << i;
//	cout << endl;
//
//	ir = i.insert_sort(arr3);
//	for (auto i : ir)
//		cout << i;
//	cout << endl;
//
//	shr = sh.shell_sort(arr4);
//	for (auto i : shr)
//		cout << i;
//	cout << endl;
//
//	mr = m.merge_sort(arr5);
//	for (auto i : mr)
//		cout << i;
//	cout << endl;
//
//	qr = q.quick_sort(arr6);
//	for (auto i : qr)
//		cout << i;
//	cout << endl;
//
//	return 0;
//}