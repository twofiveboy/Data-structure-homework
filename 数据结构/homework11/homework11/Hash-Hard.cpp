#include"pch.h"
#include <iostream>
#include<queue>
#include<vector>
#include<string.h>
#define maxTableSize 1001
#define infinity 65535
//�����������˼����,reference:https://blog.csdn.net/qq_42068614/article/details/85911268
using namespace std;
int N;
int* A,*Indegree;
int **E;
void Topsort() {  
	queue<int>Q;
	int *Visited = new int[N];
	memset(Visited, 0, N*sizeof(int));
	for (int i = 0; i < N; i++)   //���ν�Indegree==0����С����ӣ�������Indegree
	{
		int min = infinity, current = -1;
		for (int j = 0; j < N; j++)    //������Ѱ�� ��С��0��Ƚ��
		{
			if (A[j] < 0) continue;
			if (Visited[j] == 0 && Indegree[j] == 0) {  //���Ϊ0��û�б���¼��
				if (A[j] < min) {
					min = A[j];
					current = j;
				}
			}
		}
		if (current == -1) break; //�ϸ�ѭ����,û���ҵ��κ�һ�����������Ľ�㣬�ս�ѭ��
		Visited[current] = 1; //����Visited
		Q.push(A[current]);   //��������
		for (int v = 0; v < N; v++) //����current������V�� Indegree ��
		{
			if (Visited[v] == 0 && E[current][v] == 1) {  //vû��������c��v�б�
				E[current][v] = 0;  //ɾ����
				Indegree[v]--;     //�������
			}
		}
	}
		//���ģ��
	cout << Q.front();
	Q.pop();
	while (!Q.empty()){
			cout << " " << Q.front();
			Q.pop();
	}
	
}
int main() {
	cin >> N;
	int i;
	A = new int[N];     //���ɢ�б�
	Indegree = new int[N];
	for (i = 0; i < N; i++)
	{
		cin >> A[i];
	}
	E = new int*[N];
	for (int i = 0; i < N; i++) {
		E[i] = new int[N];
		for (int j = 0; j < N; j++) {
			E[i][j] = infinity;    //ȫ����ʼ��Ϊ����,����֮�����
		}
	}
	for (i = 0; i < N; i++) {
		if (A[i] < 0) continue;
		int firstpos = A[i] % N;
		if (firstpos == i) Indegree[i] = 0;
		else {
			Indegree[i] = (i - firstpos + N) % N;  //i��firstpos���ܿ�Խһ�����ڹ�-N ��%N ��0-10 %11=1��
			for (int j = 0; j < Indegree[i]; j++)
			{
				E[(firstpos + j) % N][i] = 1;   //����i����֮ǰ(��֮��)��firstpos �� i(���ܿ�Խһ������) ���� Indegree[i]����¼��
			}
		}
	}
	Topsort();
	delete[]A, Indegree, E;
	return 0;
}