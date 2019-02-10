#include "pch.h"
#include <iostream>
#include<vector>
#define maxsize 500
#define infinity 65535
using namespace std;
int N, M, S, D;
int dist[maxsize], path[maxsize], cost[maxsize];
struct Node {
	int distance;
	int cost;
};
Node ** city;
int FindMin(int collected[]) {
	int MinV;//dist最小城市的下标
	int MinDist = infinity;//最小距离初始化为无穷大
	for (int i = 0; i < N; i++) {          
		if (!collected[i] && dist[i] < MinDist) {    //若未被收录，且dist[i]更小
			MinDist = dist[i];
			MinV = i;
		}
	}
	if (MinDist == infinity) return false;  //没找到
	else return MinV;
}
void Dijkstra(int s) { //s代表出发顶点
	int collected[maxsize];
	//初始化dist,cost,collected:
	for (int i = 0; i < N; i++) {
		dist[i] = city[s][i].distance;    //起始点到该点距离
		cost[i] = city[s][i].cost;
		if (dist[i] < infinity) path[i] = s; //与起始点连通
		else path[i] = -1;
		collected[i] = false;
	}
	//收录起始点,到自己距离为0
	dist[s] = 0;
	collected[s] = true;
	int V,W;   
	while (1) {
		V = FindMin(collected);//找dist最小的城市
		if (!V) {               //没有找到,已经完成算法，返回
			break;
		}
		collected[V] = true;
		for (W = 0; W < N; W++) {  //遍历每个顶点
			if (!collected[W] && city[V][W].distance < infinity)//W未被收录且是V的邻接点
			{
				if(city[V][W].distance<0) { //距离为负数返回错误
					cout << "error";
					return;
				}
				if (dist[V] + city[V][W].distance < dist[W]) { //若收录V使得dist[W]变小，则更新W的dist
					dist[W] = dist[V] + city[V][W].distance;
					cost[W] = cost[V] + city[V][W].cost;
					path[W] = V; //W路径前一个结点更新为V
				}
				//若收录后dist[W]不变但cost减少，也更新
				else if (dist[V] + city[V][W].distance == dist[W]&& cost[V] + city[V][W].cost<cost[W]) {
					cost[W] = cost[V] + city[V][W].cost;
					path[W] = V; //W路径前一个结点更新为V
				}
			}
		}
	}

	

}
int main() {
	
	cin >> N>>M>>S>>D;
	city = new Node*[N];
	for (int i = 0; i < N; i++) {
		city[i] = new Node[N];
		for (int j = 0; j < N; j++) {
			city[i][j].distance = infinity;
			city[i][j].cost = infinity;
		}
	}
	
	for (int k = 0; k < M; k++) {
		int i, j, distance, cost;
		cin >> i >> j>>distance>>cost;
		city[i][j].distance = distance;
		city[i][j].cost = cost;
		city[j][i].distance = distance;
		city[j][i].cost = cost;
	}
	Dijkstra(S);
	cout << dist[D] << " " << cost[D];
	free(city);
	return 0;
}