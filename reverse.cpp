#include<iostream>
using namespace std;

class Solution{
public:
    int reverse(int x){
        long result=0;
        int b=x;
        while(x){
            /**/
            result = result*10 + x % 10;
            x /= 10;
        }
        return (x>INT_MAX || x<INT_MIN)?0:result;
    }
public:
  bool isPalindrome(int x) {
      long result=0;
      //只要被10整除肯定不是回文
      if(x<0||(x!=0 && x%10==0))
          return false;
      else{
          while(x){
              result = result * 10 + x % 10;
              x /= 10;
          }
         // x==result/10 可以在0-9中减少一次while循环的比较
          return (result == x)||(x==result/10);

      }
  }
};

int main(){
    Solution rev;
    int a = 3;
    //cout<<rev.reverse(a)<<endl;
    cout<<rev.isPalindrome(a);
}
