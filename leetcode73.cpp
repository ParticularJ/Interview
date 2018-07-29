/*
˼·���õ�һ�к͵�һ��ȥ��¼����ʡ�ռ䣬
	�ж�����0�ͽ���Ӧ�ĵ�һ�е�һ�м�Ϊ0
	�ֱ������ֵ����   
*/
class Solution {
public:
	void setZeroes(vector<vector<int>>& matrix) {
		int rows = matrix.size();
		if (rows == 0)return;
		int cols = matrix[0].size();
		if (cols == 0)return;
		int colc = 1, rowc = 1;

		//�ֱ�ͳ����û�г����㣬��������colc, rowc == 0
		for (int i = 0; i < cols; i++)
			rowc *= matrix[0][i] != 0;
		for (int j = 0; j < rows; j++)
			colc *= matrix[j][0] != 0;

		for (int i = 0; i<rows; i++)
			for (int j = 0; j<cols; j++)
				if (matrix[i][j] == 0) {
					matrix[i][0] = 0;
					matrix[0][j] = 0;
				}

		for (int i = 1; i < rows; i++)
			if (matrix[i][0] == 0)
				for (int j = 0; j < cols; j++)
					matrix[i][j] = 0;

		for (int j = 1; j < cols; j++)
			if (matrix[0][j] == 0)
				for (int i = 0; i < rows; i++)
					matrix[i][j] = 0;

		if (rowc == 0)
			for (int j = 0; j < cols; j++)
				matrix[0][j] = 0;

		if (colc == 0)
			for (int i = 0; i < rows; i++)
				matrix[i][0] = 0;
	}
};