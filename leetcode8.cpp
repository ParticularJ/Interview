#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Solution{
public:
  int myAtoi(string str){
    long long res=0;
    if(str.size()==0)return 0;
    int start=0;
    for(int i=0;i<str.size();i++){
      if(str[i]==' ')start++;
      else break;
    }
    int sign=1;
    for(int i=start;i<str.size();i++){
      if(str[i]=='-'){
        sign=-1;
        start++;
        break;
      }
      else if(str[i]=='+'){
        start++;
        break;
      }
    }
  //  cout<<start<<endl;
    vector<int> temp;
    for(int i=start;i<str.size();i++){
      if(str[0]==' '||(str[0]<='z' && str[0]>='a'))return 0;
      while('0'<=(str[i])&&(str[i])<='9'){
        res = res*10 + (str[i++]-'0');
        if(res*sign>((1<<31)-1))return  (1<<31)-1;
        if(res*sign<-(1<<31))return  -(1<<31);
      }
    }
    return res*sign;
  }
};

int main(){
  string a = "472332 wawith words";
  Solution mA;
  cout<<mA.myAtoi(a);
  return 0;
}
