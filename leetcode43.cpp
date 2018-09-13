/*
参考leetcode43，模拟乘法运算
*/

class Solution {
public:
	string multiply(string num1, string num2) {
		string res1 = "";
		int size1 = num1.size();
		int size2 = num2.size();
		if (size1 == 0 || size2 == 0)return res1;
		vector<int> res(size1 + size2, 0);
		for (int i = size1 - 1; i >= 0; i--) {
			for (int j = size2 - 1; j >= 0; j--) {
				int temp = (num1[i] - '0')*(num2[j] - '0');
				// cout<<temp<<" "<<endl;
				int sum = temp + res[i + j + 1];
				res[i + j + 1] = sum % 10;
				// cout<<i+j+1<<" "<<res[i+j+1]<<" "<<endl;
				res[j + i] += sum / 10;
				//cout<<i+j<<" "<<res[i+j]<<" "<<endl;
			}
		}
		for (auto i : res)
			cout << i << endl;
		int i = 0;
		while (res[i] == 0 && i<res.size())i++;
		//  cout<<i;
		if (i == res.size())return "0";
		for (; i < res.size(); i++) {

			res1 += to_string(res[i]);
		}
		return res1;
	}
};