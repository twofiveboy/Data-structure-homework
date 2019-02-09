#include "pch.h"
#include <iostream>
#include<cstring>    //memcpy所需头文件
#define infinity 65535
#define maxsize 100
using namespace std;
int N, M;
struct GNode {
	int Nv; //边数
	int Ne;//顶点数
	int G[maxsize][maxsize];
};
class MGraph
{
public:
	MGraph(int N) ;
	void InsertMerge(int i, int j, int weight);
	void CreateGraph(int M);
	void FindAnimal();
private:
	int Nv; //边数
	int Ne;//顶点数
	int G[maxsize][maxsize];
	int D[maxsize][maxsize];
	void Floyd();
	int FindMaxDist(int i); //在第i行搜寻最大值
};

MGraph::MGraph(int N)
{
	Nv = N;
	Ne = 0;
	for (int i = 0; i < Nv; i++) {
		for (int j = 0; j < Nv; j++) {
			G[i][j] = infinity;
		}
	}
	for (int i = 0; i < Nv; i++) {
             G[i][i] = 0;	
	}
}

void MGraph::InsertMerge(int i, int j, int weight)
{
	G[i][j] = weight;
	G[j][i] = weight;
}

void MGraph::CreateGraph(int M)
{
	Ne = M;
	if (Ne != 0) {
		int i, j,weight;
		for (int k = 0; k < Ne; k++) {
			cin >> i >> j>>weight;
			i--; j--;//动物编号从1开始
			InsertMerge(i, j, weight);
		}
	}
}

void MGraph::FindAnimal()
{
	int MaxDist, MinDist = infinity;
	int animal;
	Floyd();
	for (int i = 0; i < Nv; i++) {
		MaxDist = FindMaxDist(i);
		if (MaxDist == infinity) {
			cout << "0" << endl;
			return;
		}
		if (MaxDist < MinDist) {
			MinDist = MaxDist;
			animal = i + 1;    //矩阵下标从0开始，动物从1开始
		}
	}
	cout << animal << " " << MinDist;
}

void MGraph::Floyd()
{
	int i, j, k;
	memcpy(D, G, sizeof(G)); //将D初始化为G
	for (k = 0; k < Nv; k++) {
		for (i = 0; i < Nv; i++) {
			for (j = 0; j < Nv; j++) {
				if (D[i][j] > D[i][k] + D[k][j]) {
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
	return;
}

int MGraph::FindMaxDist(int i)
{
	int maxDist=0;
	for (int j = 0; j < Nv; j++) {
		if (D[i][j] > maxDist) maxDist = D[i][j];
	}
	return maxDist;
}

int main()
{
	cin >> N >> M;
	MGraph G(N);
	G.CreateGraph(M);
	G.FindAnimal();
	
	return 0;
}
