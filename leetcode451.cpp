
class Solution {


public:
	static bool  cmp(const pair<char, int>& a, const pair<char, int>& b) {
		return a.second >= b.second;
	}
	string frequencySort(string s) {
		int size = s.size();
		if (size == 0)return "";
		map<char, int> record;
		for (auto i : s)
			record[i]++;
		vector<pair<char, int>> temp(record.begin(), record.end());
		sort(temp.begin(), temp.end(), cmp);
		string res;
		for (int i = 0; i<temp.size(); i++) {
			for (int j = 0; j<temp[i].second; j++)
				res += temp[i].first;

		}
		return res;
	}
};