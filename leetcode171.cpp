#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution{
public:
  int titleToNumber(string s) {
        int res = 0;
        for(int i=0;i<s.length();i++){
          res = res*26 + (s[i] -'A' +1) ;
        }
        return res;
    }
  string titleToChar(int n){
    string res;
    while(n>0){
      n--;
      res.insert(res.begin(), char('A' + n%26));
      n/=26;
    }
    return res;
  }
};


int main(){
  Solution title;
  string s = "B";
  string b;
  int a = 2;
  cout<<title.titleToNumber(s);
  b=title.titleToChar(a);
  for(auto e:b){
    cout<<e;
  }
}
