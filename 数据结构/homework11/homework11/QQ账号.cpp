#include"pch.h"
#include <iostream>
#include<cstdlib> //atoi
#include<cstring>//strcmp
#include<string.h>
#define maxTableSize 100000
using namespace std;
//��ʼ����ģ��
typedef char qqNumber[11];//�ַ�����β�и�"/0"ռλ��
typedef char passwordNumber[17];
typedef struct userNode* PtrNode;
struct userNode {
	qqNumber data;
	passwordNumber password; //�ú�����й���ͨ������
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
int Hash(int key, int tableSize) {   //��ϣ���캯��������������  
	return key % tableSize;
}
typedef PtrNode Position;
Position Find(HashTable H,qqNumber key) {
	Position p;
	int pos;   //ȡ��7λ��Ϊɢ�е�ַ����5��6λ���г�ʱ���һ����7λ��400ms���Ժ�8��9��10���ٶ����󣨱�7��20ms����ȡǰ5λ���650ms����
	pos = Hash(atoi(key + 11 - 7), H->tableSize);
	p = H->Heads[pos].next;
	while (p != NULL && strcmp(p->data, key)) {   //��ͬstrcmp ����0
		p = p->next;
	}
	return p; //����NULL��ָ��Ľ��
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
		return false; //�Ѿ����ڣ����ش�����
	}
	
}
int main() {
	int N;
	cin >> N;
	HashTable H = createTable(N);
	char op, password[20], qqnum[20];
	for (int i = 0; i < N; i++)
	{
		cin >> op; //���������
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