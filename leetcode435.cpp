

/*

动态规划，模拟最长上升子序列
*/
bool compare(const Interval& a, const Interval& b) {
	if (a.start != b.start)
		return a.start<b.start;
	else
		return a.end<b.end;
}
class Solution {
public:

	int eraseOverlapIntervals(vector<Interval>& intervals) {
		int size = intervals.size();
		if (size == 0) return 0;
		sort(intervals.begin(), intervals.end(), compare);
		vector<int> memo(size, 1);
		for (int i = 1; i<size; i++) {
			for (int j = 0; j<i; j++) {
				if (intervals[j].end <= intervals[i].start)
					memo[i] = max(1 + memo[j], memo[i]);
			}
		}


		return size - memo[size - 1];

	}
};


/*
贪心算法，结尾越小，留给后面可选空间就越大
*/

/**
* Definition for an interval.
* struct Interval {
*     int start;
*     int end;
*     Interval() : start(0), end(0) {}
*     Interval(int s, int e) : start(s), end(e) {}
* };
*/

bool compare(const Interval& a, const Interval& b) {
	if (a.end != b.end)
		return a.end<b.end;
	else
		return a.start<b.start;
}
class Solution {
public:

	int eraseOverlapIntervals(vector<Interval>& intervals) {
		int res = 1;
		int size = intervals.size();
		if (size == 0) return 0;
		sort(intervals.begin(), intervals.end(), compare);

		int pre = 0;
		for (int i = 1; i<size; i++) {
			if (intervals[pre].end <= intervals[i].start) {
				res++;
				pre = i;
			}
		}


		return size - res;

	}
};