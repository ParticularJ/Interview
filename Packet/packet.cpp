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

		if (size == 0)
			return 0;
		memo = vector<vector<int>>(size, vector<int>(C + 1, 0));
		for (int i = 0; i < C + 1; i++) {
			memo[0][i] = i >= w[0] ? v[0] : 0;
		}
		for (int i = 1; i < size; i++) {
			for (int j = 0; j < C+1; j++) {
				if (j - w[i] >= 0) {
					memo[i][j] = max(memo[i - 1][j], memo[i - 1][j - w[i]] + v[i]);
				}
			}
		}
		return memo[size-1][C];

		memo = vector<vector<int>>(size, vector<int>(C + 1, -1));
		for (int i = 0; i <= C; i++)
			memo[0][i] = i > w[i] ? v[0] : 0;

		// ����w, v, ��������Ԫ�أ��Լ�����
		// �ݹ�
		// return findValue(w, v, size - 1, C);
	}

public:
	int packet1(vector<int>& w, vector<int>& v, int C) {
		int size = w.size();
		if (size == 0 || C == 0)
			return 0;
		// ��һ��vector��¼�������������
		// ��Ϊ����ǰֵ�͵�ǰֵ�Լ���ǰֵ��ȥweightֵ��Ӧ��value�йأ�
		
		vector<int> record(C + 1, -1);
		for (int i = 0; i < C + 1; i++)
			record[i] = i > w[0] ? v[0] : 0;
		for (int i = 1; i < size; i++) {
			for (int j = C; j >= w[i]; j--) {
				record[i] = max(record[i - w[i]], v[i] + record[i - w[i]]);
			}
		}

		return record[C];

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
