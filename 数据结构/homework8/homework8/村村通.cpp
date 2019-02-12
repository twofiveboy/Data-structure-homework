#include "pch.h"
#include <iostream>
#define infinity 65535
#define maxsize 1000
using namespace std;
int N, M;
int dist[maxsize], parent[maxsize];   //注意不同的是：dist代表结点到MST的最小距离
int** city;
int FindMin() {
	int MinV;//dist最小城市的下标
	int MinDist = infinity;//最小距离初始化为无穷大
	for (int i = 0; i < N; i++) {
		if (dist[i]!=0 && dist[i] < MinDist) {    //若未被收录，且dist[i]更小
			MinDist = dist[i];
			MinV = i;
		}
	}
	if (MinDist == infinity) return -1;  //没找到
	else return MinV;
}
int Prim() {//默认0为树根结点,即起始点    //与Dijkstra算法区别，dist意义不同，且若要建MST要增加收录模块
	int Vcount = 0;   //统计收录的顶点
	int totalWeight = 0; //总权重
	//初始化dist,cost,collected:
	for (int i = 0; i < N; i++) {
		dist[i] = city[0][i];    //dist初始化为起始点到该点距离
		parent[i] = 0;       //暂定所有节点的父节点都是起始点0

	}
	//收录起始点,到自己距离为0
	dist[0] = 0; Vcount++; parent[0] = -1; 
	int V, W;
	while (1) {
		V = FindMin();//找dist最小的城市
		if (V==-1) {               //没有找到,已经完成算法，返回
			break;
		}
		//此处可以增加收录V进入MST的模块，但本题只要求权重，所以忽略
		totalWeight += dist[V];
		dist[V] = 0;
		Vcount++;
		for (W = 0; W < N; W++) {  //遍历每个顶点
			if (dist[W]!=0 && city[V][W] < infinity)//W未被收录(即dist不为0)且是V的邻接点
			{
				if (city[V][W] < 0) { //距离为负数返回错误
					cout << "error";
					return -1;
				}
				if (city[V][W] < dist[W]) { //若收录V使得dist[W]变小，则更新W的dist,
					dist[W] = city[V][W];  //注意此处直接用边权重更新dist，因为dist是到MST的距离
					parent[W] = V;              //W父亲结点更新为V
				}
			}
		}
	}
	
	if (Vcount != N) totalWeight = -1;
	return totalWeight;
}

int main()
{
	cin >> N >> M;
	city = new int*[N];
	for (int i = 0; i < N; i++) {
		city[i] = new int[N];
		for (int j = 0; j < N; j++) {
			city[i][j] = infinity;    //初始化为无穷
		}
		city[i][i] = 0;   //对角线为0
	}
	for (int k = 0; k < M; k++) {  //记录各个城镇距离
		int i, j, distance;
		cin >> i >> j >> distance;
		i--; j--;     //输入城市从1开始
		city[i][j] = distance;
		city[j][i] = distance;
	}
	int totalweight = Prim();
	cout << totalweight;
	free(city);
	return 0;
}

