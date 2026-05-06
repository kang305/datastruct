#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"doubleLoopLink.h"
DuLoopLink stu_table;
void test1() {
initDulLoopLink(&stu_table);
    for (int i = 0; i < 10; i++) {
        insertDulLoopLinkHeader(&stu_table,i+10);
    }
    showDulLoopLink(&stu_table);
    deleteValueDuLoopLink(&stu_table,10);
    showDulLoopLink(&stu_table);
    deleteAllDuLoopLink(&stu_table);
}
int main() {
test1();

    return 0;
}
/*1. 输入两个辅助指针，再引入一个合并结果的链表头dummy
 *2. 对链表1和链表2逐个遍历，当发现谁小就将这个指针插入到结果位置处
 *3. 某个链表提前结束，剩下的未遍历节点天然有序
 */
// struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
// 	struct ListNode dummy;//虚拟的头节点,真正返回值是dummy.next
// 	struct ListNode *res;
// 	dummy.next = NULL;
// 	res = &dummy;
//
// 	while(list1 && list2) {
// 		if (list1->val < list2->val) {
// 			res->next = list1;// 把list1的当前节点接到结果链表尾部
// 			list1 = list1->next;// list1后移一位，处理下一个节点
// 		} else {
// 			res->next = list2;// 把list2的当前节点接到结果链表尾部
// 			list2 = list2->next;// list2后移一位，处理下一个节点
// 		}
// 		res =res->next;// 结果链表的“尾节点”后移，始终指向最新的尾
// 	}
// 	if (list1) {//如果还有链表元素剩余让其依次链接到新表上
// 		res->next = list1;
// 	} else {
// 		res->next = list2;
// 	}
// 	return dummy.next;
// }