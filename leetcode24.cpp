/*
Given a linked list, swap every two adjacent nodes and return its head.

Example:

Given 1->2->3->4, you should return the list as 2->1->4->3.
*/

/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/

/*
思路： 分别设置四个节点， p，node1, node2, next 
      交换1，2 ，则使得node1 -> next, node2->node1, p->next = node2, p = node1
*/
class Solution {
public:
	ListNode* swapPairs(ListNode* head) {
		ListNode* dummy = new ListNode(0);
		dummy->next = head;
		ListNode* p = dummy;
		while (p->next && p->next->next) {
			ListNode* node1 = p->next;
			ListNode* node2 = node1->next;
			ListNode* next = node2->next;

			node1->next = next;
			node2->next = node1;
			p->next = node2;

			p = node1;
		}

		ListNode *res = dummy->next;
		delete dummy;
		return res;


	}
};
