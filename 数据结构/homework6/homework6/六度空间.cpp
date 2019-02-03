#include "pch.h"
#include <iostream>
#include<vector>
#include<string.h>
#include<iomanip> //格式化输入输出
#include<queue>   //虽然邻接表更节省空间，但是BFS不仅要遍历出度，还要遍历入度，实现麻烦，所以仍用邻接矩阵存储
//reference代码主体：https://blog.csdn.net/priestessofbirth/article/details/78274933
//其他方式创建vector二维数组：https://blog.csdn.net/u011361880/article/details/77726316
//reference遍历：https://blog.csdn.net/ls306196689/article/details/35787955
//https://blog.csdn.net/liunian17/article/details/7435781
using namespace std;
int N, M;
vector<int>people[10001];
int Visited[10001];
int BFS(int v) {
	memset(Visited, 0, sizeof(Visited));
	int count = 1; queue<int>Q; int level = 0;//层数,初始为0
	int last = v;//本层最后一个结点
	int tail=1;//下层最后一个结点
	Visited[v] = 1;
	Q.push(v);
	
	while (!Q.empty()) {
		
		v = Q.front();
		Q.pop();
		for (size_t i = 0; i < people[v].size(); i++) { //size_t是一种“整型”类型，里面保存的是一个整数，就像int, long那样。这种整数用来记录一个大小(size)。size_t的全称应该是size type，就是说“一种用来记录大小的数据类型”。
			int w = people[v][i];  
			if (!Visited[w]) {
				Visited[w] = 1;
				Q.push(w);
				count++;
				tail = w;
			}
		}
			if (v == last) {
				level++; last = tail;
		}
			if (level == 6) break;
		
		
	}

	return count;
}
int main() {
	cin >> N >> M;
	
	for (int i = 0; i < M; i++) {
		int a,b;
		cin >> a >> b;
		people[a].push_back(b);
		people[b].push_back(a);    //注意people[0]中不存储数据
	}

	for (int i = 1; i <= N; i++) {
		int count = BFS(i);
		cout << i  << ": "<<fixed<<setprecision(2) << (float)(100.0*(count*1.0) / (N*1.0)) << "%" << endl;
	}
	return 0;
}