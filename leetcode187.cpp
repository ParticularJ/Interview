/*
就是一个遍历的过程
*/

class Solution {
public:
	int calc(string &s) {
		if (s == 'A')return 0;
		if (s == 'C')return 1;
		if (s == 'G')return 2;
		if (s == 'T')return 3;
	}


	vector<string> findRepeatedDnaSequences(string s) {
		vector<string> res;
		int size = s.size();
		map<int, int> mymap;


		// 存储有无出现过
		vector<int> appear((1 << 20) + 1, 0);
		for (int l = 0, r = 9; r < size; l++, r++) {
			int value = 0;
			for (int i = l; i <= r; i++) {
				value = (value<<2) + calc(s[i]))
			}
			mymap[value]++;
			if (mymap[value] > 1 && appear[value] == 0) {
				res.push_back(s.substr(l, 10));
				appear[value] = 1;
			}
		}
		return res;
	}
};