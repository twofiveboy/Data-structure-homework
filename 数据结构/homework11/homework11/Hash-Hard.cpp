#include"pch.h"
#include <iostream>
#include<queue>
#include<vector>
#include<string.h>
#define maxTableSize 1001
#define infinity 65535
//用拓扑排序的思想解决,reference:https://blog.csdn.net/qq_42068614/article/details/85911268
using namespace std;
int N;
int* A,*Indegree;
int **E;
void Topsort() {  
	queue<int>Q;
	int *Visited = new int[N];
	memset(Visited, 0, N*sizeof(int));
	for (int i = 0; i < N; i++)   //依次将Indegree==0的最小点入队，并更新Indegree
	{
		int min = infinity, current = -1;
		for (int j = 0; j < N; j++)    //遍历并寻找 最小的0入度结点
		{
			if (A[j] < 0) continue;
			if (Visited[j] == 0 && Indegree[j] == 0) {  //入度为0且没有被收录过
				if (A[j] < min) {
					min = A[j];
					current = j;
				}
			}
		}
		if (current == -1) break; //上个循环中,没有找到任何一个满足条件的结点，终结循环
		Visited[current] = 1; //更新Visited
		Q.push(A[current]);   //将结点入队
		for (int v = 0; v < N; v++) //将与current相连的V的 Indegree 和
		{
			if (Visited[v] == 0 && E[current][v] == 1) {  //v没被访问且c和v有边
				E[current][v] = 0;  //删除边
				Indegree[v]--;     //更新入度
			}
		}
	}
		//输出模块
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
	A = new int[N];     //存放散列表
	Indegree = new int[N];
	for (i = 0; i < N; i++)
	{
		cin >> A[i];
	}
	E = new int*[N];
	for (int i = 0; i < N; i++) {
		E[i] = new int[N];
		for (int j = 0; j < N; j++) {
			E[i][j] = infinity;    //全部初始化为无穷,方便之后计算
		}
	}
	for (i = 0; i < N; i++) {
		if (A[i] < 0) continue;
		int firstpos = A[i] % N;
		if (firstpos == i) Indegree[i] = 0;
		else {
			Indegree[i] = (i - firstpos + N) % N;  //i与firstpos可能跨越一个周期故-N 再%N （0-10 %11=1）
			for (int j = 0; j < Indegree[i]; j++)
			{
				E[(firstpos + j) % N][i] = 1;   //将第i个点之前(或之后)从firstpos 到 i(可能跨越一个周期) 共计 Indegree[i]个边录入
			}
		}
	}
	Topsort();
	delete[]A, Indegree, E;
	return 0;
}