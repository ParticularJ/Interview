#include<iostream>
#include<vector>
#include<string>
#include<iterator>

using namespace std;
//因为a.b会不一样长，怎样解决才是关键，之后按照进位的加法即可
//左边补0是关键
//c==1,特别重要，亮点
//字符串拼接


class Solution{
public:
  string addBinary(string a, string b){
    string result="";
    int c=0,i=a.size()-1,j=b.size()-1;
    while(i>=0||j>=0||c==1){
      c += i >=0 ? a[i--]-'0':0;
      c += j >=0 ? b[j--]-'0':0;
      //确保是字符串
      result = char(c%2+'0')+result;
      c/=2;
    }
    return result;
  }
};


void main(){
  Solution aB;
  string a = "10";
  string b = "11";
  cout<<aB.addBinary(a,b)<<endl;
  cout<<char(1+'0')<<endl;
  cout<<char('0')+a+char('0');
}
