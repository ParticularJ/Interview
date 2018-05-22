#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

/*
思路：不能使用除法，首先想到减法，在此基础上提高算法性能
引入指数的思想，16 / 3 = 5
3*2^0 + 3*2^1 + 3*2^2=21>16,所以从3*2^2从下开始累加
因为3*2^2 =12<16, 所以累加2^2=4
3*2^2+3*2^1 = 18>16,跳过
3*2^2 + 3*2^0 = 15<16, 所以累加 2^0=1
得 4+1=5
*/
class Solution{
public:
  int divide(int dividend, int divisor){
    int res=0;
    int count=1;
    int sum=0;
    vector<int> temp;
    while(sum<=dividend){
      sum+=divisor*count;
      //cout<<sum<<endl;
      temp.push_back(divisor*count);
      count*=2;
    }
    for(auto a:temp){
      cout<<a<<endl;
    }
    //cout<<count;
    int sum1=0;
    for(int i=temp.size()-1;i>=0;i--){
      if(temp[i]+sum1>dividend)continue;
      else{
        res+=pow(2,i);
        sum1+=temp[i];
      }
    }
    return res;
  }
};

int main(){
  int a =16, b=3;
  Solution did;
  cout<<did.divide(a, b);
  return 0;
}
