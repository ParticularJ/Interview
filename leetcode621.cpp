/*
贪心的策略
*/


class Solution {
public:
	//统计出现的频率
	int cnt[26];
	//统计上一次出现的时间，因为同一个任务要间隔n才可以
	int last[26];
	int leastInterval(vector<char>& tasks, int n) {
		for (auto i : tasks)
			cnt[i - 'A']++;
		int sloved = tasks.size();

		for (int t = n + 1;; t++) {
			int ans = -1;
			for (int i = 0; i < 26; i++) {
				// 保证存在并且间隔为n.
				if (cnt[i] > 0 && t - last[i] > n) {
					// 每次取最多的去做
					if (ans == -1)ans = i;
					else if (cnt[ans] < cnt[i])
						ans = i;
				}
			}
			if (ans != -1) {
				sloved--;
				cnt[ans]--;
				last[ans] = t;
				if (sloved == 0)
					// 从 n+1开始的，所以t-n+1-1 = t-n;
					return t - n;
			}
		}
	}
};