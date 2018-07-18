/**
* Definition for an interval.
* struct Interval {
*     int start;
*     int end;
*     Interval() : start(0), end(0) {}
*     Interval(int s, int e) : start(s), end(e) {}
* };
*/

/*
˼·����ȥȷ�����ұ߽磬ͨ��һ�����λ����߽�+1���б߽�-1���Ӷ�ȷ�������1->0,����һ���µı߽硣

*/
class Solution {
public:
	vector<Interval> merge(vector<Interval>& intervals) {
		vector<Interval> res;
		int size = intervals.size();
		if (size == 0)return res;
		vector<int> l(size, 0), r(size, 0);
		vector<int> des(size * 2, 0);
		for (int i = 0; i < size; i++) {
			l[i] = intervals[i * 2].start;
			r[i] = intervals[i * 2 + 1].end;
			des[i * 2] = intervals[i].start;
			des[i * 2 + 1] = intervals[i].end;
		}
		sort(l.begin(), l.end());
		sort(r.begin(), r.end());
		sort(des.begin(), des.end());
		int n = unique(des.begin(), des.end()) - des.begin();
		n += 1;
		int sum = 0;
		int l_bound = 0;
		for (int p = 0, l_index = 0, r_index = 0; p < n; p++) {
			while (l_index<size&&l[l_index]==des[p]) {
				sum += 1;
				if (sum == 1) {
					l_bound = des[p];
				}
				l_index++;
			}
			while (r_index < size && r[r_index] == des[p]) {
				sum -= 1;
				if (sum == 0) {
					res.push_back(Intervals(l_bound, des[p]));
				}
				r_index++;
			}
		}
		return res;
	}
};