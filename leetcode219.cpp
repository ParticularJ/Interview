/*
set ���÷���
ֻ�洢��ͬ��Ԫ��
*/

class Solution {
public:
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		int size = nums.size();
		set<int> record;
		// ά��һ��k��С�Ļ�������
		for (int i = 0; i < nums.size(); i++) {
			if (record.find(nums[i]) != record.end())
				return true;
			record.insert(nums[i]);

			// ά�ֳ���Ϊk
			if (record.size() == k + 1)
				record.erase(nums[i - k]);
		}
		
		return false;
	}
};