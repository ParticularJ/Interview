#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


int main()
{

	// weight 每个物体的重量， 价值，以及背包的容积
	int weight[] = { 1, 2, 3 };
	int value[] = { 6, 10, 12 };
	int C = 5;

	vector<vector<int> > memo(2, vector<int>(C + 1, -1));
	memo[0][0] = 0;
	
	for (int i = 0; i < C + 1; i++)
		memo[0][i] = (i>=weight[0])?value[0]:0;
	//for (int j = 0; j < 3; j++)
	//	memo[j][0] = 0;

	for (int i = 1; i < 3; i++) {
		for (int j = 0; j < C + 1; j++) {
			memo[i%2][j] = memo[(i - 1)%2][j];
			if (j - weight[i] >= 0)
				memo[i%2][j] = max(memo[i%2][j], memo[(i - 1)%2][j - weight[i%2]] + value[i%2]);
				
		}
	}
	for (auto i : memo) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
	cout << memo[0][C];

	//优化为一个数组
	vector<int> memo1(C + 1, -1);
	for (int i = 0; i < C + 1; i++)
		memo1[i] = (i >= weight[0])?value[0] : 0;

	for (int i = 1; i < 3; i++) {
		for (int j = C; j >= weight[i]; j--) 
			memo1[j] = max(memo1[j], value[i] + memo1[j - weight[i]]);
	}

	cout << memo1[C];



	return 0;
}
