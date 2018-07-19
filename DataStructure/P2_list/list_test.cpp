/*
 * =====================================================================================
 *
 *       Filename:  link_revert.cpp
 *
 *    Description:  revert link
 *
 *        Version:  1.0
 *        Created:  05/04/2016 07:33:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiangwei.tian (), tianxiangwei@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <string.h>
using namespace std;
typedef struct List_Node
{
	int m_value;
	struct List_Node * m_next;
}list_node;

void Print_Link(list_node * head)
{
	list_node * temp_node=NULL;
	temp_node=head;
	while(temp_node)
	{
		cout<<temp_node->m_value<<" ";
		temp_node=temp_node->m_next;
	}
	cout<<endl;
}

list_node * Create_Node(int value)
{
	list_node *node=new list_node();
	node->m_value=value;
	node->m_next=NULL;
	return node;
}

void AddToTail(list_node **head,int value)
{
	list_node *new_node=Create_Node(value);
	list_node *pNode;
	pNode=*head;
	if(pNode==NULL)
	{
		pNode=new_node;	
	}
	else
	{
		while(pNode->m_next!=NULL)
			pNode=pNode->m_next;
		pNode->m_next=new_node;
	}
}


//单链表的转置--循环方法
list_node * RevertByLoop(list_node *head)
{
	list_node *pnode,*prev_node=NULL,*pnext=NULL;
	list_node *revert_head;
	pnode=head;
	while(pnode)
	{
		pnext=pnode->m_next;
		pnode->m_next=prev_node;
		prev_node=pnode;
		pnode=pnext;
	}
	return prev_node;
}

//单链表的转置--递归方法
list_node * RevertByRecursion(list_node *head)
{
	if(head==NULL||head->m_next==NULL)
		return head;
	//递归返回的是最后一个节点
	list_node *newhead=RevertByRecursion(head->m_next);
	head->m_next->m_next=head;
	head->m_next=NULL;
	return newhead;
}

//输入一个单向链表，输出该链表中倒数第k个节点，链表的倒是第0个节点为链表的尾指针
//分析:设置两个指针p1,p2，首先p1和2都指向head,然后p2向前走k步，这样p1和p2之间就间隔k个节点,
//最后p2和p2同时向前移动，直至p2走到链表末尾

list_node * theKthNode(list_node *head,int k)
{
	list_node *before_node,*after_node;
	if(head==NULL)
		return NULL;
	before_node=after_node=head;
	int count=k;
	while(after_node&&count--)
	{
		after_node=after_node->m_next;
	}
	if(after_node==NULL)
	{
		printf("node count less then K");
		return NULL;
	}
	while(after_node->m_next)
	{
		before_node=before_node->m_next;
		after_node=after_node->m_next;
	}
	return before_node;
}


list_node * theKthNode1(list_node *head,int k)
{
	list_node *before_node,*after_node;
	if(head==NULL)
		return NULL;
	before_node=after_node=head;
	int i=k;
	for(;i>0&&after_node;i--)
	{
		after_node=after_node->m_next;
	}
	if(i>0) return NULL;
	while(after_node!=NULL)
	{
		before_node=before_node->m_next;
		after_node=after_node->m_next;
	}
	return before_node;
}

//求链表的中间节点，如果链表长度为偶数，返回中间两个节点中的任意一个，若为奇数，则返回中间节点

list_node * theMidNode(list_node *head)
{
	list_node *fast,*slow;
	if (head==NULL)
		return NULL;
	fast=slow=head;
	//如果要求在链表长度为偶数的情况下，返回中间两个节点中的第一个，则用如下循环
	//while(fast&&fast->m_next!=NULL&&fast->m_next->m_next!=NULL)
	while(fast&&fast->m_next)
	{
		slow=slow->m_next;
		fast=fast->m_next->m_next;
	}
	return slow;
}

//判断链表是否有环
bool hasCircle(list_node *head,list_node **circleNode)
{
	list_node *fast,*slow;
	if(head==NULL)
		return NULL;
	fast=slow=head;
	while(fast&&fast->m_next)
	{
		slow=slow->m_next;
		fast=fast->m_next->m_next;
		if(fast==slow)
		{
			*circleNode=fast;
			return true;
		}
	}
	return false;
}


//输入一个单向链表，判断链表是否有环，如果有环，找到环的入口点
//分析：按照上述判断有环的方法，p2每次走两步，p1每次一步的方法，如果p2和p1重合则确定单向链表有环，
//接下来让p2回到链表的头部，重新走，每次步长为1，则p1和p2再次相遇的点即为环的入口点 
list_node * findLoopPort(list_node *head)
{
	list_node *fast,*slow;
	if(head==NULL||head->m_next==NULL)
		return NULL;
	fast=slow=head;
	while(fast&&fast->m_next)
	{
		slow=slow->m_next;
		fast=fast->m_next->m_next;
		if(slow==fast)
			break;
	}
	if(slow!=fast)
	{
		printf("no circle\n");
		return NULL;
	}

	fast=head;
	while(fast!=slow)
	{
		fast=fast->m_next;
		slow=slow->m_next;
	}
	return fast;
}

//判断两个链表是否相交
//算法思路：判断两个链表的末尾节点是否相等
bool isIntersect(list_node *h1,list_node *h2)
{
	if(h1==NULL||h2==NULL)
		return false;
	while(h1->m_next)
		h1=h1->m_next;
	while(h2->m_next)
		h2=h2->m_next;
	if(h1==h2)
		return true;
	else
		return false;
}

//判断有环的链表是否相交
//如果有环且两个链表相交，则两个链表都有共同的一个环，即环上的任意一个节点都存在于两个链表上。
//因此，就可以判断一链表上两指针相遇的那个节点，在不在另一个链表上。
bool isIntersectWithLoop(list_node *h1,list_node* h2)
{
	list_node *temp_node;
	list_node *circleNode1,*circleNode2;
	if(!hasCircle(h1,&circleNode1))
		return false;
	if(!hasCircle(h2,&circleNode2))
		return false;
	temp_node=circleNode1->m_next;
	while(temp_node!=circleNode1)
	{
		if(temp_node==circleNode2)
			return true;
		temp_node=temp_node->m_next;
	}
	return false;
}

//判断两个链表相交的第一个公共节点
//假设两个列表的长度分别为L1和L2,移动较长的链表|L1-L2|次，然后共同移动知道节点相等，相等的节点就是第一个公共节点
int listlength(list_node *head)
{
	int len=0;
	while(head)
	{
		len++;
		head=head->m_next;
	}
	return len;
}
list_node * findIntersectNode(list_node *h1,list_node *h2)
{
	int i=0;
	int l1=listlength(h1);
	int l2=listlength(h2);
	if(l1>l2)
	{
		for(;i<l1-l2;i++)
			h1=h1->m_next;
	}
	else
	{
		for(;i<l2-l1;i++)
			h2=h2->m_next;
	}

	while(h1&&h2)
	{
		if(h1==h2)
			return h1;
		else
		{
			h1=h1->m_next;
			h2=h2->m_next;
		}
	}
	return NULL;

}


//O(1)时间删除链表节点，从无头单链表中删除节点
//即用下一个节点数据覆盖要删除的节点，然后删除下一个节点 因此也要求待删除的节点不能是尾节点
void deleteRandomNode(list_node *cur)
{
	list_node *pnext;
	if(cur==NULL || cur->m_next==NULL)
		return;
	pnext=cur->m_next;
	cur->m_value=pnext->m_value;
	cur->m_next=pnext->m_next;
	delete pnext;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	list_node *revert_head=NULL;
	list_node *node=NULL;
	list_node *head=Create_Node(3);
	AddToTail(&head,4);
	AddToTail(&head,5);
	AddToTail(&head,6);
	AddToTail(&head,7);
	AddToTail(&head,8);
	//AddToTail(&head,9);
	//AddToTail(&head,10);
	//AddToTail(&head,11);
	Print_Link(head);
	revert_head=RevertByLoop(head);
	Print_Link(revert_head);
	revert_head=RevertByRecursion(revert_head);
	Print_Link(revert_head);
	node=theKthNode(revert_head,3);
	printf("node->m_value:%d\n",node->m_value);
	node=theKthNode(revert_head,8);
	printf("node:%p\n",node);
	node=theKthNode1(revert_head,5);
	printf("node->m_value:%d\n",node->m_value);
	getchar();
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

