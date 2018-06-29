/**
* Definition for singly-linked list with a random pointer.
* struct RandomListNode {
*     int label;
*     RandomListNode *next, *random;
*     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
* };
*/

/*
 其实就是一个拷贝问题，我们只要用map做相应的映射，拷贝即可
 主要考虑是否存在问题。
 map 前一个为映射后的值，后一个为原始值即可
 新的节点要与新的节点映射
*/
class Solution {
public:
	RandomListNode *copyRandomList(RandomListNode *head) {
		map<RandomListNode *, RandomListNode *> f;
		if (head == NULL)
			return NULL;
		f[head] = new RandomListNode(head->label);
		f[head->next] = head->next;
		for (RandomListNode * i = head; i; i->next) {
			if (i->next) {
				if (f[i->next] == 0) {
					f[i->next] = new RandomListNode(i->next->label);
				}
				f[i]->next = f[i->next];
			}
			if (i->random) {
				if (f[i->random] == 0) {
					f[i->random] = new RandomListNode(i->random->label);
				}
				f[i]->random = f[i->random];
			}
		}
		return f[head];
	}
};