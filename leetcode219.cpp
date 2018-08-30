/*
set ���÷���
ֻ�洢��ͬ��Ԫ��
*/

class Solution {
public:
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		int size = nums.size();
		set<int> s;
		if (size == 0)return false;
		int K = min(size-1, k);
		for (int i = 0; i <= K; i++) {
			if (s.find(nums[i])!=s.end())
				return true;
			s.insert(nums[i]);
		}
		for (int i = k; i < size; i++) {
			// ��̬ά��k���ȵ�set
			s.erase(nums[i - k -1]);
			// �ҵ���
			if (s.find(nums[i])!=s.end())
				return true;
			s.insert(nums[i]);
		}
		return false;
	}
};