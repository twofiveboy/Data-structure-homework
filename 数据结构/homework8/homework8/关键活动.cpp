#include "pch.h"
#include<queue>
#include <iostream>
#include<algorithm>  //max_element所需头文件
#define infinity 65535
#define maxsize 100
using namespace std;
int N, M;
int **A;//activity
int Earliest[maxsize] = { 0 }; //各环节最早完成时间
int Latest[maxsize];
int TopSort() {
	int Indegree[maxsize] = { 0 }; //入度
	
	queue<int>Q;
	//初始化各环节入度，每有一个A[i][j]!=infinity,Indegree[j]+1
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (A[i][j] != infinity) {
				Indegree[j]++;
			}
		}
	}
	//正式开始算法，先将所有入度为0的入队
	for (int i = 0; i < N; i++) {
		if (!Indegree[i]) Q.push(i);
	}
	int V, cnt = 0; //cnt为计数器，统计已记录的环节数
	while (!Q.empty()) {     //队列为空终止
		V = Q.front();
		Q.pop();
		cnt++;
		for (int j = 0; j < N; j++) {
			if (A[V][j] != infinity) {  //V与j是邻接的，存在边
				if (Earliest[V] + A[V][j] > Earliest[j]) {    //寻找E+边权重 最大值作为j环节最早开始时间
					Earliest[j] = Earliest[V] + A[V][j];
				}
				if (--Indegree[j] == 0) {  //去掉V后j入度为0，则入队
					Q.push(j);
				}

			}
		}
	}
	int EarliestTime = *max_element(Earliest, Earliest + N);//项目最早完成时间是所有环节最早完成时间中最大值（即最后一个环节的最早完成时间）
	if (cnt != N) return 0;     //未全部收录，有回路存在
	else return EarliestTime;
}
void FindMin(int x) {
	for (int i = 0; i < N; i++) {
		Latest[i] = x;
	}
	//memset(Latest, 17, sizeof(Latest)); 不可用memset初始化非零数组https://blog.csdn.net/melody_1016/article/details/83479778
	int Outdegree[maxsize] = { 0 }; //出度
	queue<int>Q;  //类似反向执行TopSort算法,以出度代替入度
	//初始化各环节入度，每有一个A[i][j]!=infinity,Indegree[j]+1
	for (int i = N-1; i >= 0; i--) {
		for (int j = N-1; j >=0; j--) {
			if (A[j][i] != infinity) {    //i与j是邻接的
				Outdegree[j]++;
			}
		}
	}
	//正式开始算法，先将所有入度为0的入队
	for (int i = N-1; i >=0; i--) {
		if (!Outdegree[i]) Q.push(i);
	}
	int V; //无需计数器，TopSort中已经验证无回路
	while (!Q.empty()) {     //队列为空终止
		V = Q.front();
		Q.pop();
		for (int j = N-1; j >= 0; j--) {
			if (A[j][V] != infinity) {  //V与j是邻接的，存在边
				if (Latest[V] - A[j][V] < Latest[j]) {    //寻找L-边权重 最小值作为j环节最早开始时间
					Latest[j] = Latest[V] - A[j][V];
				}
				if (--Outdegree[j] == 0) {  //去掉V后j入度为0，则入队
					Q.push(j);
				}
			}
		}
	}
	return;
}
void printKey() {
	for (int i = 0; i < N; i++) {
		if (Earliest[i] != Latest[i]) continue;   //E=L即i是关键结点,否则跳过
		for (int j = N - 1; j >= 0; j--) {              //为完成题目要求同起始节点反序输出收录结点，循环翻转
			if (Latest[j]==Earliest[i]+A[i][j] && Earliest[j] == Latest[j])//j是关键结点，且i,j直接连接
				cout << i + 1 << "->" << j + 1 << endl;
		}
	}
}
int main() {
	cin >> N >> M;
	A = new int*[N];
	for (int i = 0; i < N; i++) {
		A[i] = new int[N];
		for (int j = 0; j < N; j++) {
			A[i][j] = infinity;    //全部初始化为无穷,方便之后计算
		}
	}
	for (int k = 0; k < M; k++) {  //记录各个环节之间时间
		int i, j, time;
	
		cin >> i >> j >> time;
			i--; j--;      //编号从1开始
		A[i][j] = time;
	}
	int EarliestTime = TopSort();
	if (!EarliestTime) cout << "0";
	else { 
		FindMin(EarliestTime);
		cout << EarliestTime << endl; 
		printKey();
	}
	free(A);
	return 0;
}