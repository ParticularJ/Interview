/*
��ͷ��β������ÿһ�У�Ȼ�󷵻�
*/

 class solution {
 public:
     vector<int> getrow(int rowindex) {
         vector<vector<int> > res;
         for(int i=0;i<rowindex+1;i++){
             vector<int> temp(i+1);
             temp[0] = temp[i] = 1;
             for(int j=1;j<i;j++){
                 temp[j] = res[i-1][j] + res[i-1][j-1];  
             }
             res.push_back(temp);
         }
         return res[rowindex];
     }
 };


 /*
 �������⣬Ҫ�Ӻ���ǰ���ɣ�Ҫ��Ȼ�ͻ��и�������
 */
class Solution {
public:
	vector<int> getRow(int rowIndex) {
		vector<int> res(rowIndex + 1, 0);
		//��һλΪ1
		res[0] = 1;
		for (int i = 1; i<rowIndex; i++) {
			for (int j = i; j > 0; j--) {
				// ���һλΪ1
				if (i == j)res[j] = 1;
				else
					// ��ǰλ���ǵ�ǰλ����һλ�ĺ�
					res[j] = res[j] + res[j - 1];
			}
		}
		return res;
	}
};