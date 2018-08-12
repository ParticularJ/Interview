

/*
������ѧ������ö��
DP����С��������С�ģ��Դ�����
f[1] =1 ,f[2]=2
*/
public:

	int numTrees(int n) {
		if (n == 0)return 1;
		//����
		vector<int> f(n + 1, 0);
		f[0] = 1;
		for (int i = 1; i <= n; i++)
			for (int root = 1; root <= i; root++)
				//���˸�֮�������������������
				// ��߸��������ұ߸�����Ϊ����
				// i - root ����������
				// root -1 ����������
				f[i] += f[i-root] * f[root - 1];
		return f[n];
	}
};