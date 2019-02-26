#include"pch.h"
#include <iostream>
#include<cstdlib> //atoi
#include<cstring>//strcmp
#include<string.h>
#define maxTableSize 100000
using namespace std;
//初始构造模块
typedef char qqNumber[11];//字符串结尾有个"/0"占位置
typedef char passwordNumber[17];
typedef struct userNode* PtrNode;
struct userNode {
	qqNumber data;
	passwordNumber password; //该号码进行过的通话次数
	PtrNode next;
};
typedef struct TableNode {
	int tableSize;
	PtrNode Heads;
}*HashTable;
int nextPrime(int n) {
	while (1) {
		bool flag = true;
		for (int i = 2; i < n; i++) {
			if (n % i == 0) {
				flag = false;
				break;
			}
		}
		if (flag) break;
		n++;
	}
	return n;
}
HashTable createTable(int tablesize) {
	HashTable H = new TableNode;
	H->tableSize = nextPrime(tablesize);
	H->Heads = new userNode[tablesize];
	for (int i = 0; i < H->tableSize; i++)
	{
		H->Heads[i].next = NULL;
		H->Heads[i].data[0] = '\0';
		H->Heads[i].password[0] = '\0';
	}
	return H;
}
int Hash(int key, int tableSize) {   //哈希构造函数：除留余数法  
	return key % tableSize;
}
typedef PtrNode Position;
Position Find(HashTable H,qqNumber key) {
	Position p;
	int pos;   //取后7位作为散列地址（后5，6位运行超时，且会错误）7位（400ms）以后（8，9，10）速度相差不大（比7快20ms），取前5位大概650ms左右
	pos = Hash(atoi(key + 11 - 7), H->tableSize);
	p = H->Heads[pos].next;
	while (p != NULL && strcmp(p->data, key)) {   //相同strcmp 返回0
		p = p->next;
	}
	return p; //返回NULL或指向的结点
}
bool Insert(HashTable H,qqNumber key, passwordNumber password) {
	int pos;
	Position P = Find(H, key);
	if (!P) {
		Position newuser = new userNode;
		strcpy_s(newuser->password,password);
		strcpy_s(newuser->data,key);
		pos = Hash(atoi(key + 11 - 7), H->tableSize);
		newuser->next = H->Heads[pos].next;
		H->Heads[pos].next = newuser;
		return true;
	}
	else {
		return false; //已经存在，返回错误标记
	}
	
}
int main() {
	int N;
	cin >> N;
	HashTable H = createTable(N);
	char op, password[20], qqnum[20];
	for (int i = 0; i < N; i++)
	{
		cin >> op; //输入操作符
		cin >> qqnum>>password;
		if (op == 'N') {
			PtrNode p = Find(H, qqnum);
			if (p != NULL)  cout << "ERROR: Exist" << endl;
			else {
				Insert(H, qqnum,password);
				cout << "New: OK" << endl;
			}
		}
		else if (op == 'L') {
			PtrNode p = Find(H, qqnum);
			if (p == NULL) cout << "ERROR: Not Exist" << endl;
			else if (strcmp(p->password, password)) cout << "ERROR: Wrong PW" << endl;
			else   cout << "Login: OK" << endl;
		}
	}
	delete H;
	return 0;
}