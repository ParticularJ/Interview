/*
	dfs 递归
*/

class Solution {
public:
	string S;
	string dfs(int& index) {
		string res = "";
		while (1) {
			// 递归出口条件
			if (index == ']') {
				index++;
				return res;
			}
			else if (S[index] >= '0'&&S[index] <= '9') {
				int n = 0;
				while (S[index] >= '0'&&S[index] <= '9') {
					n = n * 10 + S[index++] - '0';
				}
				//跳过"["
				index++;
				string temp = dfs(index);
				//拼接字母
				for (; n--;) {
					res += temp;
				}
			}
			else {
				res += S[index++];
			}
		}
	}

	string decodeString(string s) {
		S = s;
		S += ']';
		int index = 0;
		return dfs(index);
	}
};