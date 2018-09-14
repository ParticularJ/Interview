class Solution {
public:
    int count(int n){
        int res=0;
        while(n>0){
            res+=(n%10)*(n%10);
            n/=10;
        }
        return res;
    }
public:
    bool isHappy(int n) {
        //int 有10位 ，所以最大值为499999999，所以平方相加，最大为4+9*9*9 = 810
        vector<bool> flag(999,0);
        for(;n!=1;){
            int new_n = count(n);
            if(new_n==1)break;
            if(flag[new_n]==1)return false;
            flag[new_n]=1;
            n=new_n;
        }
        return true;
    }
};



class Solution {
public:
	int count(int n) {
		int sum = 0;
		while (n) {
			int temp = n% 10;
			sum += temp*temp;
			n /= 10;
		}
		return sum;
	}

	bool isHappy(int n) {
		int new_n = 0;
		set<int> record;
		while (new_n != 1) {
			int new_n = count(n);
			if (new_n == 1)break;
			if (record.find(new_n) != record.end())
				return false;
			record.insert(new_n);
			n = new_n;
		}
		return true;
	}
};