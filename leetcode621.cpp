/*
̰�ĵĲ���
*/


class Solution {
public:
	//ͳ�Ƴ��ֵ�Ƶ��
	int cnt[26];
	//ͳ����һ�γ��ֵ�ʱ�䣬��Ϊͬһ������Ҫ���n�ſ���
	int last[26];
	int leastInterval(vector<char>& tasks, int n) {
		for (auto i : tasks)
			cnt[i - 'A']++;
		int sloved = tasks.size();

		for (int t = n + 1;; t++) {
			int ans = -1;
			for (int i = 0; i < 26; i++) {
				// ��֤���ڲ��Ҽ��Ϊn.
				if (cnt[i] > 0 && t - last[i] > n) {
					// ÿ��ȡ����ȥ��
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
					// �� n+1��ʼ�ģ�����t-n+1-1 = t-n;
					return t - n;
			}
		}
	}
};