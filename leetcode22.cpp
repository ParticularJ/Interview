#include<vector>
#include<iostream>
#include<string>

using namespace std;

//思路：只要‘（’的次数大于等于‘）’的次数即可

class  Solution{
public:
  void helper(vector<string>& res, string s, int left, int right){
    if(left>right)return;
    if(left==0 && right==0){
      res.push_back(s);
      return;
    }
    if(left>0){
      helper(res, s+"(", left-1, right);
    }
    if(right>0){
      helper(res, s+")", left, right-1);
    }
  }
public:
  vector<string> generateParenthesis(int n){
    vector<string> res;
    if(n==0)return res;
    helper(res, "", n, n);
    return res;
  }
};

int main(){
  Solution gP;
  int n = 2;
  vector<string> a;
  a = gP.generateParenthesis(n);
  for(auto &c:a){
    cout<<c;
  }
}
