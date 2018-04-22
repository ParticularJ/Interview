#include<iostream>
#include<vector>
#include<string>

using namespace std;

// 从后往前，找到第一个不是空字符串的位置
// 从这个位置往后统计最后一个字符的长度
// 理解while的用法，for循环有时候不能达到效果


class Solution{
public:
  int lengthOfLastWord(string s){
    int res=0;
    int len=s.size()-1;
    while(len>0 && s[len] == ' ')len--;
    while(len>0 && s[len] != ' '){
      len--;
      res++;
    }
    return res;
  }
};

void main(){
  string s = "";
  Solution lof;
  cout<<lof.lengthOfLastWord(s);
}
