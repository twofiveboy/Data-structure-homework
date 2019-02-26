#include"pch.h"
#include<math.h>
#include <iostream>
#define maxTableSize 10001
using namespace std;
//其实并不需要真的HashTable，只需要一个数组flag[nextPrime(M)]记录单元是否被存放即可
typedef enum { Legitimate, Empty} EntryType;
typedef struct pNode {
	int data;
	EntryType Info;//单元状态
}*PtrNode;

typedef struct TableNode {
	int tableSize;  //表长度
	PtrNode Cells;  //存放头节点的数组
}*HashTable;
//初始构造模块
bool isPrime(int N) {
	if (	N <= 1) return 0;
	for (int i = 2; i <= sqrt(N); i++)
		if (N%i == 0)return 0;
	return 1;
}
int nextPrime(int N) {    //返回一个比N大且小于maxTableSize的质数
	int  p = N;
	while (!isPrime(p)) p++;
	return p;
	
}
HashTable createTable(int tablesize) {
    HashTable H=new TableNode;
	H->tableSize = nextPrime(tablesize);
	H->Cells = new pNode[H->tableSize];
	for (int i = 0; i < H->tableSize; i++)
	{
		H->Cells[i].Info = Empty;
	}
	return H;
}
//插入模块
int Hash(int key, int tableSize) {   //哈希构造函数：除留余数法
	return key % tableSize;
}
typedef int Position;
Position Find(HashTable H, int key) {
	Position NewP,CurrentP;
	int Cnum=0;//冲突次数
	bool judge = 0;
	NewP = CurrentP  = Hash(key, H->tableSize);
	while (Cnum<H->tableSize) { //一直到Cnum等于size为止
		//只做正向增加的平方检测
		NewP = CurrentP + Cnum * Cnum;
		if (NewP >= H->tableSize)  NewP = NewP % H->tableSize;
		if (H->Cells[NewP].Info == Empty) {  //单元未被占
			H->Cells[NewP].Info = Legitimate;
			H->Cells[NewP].data = key;
			judge = 1;
			break;
		}
		Cnum++;
	}
	if (judge == 0)return -1;
	return NewP;
}

int main() {
	int M, N, key,pos;
	cin >> M >> N;
	HashTable H = createTable(M);
	for (int i = 0; i < N; i++)
	{
		cin >> key;
		pos = Find(H, key);
		if (i == 0) pos >= 0 ? cout << pos : cout << "-";
		else  pos >= 0 ? cout << " " << pos : cout << " " << "-";
	}
	delete H;
}
//bool Insert(HashTable H, int key) {
//	Position pos = Find(H,key);
//	if (pos == -1) return false;
//	else if (H->Cells[pos].Info != Legitimate) {  //单元未被占
//		H->Cells[pos].Info = Legitimate;
//		H->Cells[pos].data = key;
//		return true;
//	}
//	else return false;
//	
//}