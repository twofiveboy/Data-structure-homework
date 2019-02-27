#include "pch.h"
#include<stack>
#include<queue>
#include<algorithm>  //sort函数reference:https://www.cnblogs.com/jjzzx/p/5122381.html
#include<cstring>
#include<cmath>
#include <iostream>
#include<vector>
//reference：http://www.cnblogs.com/minesweeper/p/5954733.html
using namespace std;
int N;
double D;
bool answer;
int path[101] = { -1 };                 //007跳跃路径
struct location {
	double x;
	double y;
	bool Visited;       //代表某个结点是否被访问过，默认为0

};
vector<location>Crocodiles;
double firstJump(int v) {
	double r = pow(Crocodiles[v].x, 2) + pow(Crocodiles[v].y, 2);
	double maxjump = pow((7.5 + D), 2);
	if (r <= maxjump) return r;
	else return 0;
}
bool isSafe(int v) {
	return(50 - abs(Crocodiles[v].x) <= D || 50 - abs(Crocodiles[v].y) <= D);
}
bool jump(int v, int w) {   //能否跳跃
	double distance = pow(Crocodiles[v].x - Crocodiles[w].x, 2) + pow(Crocodiles[v].y - Crocodiles[w].y, 2);
	return distance <= D * D;
}
bool compare(int a,int b){
	return firstJump(a) < firstJump(b);
}
void BFS() {          //有些类似六度空间的BFS，但是要输出路径并考虑第一跳
	queue<int>Q;
	int last, tail=0;
	int* tmp = new int[N];
	for (int i = 0; i < N; i++) {   
		tmp[i] = i;
	}
	sort(tmp, tmp + N, compare);     //以上为按firstjump从小到大记录在tmp中，为0的会在之后if判断被排除
	for (int i = 0; i < N; i++) {
		if (firstJump(tmp[i])) {     //将第一跳能到达的鳄鱼，按距离从小到大压入队列
			Q.push(tmp[i]);
			Crocodiles[tmp[i]].Visited = 1;
			last = tmp[i];           //last指向第一跳（即第一层BFS）中最后一个结点,tail为下一层最后一个结点
		}
	}
	int step = 2;   //代表跳跃次数，此时先把第一跳和最后一跳已经记录了,因为只跳一次的在主函数中已处理
	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		if (isSafe(v)) {   //已经安全，将v的path压栈再出栈就得到路径了
			cout << step << endl;
			stack<int>road;
			int k = 1;
			while (k < step) {     //鳄鱼数量为步数-1
				road.push(v);
				v = path[v];
				k++;
			} 
			while (!road.empty()) {      //出栈并输出位置
				int p = road.top();
				cout << Crocodiles[p].x << " " << Crocodiles[p].y << endl;
				road.pop();
			}
			free(tmp);
			return;
		}
		else{
			for (int i = 0; i < N; i++){
				if (!Crocodiles[i].Visited&&jump(v, i)) {   //	BFS还要加条件，是否能跳到
					Crocodiles[i].Visited = 1;
					Q.push(i);
					path[i] = v;
					tail = i;    //不断更新tail为下一层最后一个结点
			    }
				
			}
			if (last == v) {  //访问到了该层最后一个结点，层数加一，层尾结点置为下一层尾
				step += 1; last = tail; //进入下一层

			}
		}
		
	}
	cout << "0" << endl;//队列空了还未安全，007死定了
	free(tmp);

}
int main() {
	int i = 0;
	cin >> N >> D;
	Crocodiles.resize(N);
	while (i < N) {                     //记录鳄鱼位置并初始化
		cin >> Crocodiles[i].x;
		cin >> Crocodiles[i].y;
		Crocodiles[i].Visited = 0;
		i++;
	}
	if (D >= 42.5) { 
		cout << "1" << endl; 

	}
	else {
		BFS();
	}
	
	Crocodiles.clear();

	return 0;
}



