#include<iostream>
#include<vector>
#include<deque>

using namespace std;
/*
	
*/

class Solution {
public:
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		int size = gas.size();
		int a = 0;
		vector<int> temp;
		for (int i = 0; i < size; i++) {
			a += gas[i] - cost[i];
			temp.push_back(gas[i] - cost[i]);
		}
		if (a != 0)return -1;
		if (a == 0) {
			for (int i = 0; i < temp.size(); i++) {
				if(temp)
			}
		}
	}
};