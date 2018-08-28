/*
从头到尾，生成每一列，然后返回
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
 生成问题，要从后往前生成，要不然就会有覆盖问题
 */
class Solution {
public:
	vector<int> getRow(int rowIndex) {
		vector<int> res(rowIndex + 1, 0);
		//第一位为1
		res[0] = 1;
		for (int i = 1; i<rowIndex; i++) {
			for (int j = i; j > 0; j--) {
				// 最后一位为1
				if (i == j)res[j] = 1;
				else
					// 当前位就是当前位和上一位的和
					res[j] = res[j] + res[j - 1];
			}
		}
		return res;
	}
};