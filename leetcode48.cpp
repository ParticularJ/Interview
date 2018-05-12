#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int row = matrix.size();
        for(int i=0;i<row;i++){
            for(int j=row-1;j>=i;j--){
                matrix[i][j]=matrix[j][i];
                cout<<count;
            }
        }
        for(int i=0;i<row;i++){
          for(int j=0;j<col;)
          matrix[i][i]
        }
    }
};


int main(){
  vector<vector<int>> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  vector<vector<int>> b;
  Solution rot;
  b = rot.rotate(a);
  for(auto c:b){
    for(auto d:c){
      cout<<d;
    }
  }
  return 0;
}
