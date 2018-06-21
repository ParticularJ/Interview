#include<iostream>
#include<stack>
#include<string>


// 使用栈从而区分优先级
using namespace std;

class Solution{
public:
  stack<int> num;
  stack<char> symbol;
  void pop_stack(){
    int a=num.top();num.pop();
    int b=num.top();num.pop();
    char c=symbol.top();symbol.pop();
    if(c=='+')num.push(a+b);else
    if(c=='-')num.push(b-a);else
    if(c=='*')num.push(a*b);else
    if(c=='/')num.push(b/a);
    //cout<<a<<" "<<b<<endl;
    //cout<<num.top();
  }

  int caculate(string s){
    int size = s.size();
    for(int i=0;i<size;i++){
      if(s[i]==' '){
        continue;
      }
      else
      if(s[i]>='0'&&s[i]<='9'){
          int N=s[i]-'0';
          for(;i+1<size&&s[i+1]>='0'&&s[i+1]<='9';i++){
              N=N*10 + (s[i+1]-'0');
          }
          num.push(N);
        //  cout<<N<<endl;
          continue;
      }
      else
      if(s[i]=='+'||s[i]=='-'){
        // cout<<s[i]<<endl;
          while(!symbol.empty()){
            pop_stack();
          }
          symbol.push(s[i]);
          continue;
      }
      else{
      //  要判断上一次的符号，从而区分乘除和加减的优先级
        while(!symbol.empty()&&(symbol.top()=='*'||symbol.top()=='/')){
          pop_stack();
        }
        symbol.push(s[i]);
      }
    }
    if(num.empty())return 0;
    else{
      while(!symbol.empty()){
      pop_stack();
      }
      return num.top();
    }
  }
};

int main(){
  Solution cal;
  string a = "1+2*3";
  cout<<cal.caculate(a);
  return 0;
}
