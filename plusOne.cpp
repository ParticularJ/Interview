#include<iostream>
#include<vector>
#include<string>
#include<iterator>

using namespace std;

// 题意：如果是9那么加1后就变成[1，0],
// 类似模拟进位操作
// flag很关键
class Solution{
public:
  vector<int> plusOne(vector<int>& digits){
    int a=0;
    int b=0;
    int flag=1;
    for(vector<int>::reverse_iterator iter=digits.rbegin();iter<digits.rend();iter++){
        a=*iter+flag;
        b=a%10;
        flag = a/10;
        *iter = b;
    }
    if(flag==1) digits.insert(digits.begin(),flag);
    return digits;
  }
};

void main(){
  Solution po;
  vector<int> a={1,7};
  vector<int> b;
  b=po.plusOne(a);
  for(auto s:b){
    cout<<s;
  }
}
