/*
 运用栈的思想
 
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

			// 先判断nums[i] > 栈顶元素，得知现在nums[i]最大
			// 即为 a[j], 之后将min赋为栈顶元素， 即为 a[k] , 
			// 再判断第一个是否小于min，即为a[i] < a[k]
			while (!st.empty() && nums[i] > st.top()) {
				min = st.top();
				st.pop();
			}

			st.push(nums[i]);
		}
		return false;
	}
};