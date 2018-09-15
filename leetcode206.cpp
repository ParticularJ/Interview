/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/

/* 记录三个节点，分别为pre, cur, next;
  pre  cur	next
	    1  ->  2  ->  3
      pre cur      next
NULL <- 1  2   ->  3     	  
*/
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		ListNode * pre = NULL;
		ListNode *cur = head;
		while (cur) {
			ListNode* next = cur->next;
			cur->next = pre;
			pre = cur;
			cur = next;
		}
		return pre;
	}
};