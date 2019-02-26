#include"pch.h"
#include<math.h>
#include <iostream>
#define maxTableSize 10001
using namespace std;
//��ʵ������Ҫ���HashTable��ֻ��Ҫһ������flag[nextPrime(M)]��¼��Ԫ�Ƿ񱻴�ż���
typedef enum { Legitimate, Empty} EntryType;
typedef struct pNode {
	int data;
	EntryType Info;//��Ԫ״̬
}*PtrNode;

typedef struct TableNode {
	int tableSize;  //����
	PtrNode Cells;  //���ͷ�ڵ������
}*HashTable;
//��ʼ����ģ��
bool isPrime(int N) {
	if (	N <= 1) return 0;
	for (int i = 2; i <= sqrt(N); i++)
		if (N%i == 0)return 0;
	return 1;
}
int nextPrime(int N) {    //����һ����N����С��maxTableSize������
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
//����ģ��
int Hash(int key, int tableSize) {   //��ϣ���캯��������������
	return key % tableSize;
}
typedef int Position;
Position Find(HashTable H, int key) {
	Position NewP,CurrentP;
	int Cnum=0;//��ͻ����
	bool judge = 0;
	NewP = CurrentP  = Hash(key, H->tableSize);
	while (Cnum<H->tableSize) { //һֱ��Cnum����sizeΪֹ
		//ֻ���������ӵ�ƽ�����
		NewP = CurrentP + Cnum * Cnum;
		if (NewP >= H->tableSize)  NewP = NewP % H->tableSize;
		if (H->Cells[NewP].Info == Empty) {  //��Ԫδ��ռ
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
//	else if (H->Cells[pos].Info != Legitimate) {  //��Ԫδ��ռ
//		H->Cells[pos].Info = Legitimate;
//		H->Cells[pos].data = key;
//		return true;
//	}
//	else return false;
//	
//}