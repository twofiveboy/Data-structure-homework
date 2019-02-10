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
	int MinV;//dist��С���е��±�
	int MinDist = infinity;//��С�����ʼ��Ϊ�����
	for (int i = 0; i < N; i++) {          
		if (!collected[i] && dist[i] < MinDist) {    //��δ����¼����dist[i]��С
			MinDist = dist[i];
			MinV = i;
		}
	}
	if (MinDist == infinity) return false;  //û�ҵ�
	else return MinV;
}
void Dijkstra(int s) { //s�����������
	int collected[maxsize];
	//��ʼ��dist,cost,collected:
	for (int i = 0; i < N; i++) {
		dist[i] = city[s][i].distance;    //��ʼ�㵽�õ����
		cost[i] = city[s][i].cost;
		if (dist[i] < infinity) path[i] = s; //����ʼ����ͨ
		else path[i] = -1;
		collected[i] = false;
	}
	//��¼��ʼ��,���Լ�����Ϊ0
	dist[s] = 0;
	collected[s] = true;
	int V,W;   
	while (1) {
		V = FindMin(collected);//��dist��С�ĳ���
		if (!V) {               //û���ҵ�,�Ѿ�����㷨������
			break;
		}
		collected[V] = true;
		for (W = 0; W < N; W++) {  //����ÿ������
			if (!collected[W] && city[V][W].distance < infinity)//Wδ����¼����V���ڽӵ�
			{
				if(city[V][W].distance<0) { //����Ϊ�������ش���
					cout << "error";
					return;
				}
				if (dist[V] + city[V][W].distance < dist[W]) { //����¼Vʹ��dist[W]��С�������W��dist
					dist[W] = dist[V] + city[V][W].distance;
					cost[W] = cost[V] + city[V][W].cost;
					path[W] = V; //W·��ǰһ��������ΪV
				}
				//����¼��dist[W]���䵫cost���٣�Ҳ����
				else if (dist[V] + city[V][W].distance == dist[W]&& cost[V] + city[V][W].cost<cost[W]) {
					cost[W] = cost[V] + city[V][W].cost;
					path[W] = V; //W·��ǰһ��������ΪV
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