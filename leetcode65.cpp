class Solution {
public:
	int numSquares(int n) {
		assert(n>0);
		vector<int> memo(n + 1, (1 << 31) - 2);
		memo[1] = 1;
		for (int i = 2; i <= n; i++) {
			memo[i*i] = 1;
			//  cout<<memo[i*i]<<" ";
			for (int j = 1; j <= i&&j*j <= i; j += 1) {
				memo[i] = min(memo[i], memo[j*j] + memo[i - j*j]);
			}
			//cout<<memo[i]<<" ";
		}
		return memo[n];
	}
};