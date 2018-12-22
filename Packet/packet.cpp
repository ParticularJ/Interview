#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
private:
	vector<vector<int>> memo;
	int findValue(vector<int>& w, vector<int>& v, int index, int C) {
		// �ݹ���ֹ����
		// index ����ȡ��0��
		if (index < 0 || C <= 0) {
			return 0;
		}
		//�ж��Ƿ�����
		if (memo[index][C] != -1)
			return memo[index][C];


		// ���ܵ�ǰ�Ľ��
		int res = findValue(w, v, index - 1, C);
		// �ж��Ƿ��ܷ���
		if (C >= w[index]) {
			// ���ܵ�ǰ�ͷ��µ�ǰ�Ľ����С
			res = max(res, v[index] + findValue(w, v, index - 1, C - w[index]));
		}
		memo[index][C] = res;

		return res;
	}

public:
	int packet(vector<int>& w, vector<int>& v, int C) {
		int size = w.size();
		memo = vector<vector<int>>(size, vector<int>(C + 1, -1));
		for (int i = 0; i <= C; i++)
			memo[0][i] = i > w[i] ? v[0] : 0;
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
