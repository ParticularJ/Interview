#include<iostream>
#include<vector>

using namespace std;

/*
˼·��ά��һ�������¼ǰ׺��
     ά��һ�������¼ÿ���ַ���һ�γ��ֵ�λ��
	 ������ִ���С��K,��ô���Ǿͽض�����ַ��� 
*/

class Solution {
public:
	vector<int> pre[26];
	vector<int> next[26];
	int K;
	int res = 0;
	int dfs(string &s, int l, int r) {
		for (int i = 0; i < 26; i++) {
			// l-1 ��ԭ��������Ҫ��ȥ��һ����ĸ���ֵ�λ��
			// ���� a,a,a,b,b   b���ֵ�ǰ׺��-����δ���ֵ� ͳ��a���ֶ��ٴΣ�pre[0][4]-0 = 3
			 // pre[0][4]-pre[0][0]=2Ҫ��0��ʼ����
			int sum = pre[i][r] - (l == 0 ? 0 : pre[i][l - 1]);
			if (sum == 0)continue; 
			if (sum < K) {
				int pre = l;
				for (int p = next[i][l]; p <= r&&p != -1; p = next[i][p + 1]) {
					res = max(res, dfs(s, pre, p-1));
					pre = p + 1;
				}
				res = max(res, dfs(s, pre, r));
				return res;
			}
		}
		return r - l + 1;
	}


	int longestSubstring(string s, int k) {
		K = k;
		int size = s.size();
		for (int i = 0; i < 26; i++) {
			pre[i] = vector<int>(size, 0);
			next[i] = vector<int>(size+1, -1);
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < 26; j++) {
				pre[j][i] = i == 0 ? 0 : pre[j][i - 1] + (j == (s[i] - 'a'));
			}
		}
		for (int i = size - 1; i >= 0; i--) {
			for (int j = 0; j < 26; j++) {
				next[j][i] = s[i] - 'a' == j ? i : next[j][i + 1];
			}
		}

		return dfs(s, 0, size - 1);
	}
};