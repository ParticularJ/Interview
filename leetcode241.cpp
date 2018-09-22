/*
递归求解
*/

class Solution {
public:
	vector<int> diffWaysToCompute(string input) {
		vector<int> res;
		int size = input.size();
		for (int i = 0; i < size; i++) {
			char a = input[i];
			if (a == '+' || a == '-' || a == '*') {
				vector<int> b = diffWaysToCompute(input.substr(0, i));
				vector<int> c = diffWaysToCompute(input.substr(i + 1));
				for (auto i : b) {
					for (auto j : c) {
						if (a == '+')
							res.push_back(i + j);
						else if (a == '-')
							res.push_back(i - j);
						else if (a == '*')
							res.push_back(i*j);
					}
				}
			}
		}
		// 如果只是单纯数字，添加进res
		if (res.size() == 0) {
			cout << stoi(input) << " ";
			res.push_back(stoi(input));
		}
		return res;
	}
};