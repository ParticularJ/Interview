/*
The n-queens puzzle is the problem of placing n queens on an n��n chessboard such that no two queens attack each other.



Given an integer n, return the number of distinct solutions to the n-queens puzzle.

Example:

Input: 4
Output: 2
Explanation: There are two distinct solutions to the 4-queens puzzle as shown below.
[
[".Q..",  // Solution 1
"...Q",
"Q...",
"..Q."],

["..Q.",  // Solution 2
"Q...",
"...Q",
".Q.."]
]
*/


class Solution {
private:
	// �ж϶Խ����Լ����ϲ��ظ�
	vector<bool> col, diag1, diag2;
	int res;
private:
	void findQueens(int n, int index) {
		if (n == index) {
			res++;
			return;
		}

		// ���ݷ�
		for (int i = 0; i < n; i++) {
			if (!col[i] && !diag1[i + index] && !diag2[i - index + n - 1]) {
				col[i] = true;
				diag1[i + index] = true;
				diag2[i - index + n - 1] = true;
				findQueens(n, index + 1);
				col[i] = false;
				diag1[i + index] = false;
				diag2[i - index + n - 1] = false;
			}
		}
		return;
	}
public:
	int totalNQueens(int n) {
		// ��ʼ��col�Լ� diag1�� diag2
		col = vector<bool>(n, false);
		diag1 = vector<bool>(2 * n - 1, false);
		diag2 = vector<bool>(2 * n - 1, false);
		// ���ݷ������ܵĽ�
		findQueens(n, 0);
		return res;
	}
};