class Solution {
public:
	int maxArea(vector<int>& height) {
		int size = height.size();
		int area = 0;
		for (int i = 0; i<size; i++) {
			for (int j = i + 1; j<size; j++) {
				area = max(area, (j - i)*min(height[i], height[j]));
			}
		}
		return area;
	}

public:
	int maxArea(vector<int>& height) {
		int begin = 0;
		int end = height.size() - 1;
		int area = 0;
		while (begin < end) {
			area = max(area, (end - begin)* min(height[begin], height[end]));
			if (height[begin] < height[end])
				begin++;
			else
				end--;
		}
		return area;
	}
};