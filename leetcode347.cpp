#include<iostream>
#include<unordered_map>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

class Solution{
public:
  vector<int> topKFrequent(vector<int>& nums, int k){
    unordered_map<int, int> mymap;
    vector<int> res;
    for(int i=0;i<nums.size();i++){
      mymap[nums[i]]++;
    }
    priority_queue<pair<int, int>> pq;
    for(unordered_map<int, int>::iterator iter=mymap.begin();iter!=mymap.end();iter++){
      pq.push(make_pair(iter->second, iter->first));
      if(pq.size()>mymap.size()-k){
        res.push_back(pq.top().second);
        pq.pop();
      }
    }
    return res;
  }
};

int main(){
  vector<int> a={1, 1, 1, 2, 2, 3};
  int k=2;
  Solution tkf;
  vector<int> b;
  b=tkf.topKFrequent(a, k);
  for(auto c:b){
    cout<<c;
  }
}
