/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/


/*
思路：
快慢指针，相等之后，一个指针从头走，一个指针从相遇点走，再次相遇即为起始点。
慢指针： a + b  快指针 a+b+c+b
由 2(a + b)=(a+b+c+b)  ->  a = c
所以从相遇点继续走，和从头开始走，再次相遇即为环的起点。
*/
class Solution {
public:
	ListNode *detectCycle(ListNode *head) {
		if (head == NULL || head->next == NULL)return NULL;
		ListNode* slow = head;
		ListNode* fast = head;
		ListNode* begin = head;
		while (fast->next&&fast->next->next) {
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast) {
				while (begin != slow) {
					begin = begin->next;
					slow = slow->next;
				}
				return begin;
			}
		}
		return NULL;
	}
};