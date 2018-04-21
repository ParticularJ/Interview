#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution{
public:
  vector<vector<int>> generate(int numRows){
    vector<vector<int>> res;
    for(int i=0;i<numRows;i++){
      vector<int> tmp(i+1);
      tmp[0]=tmp[i]=1;
      for(int j= 1;j< i;j++){
        tmp[j]=res[i-1][j] + res[i-1][j-1];
      }
      res.push_back(tmp);
    }

    return res;
  }

};


int main(){
  Solution ger;
  int a = 3;
  vector<vector<int>> f;
  f=ger.generate(a);
  for(auto s:f){
    for(auto c:s)
    cout<<c;
  }
}
