#include "pch.h"
#include<stack>
#include<queue>
#include<algorithm>  //sort����reference:https://www.cnblogs.com/jjzzx/p/5122381.html
#include<cstring>
#include<cmath>
#include <iostream>
#include<vector>
//reference��http://www.cnblogs.com/minesweeper/p/5954733.html
using namespace std;
int N;
double D;
bool answer;
int path[101] = { -1 };                 //007��Ծ·��
struct location {
	double x;
	double y;
	bool Visited;       //����ĳ������Ƿ񱻷��ʹ���Ĭ��Ϊ0

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
bool jump(int v, int w) {   //�ܷ���Ծ
	double distance = pow(Crocodiles[v].x - Crocodiles[w].x, 2) + pow(Crocodiles[v].y - Crocodiles[w].y, 2);
	return distance <= D * D;
}
bool compare(int a,int b){
	return firstJump(a) < firstJump(b);
}
void BFS() {          //��Щ�������ȿռ��BFS������Ҫ���·�������ǵ�һ��
	queue<int>Q;
	int last, tail=0;
	int* tmp = new int[N];
	for (int i = 0; i < N; i++) {   
		tmp[i] = i;
	}
	sort(tmp, tmp + N, compare);     //����Ϊ��firstjump��С�����¼��tmp�У�Ϊ0�Ļ���֮��if�жϱ��ų�
	for (int i = 0; i < N; i++) {
		if (firstJump(tmp[i])) {     //����һ���ܵ�������㣬�������С����ѹ�����
			Q.push(tmp[i]);
			Crocodiles[tmp[i]].Visited = 1;
			last = tmp[i];           //lastָ���һ��������һ��BFS�������һ�����,tailΪ��һ�����һ�����
		}
	}
	int step = 2;   //������Ծ��������ʱ�Ȱѵ�һ�������һ���Ѿ���¼��,��Ϊֻ��һ�ε������������Ѵ���
	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		if (isSafe(v)) {   //�Ѿ���ȫ����v��pathѹջ�ٳ�ջ�͵õ�·����
			cout << step << endl;
			stack<int>road;
			int k = 1;
			while (k < step) {     //��������Ϊ����-1
				road.push(v);
				v = path[v];
				k++;
			} 
			while (!road.empty()) {      //��ջ�����λ��
				int p = road.top();
				cout << Crocodiles[p].x << " " << Crocodiles[p].y << endl;
				road.pop();
			}
			free(tmp);
			return;
		}
		else{
			for (int i = 0; i < N; i++){
				if (!Crocodiles[i].Visited&&jump(v, i)) {   //	BFS��Ҫ���������Ƿ�������
					Crocodiles[i].Visited = 1;
					Q.push(i);
					path[i] = v;
					tail = i;    //���ϸ���tailΪ��һ�����һ�����
			    }
				
			}
			if (last == v) {  //���ʵ��˸ò����һ����㣬������һ����β�����Ϊ��һ��β
				step += 1; last = tail; //������һ��

			}
		}
		
	}
	cout << "0" << endl;//���п��˻�δ��ȫ��007������
	free(tmp);

}
int main() {
	int i = 0;
	cin >> N >> D;
	Crocodiles.resize(N);
	while (i < N) {                     //��¼����λ�ò���ʼ��
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



