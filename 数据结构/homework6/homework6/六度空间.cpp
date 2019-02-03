#include "pch.h"
#include <iostream>
#include<vector>
#include<string.h>
#include<iomanip> //��ʽ���������
#include<queue>   //��Ȼ�ڽӱ����ʡ�ռ䣬����BFS����Ҫ�������ȣ���Ҫ������ȣ�ʵ���鷳�����������ڽӾ���洢
//reference�������壺https://blog.csdn.net/priestessofbirth/article/details/78274933
//������ʽ����vector��ά���飺https://blog.csdn.net/u011361880/article/details/77726316
//reference������https://blog.csdn.net/ls306196689/article/details/35787955
//https://blog.csdn.net/liunian17/article/details/7435781
using namespace std;
int N, M;
vector<int>people[10001];
int Visited[10001];
int BFS(int v) {
	memset(Visited, 0, sizeof(Visited));
	int count = 1; queue<int>Q; int level = 0;//����,��ʼΪ0
	int last = v;//�������һ�����
	int tail=1;//�²����һ�����
	Visited[v] = 1;
	Q.push(v);
	
	while (!Q.empty()) {
		
		v = Q.front();
		Q.pop();
		for (size_t i = 0; i < people[v].size(); i++) { //size_t��һ�֡����͡����ͣ����汣�����һ������������int, long��������������������¼һ����С(size)��size_t��ȫ��Ӧ����size type������˵��һ��������¼��С���������͡���
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
		people[b].push_back(a);    //ע��people[0]�в��洢����
	}

	for (int i = 1; i <= N; i++) {
		int count = BFS(i);
		cout << i  << ": "<<fixed<<setprecision(2) << (float)(100.0*(count*1.0) / (N*1.0)) << "%" << endl;
	}
	return 0;
}