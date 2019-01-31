#include "pch.h"
#include <iostream>
#include<string.h>
#include<queue>
using namespace std;

int Visited[10] = {0};//代表某个结点是否被访问过，默认为0
int N, E;
int G[55] = {0};
void DFS(int V) {   //vertex v，
	Visited[V] = 1;
	for (int i = 0 ; i < N; i++) {    
		if (i < V) {         //按行搜寻邻接点并DFS
			if (Visited[i] == 0 && G[V*(V + 1) / 2 + i] == 1) {
				cout << i << " ";
				DFS(i);
			}
		}
		else {               //按列搜寻邻接点并DFS，如果是二维数组只需用列搜寻即可
			if (Visited[i] == 0 && G[i*(i + 1) / 2 + V] == 1) {  //i*(i + 1) / 2 + V是G中的下标
				cout << i << " ";
				DFS(i);
			}
		}

	}
}
void BFS(int V) {
	queue<int> Q;
	Visited[V] = 1;
	Q.push(V);
	while (!Q.empty()) {
		V = Q.front();
		Q.pop();
		for (int i = 0; i < N; i++) {
			if (i < V) {         //按行搜寻邻接点并压栈
				if (Visited[i] == 0 && G[V*(V + 1) / 2 + i] == 1) {
					Visited[i] = 1;
					cout << i << " ";
					Q.push(i);
				}
			}
			else {               //按列搜寻邻接点并压栈，如果是二维数组只需用列搜寻即可
				if (Visited[i] == 0 && G[i*(i + 1) / 2 + V] == 1) {  //i*(i + 1) / 2 + V是G中的下标
					Visited[i] = 1;
					cout << i << " ";
					Q.push(i);
				}
			}

		}

	}
}
int main()
{      
	int i,j,k=0;
	cin >> N >> E;
	for (k = 0; k < E; k++) {
		cin >> i >> j;
		i > j ? G[i*(i + 1) / 2 + j] = 1 : G[j*(j + 1) / 2 + i]=1;   
	}
	for (int i = 0; i < N; i++) {
		if (!Visited[i]) { 
			cout << "{ ";
			cout <<i;
			cout<< " ";
			DFS(i); 
			cout << "}" << endl;
		}
	}
	memset(Visited, 0, sizeof(Visited)); //重制Visited值
	 //对数组a[]进行初始化时，表达式memset(a,0,size)中的size指的是数组所占内存的大小
     //而不是数组中元素的个数
	for (int i = 0; i < N; i++) {
		if (!Visited[i]) {
			cout << "{ ";
			cout << i;
			cout << " ";
			BFS(i);
			cout << "}" << endl;
		}
	}
	return 0;  
}
/*delete(Visited);*/
/*int *G = new int[N];
	while (k < N*(N+1)/2) {
		G[k] = 0;
		k++;
	}*/