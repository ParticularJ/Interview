/*
The n-queens puzzle is the problem of placing n queens on an n��n chessboard such that no two queens attack each other.

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
	���ȣ����һ�����Ѿ�����һ���ʺ���ô���оͲ�Ӧ���ٳ��ֻʺ�
	�ڶ����Խ��߲�Ӧ�ó��֣�   ��0��0����0��1����0��2��
	                         ��1��0����1��1����1��2��
							 ��2��0����2��1����2��2��
		  �����ϵ����µĶԽ��ߺ���ȣ������ϵ����µĶԽ��߲����

*/

class Solution {
private:
	vector<vector<string>> res;
	vector<bool> col, diag1, diag2;
	// һ��n���ʺ�indexΪ��Ӧ���У� record��¼��Ӧ��λ��
	void findQueues(int n, int index, vector<int>& record) {
		if (index == n) {
			res.push_back(generateBoard(n, record));
			return;
		}

		for (int i = 0; i < n; i++) {
			// ���ڶ�Ӧ���У��Խ���
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
		// �Ƚ�ÿһ�б�Ϊ .... 
		// STRING ���÷�ֵ��ע��
		vector<string> board(n,  string(n, '.'));
		// ����Ӧ�洢�������ΪQ
		for (int i = 0; i < record.size(); i++) {
			board[i][record[i]] = 'Q';
		}
		return board;
	}

public:
	vector<vector<string> > solveQueues(int n) {
		res.clear();
		// ����Ӧ���б�ǣ�
		col = vector<bool>(n, false);
		// �����Խ��ߵı��
		diag1 = vector<bool>(2 * n - 1, false);
		diag2 = vector<bool>(2 * n - 1, false);
		vector<int> record;
		findQueues(n, 0, record);
		return res;
	}
};