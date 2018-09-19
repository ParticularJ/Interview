/*
ʹ�û������ڣ����ǣ�Ҫ��֤�ҵ���ֵ���ڵ���v-t, С�ڵ��� v+t
*/

class Solution {
public:
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		int size = nums.size();
		set<long long> record;
		for (int i = 0; i < size; i++) {

			// �ж����ҵ�Ԫ�ص�ֵ��set���Ƿ����ҵ���ֵ���������� ���ڵ���nums[i] -t
			// С�ڵ���nums[i] + t
			if (record.lower_bound((long long)nums[i] - (long long)t) != record.end() &&
				*(record.lower_bound((long long)nums[i] - (long long)t)) <= (long long)nums[i] + (long long)t)
				return true;
			record.insert(nums[i]);
			if (record.size() == k + 1)
				record.erase(nums[i - k]);
		}
		return false;

	}
};