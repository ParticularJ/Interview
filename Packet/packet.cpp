#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
private:
	int findValue(vector<int>& w, vector<int>& v, int index, int C) {
		if (index < 0 || C <= 0) {
			return 0;
		}

		int res = findValue(w, v, index - 1, C);

		if (C >= w[index]) {
			res = max(res, v[index] + findValue(w, v, index - 1, C - w[index]));
		}
		return res;
	}

public:
	int packet(vector<int>& w, vector<int>& v, int C) {
		int size = w.size();
		// ����w, v, ��������Ԫ�أ��Լ�����
		return findValue(w, v, size - 1, C);
	}
};


int main()
{

	// weight ÿ������������� ��ֵ���Լ��������ݻ�
	vector<int> w, v;
	w = { 1, 2, 3 };
	v = { 6, 10, 12 };
	int C = 5;
	Solution pack;
	int res = pack.packet(w, v, C);
	cout << res;
	return 0;
}
