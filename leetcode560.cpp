/*
ǰ׺�͵�˼��, ά��һ��ǰ׺��
�������һ��ǰ׺�͵���K,��ô(k+ǰ׺��)Ҳ������ô������
��һ�Ρ�
*/


class Solution {
public:
	int subarraySum(vector<int>& nums, int k) {
		int sum = 0;
		unordered_map<int, int> cnt;
		cnt[0] = 1;
		int prefix = 0;
		int res = 0;
		for (auto i : nums) {
			prefix += i;
			res += cnt[prefix - k];
			cnt[prefix] += 1;
		}
		return res;
	}
};