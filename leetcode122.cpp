#include<iostream>
#include<vector>

using namespace std;
//思想，贪心算法，只要为正我们都可以去买卖

class Solution{
public:
  int maxProfit(vector<int>& prices){
    if(!prices.size() || prices.size()==1)return 0;
    int res = 0;
    for(int i=0;i<prices.size()-1;i++){
      if(prices[i]<prices[i+1]){
        res += prices[i+1] - prices[i];
      }
    }
    return res;
  }
};

int main(){
  Solution max;
  vector<int> a = {7, 1, 5, 3, 6, 4};
  cout<<max.maxProfit(a);
}
