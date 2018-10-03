/*
 ����ջ��˼��
 
*/

class Solution {
public:
	bool find132pattern(vector<int>& nums) {
		stack<int> st;
		int min = INT_MIN;
		int size = nums.size();
		for (int i = size - 1; i >= 0; i--) {
			// i ,j , k  aj > ak> ai
			if (nums[i] < min)
				return true;

			// ���ж�nums[i] > ջ��Ԫ�أ���֪����nums[i]���
			// ��Ϊ a[j], ֮��min��Ϊջ��Ԫ�أ� ��Ϊ a[k] , 
			// ���жϵ�һ���Ƿ�С��min����Ϊa[i] < a[k]
			while (!st.empty() && nums[i] > st.top()) {
				min = st.top();
				st.pop();
			}

			st.push(nums[i]);
		}
		return false;
	}
};