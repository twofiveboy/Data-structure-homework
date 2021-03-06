// homework2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#define Maxsize 1000
struct Node {
	int coef;     // 系数
	int expon;   //指数
	Node*   Next; /* 指向下一个结点的指针 */
};
typedef Node* Polynomial;
using namespace std;
void read(Polynomial& p, int n, int a[], int b[])
{
	int i;
	Polynomial temp,rear=p;  
	for(i=0;i<n;i++)
	{   
		temp = (Polynomial)malloc(sizeof(struct Node));
		temp->Next = NULL;
		temp->coef = a[i];
		temp->expon = b[i];
		rear->Next = temp;
		rear = rear->Next;
	}
	
}
void print(Polynomial p)
{   
	p = p->Next;
	if (!p) cout <<"0 0";
	while (p)
	{
		cout << p->coef << " " << p->expon;         
		p = p->Next;
		if (p) cout << " ";               //符合格式要求
	}

}
Polynomial Add(Polynomial p1, Polynomial p2)
{
	Polynomial p3,rear,temp;
	p3 = (Polynomial)malloc(sizeof(struct Node));
	p3->Next = NULL;
	rear = p3;
	p1 = p1->Next;
	p2 = p2->Next;
	while (p1&&p2)
	{
		if (p1->expon > p2->expon)
		{
			temp = (Polynomial)malloc(sizeof(struct Node));
			temp->Next = NULL;
			temp->coef = p1->coef;
			temp->expon = p1->expon;
			rear->Next = temp;
			rear = rear->Next;
			p1 = p1->Next;
		}
		else if (p1->expon == p2->expon)
		{
			temp = (Polynomial)malloc(sizeof(struct Node));
			temp->Next = NULL;
			if (temp->coef = p1->coef + p2->coef)
			{
				temp->expon = p1->expon;
				rear->Next = temp;
				rear = rear->Next;
			}
			p1 = p1->Next;
			p2 = p2->Next;
		}
		else
		{
			temp = (Polynomial)malloc(sizeof(struct Node));
			temp->Next = NULL;
			temp->coef = p2->coef;
			temp->expon = p2->expon;
			rear->Next = temp;
			rear = rear->Next;
			p2 = p2->Next;
		}
	}
	for(;p1;p1=p1->Next)
	{
		temp = (Polynomial)malloc(sizeof(struct Node));
		temp->Next = NULL;
		temp->coef = p1->coef;
		temp->expon = p1->expon;
		rear->Next = temp;
		rear = rear->Next;
	}
	for(;p2;p2=p2->Next)
	{
		temp = (Polynomial)malloc(sizeof(struct Node));
		temp->Next = NULL;
		temp->coef = p2->coef;
		temp->expon = p2->expon;
		rear->Next = temp;
		rear = rear->Next;
	}
	return p3;
}
Polynomial Mult(Polynomial p1, Polynomial p2)
{
	Polynomial p4, item, front,temp,p2init;
	p4 = (Polynomial)malloc(sizeof(struct Node));
	p4->Next = NULL;
	p1 = p1->Next;
	p2 = p2->Next;
	p2init = p2;
	if (!p1 || !p2) return p4;
	while (p1)
	{   
		                                  //某一项与另一个多项式的乘积
		item = (Polynomial)malloc(sizeof(struct Node));
		item->Next = NULL;
		front = item;
		while (p2)
		{
			temp = (Polynomial)malloc(sizeof(struct Node));
			temp->Next = NULL;
			temp->coef = p1->coef*p2->coef;
			temp->expon = p1->expon+p2->expon;
			item->Next = temp;
			item = item->Next;
			p2 = p2->Next;
		}
		p2 = p2init;     //初始化p2
		p4 = Add(p4, front);          
		p1 = p1->Next;
	}
	return p4;
}
int main()
{
	Polynomial p1, p2,p3,p4;
	p1 = (Polynomial)malloc(sizeof(struct Node));
	p2 = (Polynomial)malloc(sizeof(struct Node));
	p1->Next = p2->Next = NULL;
	int n1, n2,i;
	int a[Maxsize],b[Maxsize];
	cin >> n1;                       //存取多项式数据
	for (i = 0; i < n1;i++)
	{
		cin >> a[i] >> b[i];
	}
	read(p1, n1, a, b);
	cin >> n2;
	for (i = 0; i < n2; i++)
	{
		cin >> a[i] >> b[i];
	}
	read(p2, n2, a, b);
	p4 = Mult(p1, p2);
	print(p4);
	cout << endl;
	p3 = Add(p1, p2);
	print(p3);

}

