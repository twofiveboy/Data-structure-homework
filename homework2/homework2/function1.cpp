#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
	ElementType Data; /* 存储结点数据 */
	PtrToNode   Next; /* 指向下一个结点的指针 */
};
typedef PtrToNode List; /* 定义单链表类型 */
List Merge(List L1, List L2)
{
	List p,temp;
	List temp1 = L1;
	List temp2 = L2;
	L1 = L1->Next;
	L2 = L2->Next;
	p = (List)malloc(sizeof(struct Node));   //maybe error
	p->Next = NULL;
	temp = p;
	while (L1&&L2)
	{
		if (L1->Data <= L2->Data)
		{
			temp->Next = L1;
			temp = temp->Next;
			L1 = L1->Next;
			

		}
		else 
		{
			temp->Next = L2;
			temp = temp->Next;
			L2 = L2->Next;
		}
	}
	while (L1)
	{
		temp->Next = L1;
		L1 = L1->Next;
		temp = temp->Next;
	}
	while (L2)
	{
		temp->Next = L2;
		L2 = L2->Next;
		temp = temp->Next;
	}
	temp1->Next = NULL;
	temp2->Next = NULL;
	temp->Next = NULL;
	
	return p;
}
//if (!L1 && !L2)
	//{
	//	front->Next = NULL;
	//	return front;
	//}