class Solution {
public:
	vector<vector<string> > res;
	int size;
	string S;
	void dfs(int begin, vector<string> temp) {
		if (begin == size) {
			res.push_back(temp);
			return;
		}
		for (int i = begin; i < size; i++) {
			if (isPalindrome(begin-1, i+1)) {
				temp.push_back(S.substr(begin, i - begin + 1));
				dfs(i + 1, temp);
				res.pop_back();
			}
		}
	}
	bool isPalindrome(int begin, int end) {
		while (begin < end && S[++begin] == S[--end]);
		return end <= begin;
	}
	vector<vector<string> > partition(string s) {
		S = s;
		size = s.size();
		if (size == 0)return res;
		dfs(0, vector<string>());
		return res;
	}
};