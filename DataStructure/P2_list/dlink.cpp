#include <iostream>
using namespace std;
struct Node
{
	int data;
	Node *next; // 指向下一个节点
	Node *prev; // 指向前一个节点
};

//对链表进行反转
void reverse(Node **head)
{
	Node *temp = NULL;
	Node *current = *head;

	//交换每个节点的后向指针和前向指针
	// 1-->2-->3, 假设2为current.
	while (current != NULL)
	{

        	std::cout<<"*************"<<endl;
		std::cout<<"prev:"<<current->prev<<"current:"<<current<<"next:"<<current->next<<endl;
		
        
        	temp = current->prev; //temp=1
		current->prev = current->next; //3-->2
		current->next = temp;            //2-->1 
		current = current->prev; //3-->2-->1, current变为3，继续往后循环。
		
        
	}
	//总结：先处理前向指针，然后处理后向指针。这些操作都只对当前节点(current),不涉及其它节点。
	//1.缓存前向指针
	//2.将后向指针赋值给前向指针
	//3.将缓存的前者指针，赋值给后向指针
	//4.当前节点指针移动到下一个待处理节点

	//修改头指针之前，先检测链表是否为空链表，或者只有一个节点的情况
	if (temp != NULL)
		*head = temp->prev;
}

// 给定链表的头指针(head)以及一个整数，插入一个新的节点至链表的头部  
// 之所以传入双指针，因为函数中需要修改链表  
void push(Node** head, int newData)
{
	//1. 分配新节点内存  
	Node* newNode = new Node;

	//2. 赋值  
	newNode->data = newData;

	//3. 将原始头节点做为新节点的后向指针，而前向指针置为NULL  
	newNode->next = (*head);
	newNode->prev = NULL;

	//4. 将原始头节点的前向指针置为新的节点  
	if ((*head) != NULL)
		(*head)->prev = newNode;

	//5. 将头指针置为新的节点  
	(*head) = newNode;
}

void printList(Node *head)
{
	while (head != NULL)
	{
		std::cout<<" "<<head->data<<" ";
		head = head->next;
	}
	std::cout << std::endl;
}


int main()
{
	//初始化链表为：10<->8<->6<->4<->2<->0
	Node* head = NULL;
	push(&head, 0);
	push(&head, 2);
	push(&head, 4);
	//push(&head, 6);
	//push(&head, 8);
	//push(&head, 10);

	std::cout << "Original DLL is: ";
	printList(head);

	reverse(&head);

	std::cout << "Reversed DLL is: ";
	printList(head);
	return 0;
}
