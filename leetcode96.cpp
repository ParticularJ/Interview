

/*
类似数学方法，枚举
DP，从小到大，先求小的，以此类推
f[1] =1 ,f[2]=2
*/
public:

	int numTrees(int n) {
		if (n == 0)return 1;
		//遍历
		vector<int> f(n + 1, 0);
		f[0] = 1;
		for (int i = 1; i <= n; i++)
			for (int root = 1; root <= i; root++)
				//除了根之外的左子树和右子树，
				// 左边个数乘以右边个数即为总数
				// i - root 左子树个数
				// root -1 右子树个数
				f[i] += f[i-root] * f[root - 1];
		return f[n];
	}
};