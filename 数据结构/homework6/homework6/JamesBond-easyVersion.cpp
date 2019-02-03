#include "pch.h"
#include<string.h>
#include<cmath>
#include <iostream>
#include<vector>
//reference：https://blog.csdn.net/qq_42068614/article/details/85621562
using namespace std;
int N;
double D;
bool answer;
struct location {
	double x;
	double y;
	bool Visited;       //代表某个结点是否被访问过，默认为0
};
vector<location>Crocodiles;
bool firstJump(int v) {
	double r = pow(Crocodiles[v].x,2) + pow(Crocodiles[v].y, 2);
	double maxjump = pow((7.5 + D),2);
	if (r <= maxjump) return true;
	else return false;
}
bool isSafe(int v) {
	return(50 - abs(Crocodiles[v].x) <= D || 50 - abs(Crocodiles[v].y) <= D);
}
bool jump(int v, int w) {   //能否跳跃
	double distance = pow(Crocodiles[v].x - Crocodiles[w].x, 2) + pow(Crocodiles[v].y - Crocodiles[w].y, 2);
	return distance <= D*D;
}
bool DFS(int v){
	Crocodiles[v].Visited = 1;
	if (isSafe(v)) answer = 1;
	else {
		for (int i = 0; i < N; i++) {
			if (!Crocodiles[i].Visited&&jump(v, i)) {   //DFS还要加条件，是否能跳到
				DFS(i);
				if (answer) break;
			}
		}
	}
	return answer;
}

int main() {
	int i=0;
	cin >> N >> D;
	Crocodiles.resize(N);
	while (i < N) {
		cin >> Crocodiles[i].x;
		cin >> Crocodiles[i].y;
		Crocodiles[i].Visited = 0;
		i++;
	}
	for (int i = 0; i < N; i++) {
		if (!Crocodiles[i].Visited&&firstJump(i)) {  //第一跳要做特殊处理
			DFS(i);
			if (answer) break;
		}
	}
	if (answer) cout << "Yes";
	else cout << "No";
	Crocodiles.clear();
	
	return 0;
}