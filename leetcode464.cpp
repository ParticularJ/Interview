/*
���仯������ ��̬�滮���Է�Ϊ����ʵ�ַ�ʽ��һ��Ϊ���仯��������һ��Ϊ���Ƶķ�ʽ

*/


class Solution {
public:
	// 2 ����Ӯ�� 1����
	vector<int> flag;

	int dfs(int status, int maxi int sum, int dt) {
		if (flag[status] != 0)
			return flag[status] - 1;
		if (sum >= dt)return 0;

		for (int i = 0; i < maxi; i++) {
			// �����û�б�ȡ
			if ((status & (1 << i)) == 0) {
				// �Լ��᲻��Ӯ
				int temp = dfs(status | (1 << i), maxi, sum + i + 1, dt)^1;
				// ���� �ҵ���Ӯ��·
				if (temp == 1) {
					flag[status] = 2;
					return 1;
				}
			}
		}
		flag[status] = 1;
		return 0;
	}

	bool canIWin(int mc, int dt) {
		if ((mc + 1)*mc / 2 < dt)return false;
		if (dt == 0)return true;
		// ���е�״̬
		flag = vector<int>(1 << mc);
		return dfs(0, mc, 0, dt);
	}
};