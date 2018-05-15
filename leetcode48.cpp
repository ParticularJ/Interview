#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> rotate(vector<vector<int>>& matrix) {
        vector<vector<int>> res;
        res = matrix;
        int row = matrix.size();
        for(int i=0;i<row;i++){
            for(int j=row-1;j>=i;j--){
                int temp = res[i][j];
                res[i][j] = res[j][i];
                res[j][i] = temp;
            }
        }
      //  return res;
        int count=row-1;
         for(int i=0;i<int(row/2);i++){
           for(int j=0;j<row;j++){
             int temp=res[j][i];
             res[j][i]=res[j][count];
             res[j][count]=temp;
           }
           count--;
         }
    return res;
  }
};


int main(){
  vector<vector<int>> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  Solution rot;
  vector<vector<int>> b;
  b=rot.rotate(a);
  for(auto c:b){
    for(auto d:c){
      cout<<d;
    }
  }
  return 0;
}
