#include "pch.h"
#include<queue>
#include <iostream>
#include<algorithm>  //max_element所需头文件
//reference：https://blog.csdn.net/yeternity/article/details/71075571
#define infinity 65535
#define maxsize 100
using namespace std;
int N, M;
int **A;//activity
int TopSort() {
	int Indegree[maxsize] = {0}; //入度
	int Earliest[maxsize] = {0}; //各环节最早完成时间
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
	int V,cnt=0; //cnt为计数器，统计已记录的环节数
	while (!Q.empty()){     //队列为空终止
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
		A[i][j] = time;
	}
	int EarliestTime = TopSort();
	if (!EarliestTime) cout << "Impossible";
	else cout << EarliestTime;
	free(A);
	return 0;
}