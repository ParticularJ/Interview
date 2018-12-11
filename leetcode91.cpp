/*
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given a non-empty string containing only digits, determine the total number of ways to decode it.

Example 1:

Input: "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).
Example 2:

Input: "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
*/

class Solution {
private:
	const int isValidNum(string &s, int i) {
		int tempa = 10 * (s[i] - '0');
		int tempb = s[i + 1] - '0';
		return tempa + tempb;
	}

public:
	int numDecodings(string s) {
		assert(s.size() > 0);
		// 记录数组 ， 分别考虑两种情况， 一位一位取和两位两位取
		int size = s.size();
		vector<int> memo(size + 1, 0);
		//只有一个字母时为1
		memo[0] = 1;
		for (int i = 0; i < size; i++) {
			//一位一位取
			if (s[i] != '0')
				memo[i + 1] = memo[i + 1] + memo[i];
			//两位两位取，保证前一位不为0
			if (s[i] != '0'&&i + 1 < size && (isValidNum(s, i) <= 26)) {
				memo[i + 2] = memo[i + 2] + memo[i];
			}
		}
		return memo[size];
	}
};