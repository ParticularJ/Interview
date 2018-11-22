/*
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

Example:

Input: 4
Output: [
[".Q..",  // Solution 1
"...Q",
"Q...",
"..Q."],

["..Q.",  // Solution 2
"Q...",
"...Q",
".Q.."]
]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above.
*/

/*
	首先，如果一个列已经有了一个皇后，那么该列就不应该再出现皇后
	第二，对角线不应该出现，   （0，0）（0，1）（0，2）
	                         （1，0）（1，1）（1，2）
							 （2，0）（2，1）（2，2）
		  从右上到左下的对角线和相等，从左上到右下的对角线差相等

*/

class Solution {
private:
	vector<vector<string>> res;
	vector<bool> col, diag1, diag2;
	// 一共n个皇后，index为对应的行， record记录相应的位置
	void findQueues(int n, int index, vector<int>& record) {
		if (index == n) {
			res.push_back(generateBoard(n, record));
			return;
		}

		for (int i = 0; i < n; i++) {
			// 不在对应的列，对角线
			if (!col[i] && !diag1[index + i] && !diag2[index - i + n - 1]) {
				record.push_back(i);
				col[i] = true;
				diag1[index + i] = true;
				diag2[index - i + n - 1] = true;
				findQueues(n, index + 1, record);
				col[i] = false;
				diag1[index + i] = false;
				diag2[index - i + n - 1] = false;
				record.pop_back();
			}
		}
		return;
	}

	vector<string> generateBoard(int n, vector<int>& record) {
		assert(record.size() == n);
		// 先将每一行变为 .... 
		// STRING 的用法值得注意
		vector<string> board(n,  string(n, '.'));
		// 将对应存储的坐标变为Q
		for (int i = 0; i < record.size(); i++) {
			board[i][record[i]] = 'Q';
		}
		return board;
	}

public:
	vector<vector<string> > solveQueues(int n) {
		res.clear();
		// 将对应的列标记，
		col = vector<bool>(n, false);
		// 两个对角线的标记
		diag1 = vector<bool>(2 * n - 1, false);
		diag2 = vector<bool>(2 * n - 1, false);
		vector<int> record;
		findQueues(n, 0, record);
		return res;
	}
};