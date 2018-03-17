#include<iostream>
#include<vector>
#include<string>

// 首先要理解迭代的意思，然后去统计每个字符出现的次数
// push_back对应的值


using namespace std;

class Solution{
public:
  string countAndSay(int n){
      if(n==0) return "";
      if(n==1) return "1";
      if(n==2) return "11";
      string newresult = "";
      string result =countAndSay(n-1);
      int len = result.length();
      int count =1;
      for(int i=1; i< len;i++){
        if(result[i]!=result[i-1]){
          // 特别注意，‘0’+count，使得以string形式添加计算结果
          newresult.push_back('0'+count);
          newresult.push_back(result[i-1]);
          count=1;
        }
        else count++;
        if(i == result.size()-1){
          newresult.push_back('0'+count);
          newresult.push_back(result[i]);
        }
      }
  return newresult;
}
};

int main(){
  Solution countandsay;
  string a;
  a.push_back(0+ '6');
  cout<<a[0];
  int n=5;
  cout<<countandsay.countAndSay(n);
}
