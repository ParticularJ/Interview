/*
	dfs �ݹ�
*/

class Solution {
public:
	string S;
	string dfs(int& index) {
		string res = "";
		while (1) {
			// �ݹ��������
			if (index == ']') {
				index++;
				return res;
			}
			else if (S[index] >= '0'&&S[index] <= '9') {
				int n = 0;
				while (S[index] >= '0'&&S[index] <= '9') {
					n = n * 10 + S[index++] - '0';
				}
				//����"["
				index++;
				string temp = dfs(index);
				//ƴ����ĸ
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