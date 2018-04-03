#include<iostream>
#include<vector>
#include<string>

using namespace std;

// 确保对每一个字符串进行比较，但是不能超出范围
// 因此，主循环我们要用到 m-n+1,确保在范围内


class Solution{
public:
  int strStr(string haystack, string needle){
    int a=haystack.size();
    int b=needle.size();
    if(!b) return 0;
    for(int i=0;i<a-b+1;++i){
      int j=0;
      for(;j<b;++j){
        //i+j,保证遍历needle
        if(haystack[i+j]!=needle[j])
          break;
        }
        if(j==b) return i;
    }
    return -1;
  }
};


int main(){
  string a="aabaaaababaababaa";
  string b="bbbb";
  cout<<a.size()<<" "<<b.size()<<endl;
  Solution str1;
  cout<< str1.strStr(a, b);
}
