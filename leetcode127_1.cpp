class Solution {
public:
	bool similar(string & a, string & b) {
		int cnt = 0;
		for (int i = 0; i < a.size(); i++) {
			if (a[i] != b[i])cnt++;
		}
		if (cnt == 1)return true;
		else
			return false;
	}

	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		int end = find(wordList.begin(), wordList.end(), endWord) - wordList.begin();
		if (end == wordList.size())
			return 0;
		int start = find(wordList.begin(), wordList.end(), beginWord) - wordList.begin();
		if (start == wordList.size())
			wordList.push_back(beginWord);
		int size = wordList.size();

		vector<vector<bool> > G(size, vector<int>(size, false));
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < i; j++) {
				if (similar(wordList[i], wordList[j])) {
					g[i][j] = g[j][i] = true;
				}
			}
		}

		queue<int> q;
		q.push(start);
		vector<int> step(size, 0);
		step[start] = 1;
		while (q.size()) {
			int top = q.front();
			q.pop();

			for (int i = 0; i < size; i++) {
				if (step[i] == 0 && g[top][i]) {
					if (i == end)
						return step[top] + 1;
					step[i] = step[top] + 1;
					q.push(i);
				}
			}
		}
		return 0;

	}
};