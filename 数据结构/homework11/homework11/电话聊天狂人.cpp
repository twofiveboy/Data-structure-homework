#include"pch.h"
#include <iostream>
#include<cstdlib> //atoi
#include<cstring>//strcmp
#include<cmath>
#define maxlength 11
#define maxTableSize 1000000
using namespace std;
//初始构造模块
typedef char phoneNumber[maxlength + 1];//字符串结尾有个"/0"占位置
typedef struct pNode* PtrNode;
struct pNode {
	phoneNumber data;
	PtrNode next;
	int count; //该号码进行过的通话次数
};
typedef struct TableNode {
	int tableSize;  //表长度
	PtrNode Heads;  //存放头节点的数组
}*HashTable;
int nextPrime(int N) {    //返回一个比N大且小于maxTableSize的质数
	int i, p = (N % 2) ? N + 2 : N + 1;  //将P初始化为大于N的下一个奇数
	while (p <= maxTableSize) {
		for (i = (int)sqrt(p); i > 2; i--) {  //从(int)sqrt(p)递减扫描是否存在p的因数
			if (!(p%i)) break;  //如果存在因数：p%i=0，不是质数
		}
		if (i == 2) break;  //完整结束，所求p为质数
		else p += 2;        //不是的话寻找下一个奇数
	}
	return p;
}
HashTable createTable(int tableSize) {
	HashTable H;
	int i;
	H = new TableNode;
	H->tableSize = nextPrime(tableSize);   //寻找质数作为size
	H->Heads = new pNode[H->tableSize];   //头结点数量与size相同
	for (i = 0; i < H->tableSize; i++) {   //初始化每个头结点
		H->Heads[i].data[0] = '\0';//结束标志
		H->Heads[i].next = NULL;
		H->Heads[i].count = 0;
	}
	return H;
}

//插入模块
int Hash(int key, int tableSize) {   //哈希构造函数：除留余数法
	return key % tableSize;
}
typedef PtrNode Position;
Position Find(HashTable H, phoneNumber key) {
	Position p;
	int pos;  //除留余数法构造后的位置
	pos = Hash(atoi(key + maxlength - 5), H->tableSize);  //atoi把字符串转化为整数,以后号码五位计算pos
	p = H->Heads[pos].next;  //从头结点的后继，即第一个数据结点开始依次扫描
	while (p != NULL && strcmp(p->data, key)) p = p->next;  //当不为空且不相同时继续扫描
	return p;   //返回NULL或指向的结点
}
bool Insert(HashTable H, phoneNumber key) {
	int pos;
	Position P;
	P = Find(H, key);
	if (!P) {//之前没有这个结点
		pos = Hash(atoi(key + maxlength - 5), H->tableSize);  //atoi把字符串转化为整数,以后号码五位计算pos
		Position newuser = new pNode;
		strcpy(newuser->data, key);//将key复制到新结点
		newuser->count = 1;
		newuser->next = H->Heads[pos].next;
		H->Heads[pos].next = newuser;
		return true;
	}
	else {//如果找到了结点位置
		P->count++;  //计数器加一
		return false;
	}
}

void ScanAndPrint(HashTable H) {
	int Pcnt, Maxcnt = Pcnt = 0;// Maxcnt：最大通话次数，Pcnt：多少个同为最大通话的人
	PtrNode ptr;            //临时结点
	phoneNumber Minphone;  //要输出的最小号码
	Minphone[0] = '\0';
	for (int i = 0; i < H->tableSize; i++)//扫描整个链表
	{
		ptr = H->Heads[i].next;
		while (ptr != NULL)   //扫描某个头结点的链表
		{
			if (ptr->count > Maxcnt) {   //如果通话次数更大
				Maxcnt = ptr->count;
				strcpy(Minphone, ptr->data);  //更新号码
				Pcnt = 1;
			}
			else if (ptr->count == Maxcnt) {
				Pcnt++;
				if (strcmp(Minphone, ptr->data) > 0) {  //如果新号码更小，更新号码
					strcpy(Minphone, ptr->data);
				}
			}
			ptr = ptr->next;
		}
	}
	cout << Minphone << " " << Maxcnt;
	if (Pcnt > 1) cout << " " << Pcnt;
	cout << endl;
}
int main()
{
	int N, i;
	cin >> N;
	phoneNumber key;
	HashTable H = createTable(N * 2);   //号码最大条数为通话记录条数*2
	for (i = 0; i < N; i++) {
		cin >> key; Insert(H, key);
		cin >> key; Insert(H, key);
	}
	ScanAndPrint(H);
	delete H;
}
