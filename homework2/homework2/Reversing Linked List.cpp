#include "pch.h"
#include <iostream>
#include<iomanip>
#define Maxsize 100000
typedef struct Node {
	int data;
	int next;

}LinkedList;
using namespace std;
int test(LinkedList a[], int firstaddress)
{
	firstaddress = 1000;
	a[firstaddress].data = 100;
	a[firstaddress].next = -1;
	return firstaddress;
}
void printList(LinkedList a[], int firstAddress)
{
	int tempAddress;
	if (a[firstAddress].next != -1)
		cout << setw(5) << setfill('0') << firstAddress << " " << a[firstAddress].data << " " << setw(5) << setfill('0') << a[firstAddress].next << endl;
	else
		cout << setw(5) << setfill('0') << firstAddress << " " << a[firstAddress].data << " " << a[firstAddress].next;

	tempAddress = a[firstAddress].next;
	while (tempAddress != -1)
	{
		if (a[tempAddress].next != -1)
			cout << setw(5) << setfill('0') << tempAddress << " " << a[tempAddress].data << " " << setw(5) << setfill('0') << a[tempAddress].next << endl;
		else
			cout << setw(5) << setfill('0') << tempAddress << " " << a[tempAddress].data << " " << a[tempAddress].next;
		tempAddress = a[tempAddress].next;
	}
}
int reverseList(LinkedList a[], int firstAddress, int k)
{
	int cnt = 1;
	int  New, Old, tmp;
	New = firstAddress;
	Old = a[firstAddress].next;
	while (cnt < k)
	{
		//if (a[Old].next != -1)                      //消除无关结点的影响
		//{
		tmp = a[Old].next;
		a[Old].next = New;
		New = Old;
		Old = tmp;
		cnt++;
		/*else
		{
			a[Old].next = New;
			New = Old;
		}*/
	}
	a[firstAddress].next = Old;
	return New;
}
int getSize(LinkedList a[], int firstAddress)
{
	int tmp, counter = 0;
	tmp = a[firstAddress].next;
	if (tmp != -1) counter++;
	while (tmp != -1)
	{
		tmp = a[tmp].next;
		counter++;
	}
	return counter;
}
int main()
{
	int firstAddress, n, k, i;
	LinkedList a[Maxsize];
	cin >> firstAddress >> n >> k;
	int address;                      //input data 
	for (i = 0; i < n; i++)
	{
		cin >> address;
		cin >> a[address].data;
		cin >> a[address].next;
	}
	int saveAddress, tmpAddress, size;
	size = getSize(a, firstAddress);
	saveAddress = firstAddress;                    //保存首地址
	firstAddress = reverseList(a, firstAddress, k);


	for (i = 1; i <= size / k; i++)
	{
		if (a[saveAddress].next == -1)
			break;
		if (a[a[saveAddress].next].next == -1)   //消除无关结点影响
			break;
		tmpAddress = a[saveAddress].next;
		a[saveAddress].next = reverseList(a, tmpAddress, k);
		saveAddress = tmpAddress;

	}

	printList(a, firstAddress);

}