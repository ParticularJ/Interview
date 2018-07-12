#include<iostream>
#include<vector>

using namespace std;

/*
思路：维护一个数组记录前缀和
     维护一个数组记录每个字符第一次出现的位置
	 如果出现次数小于K,那么我们就截断这个字符串 
*/

class Solution {
public:
	vector<int> pre[26];
	vector<int> next[26];
	int K;
	int res = 0;
	int dfs(string &s, int l, int r) {
		for (int i = 0; i < 26; i++) {
			// l-1 的原因是我们要减去上一个字母出现的位置
			// 比如 a,a,a,b,b   b出现的前缀和-所有未出现的 统计a出现多少次，pre[0][4]-0 = 3
			 // pre[0][4]-pre[0][0]=2要从0开始减。
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