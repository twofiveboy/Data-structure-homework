#include "pch.h"
#include<queue>
#include <iostream>
#include<algorithm>  //max_element����ͷ�ļ�
//reference��https://blog.csdn.net/yeternity/article/details/71075571
#define infinity 65535
#define maxsize 100
using namespace std;
int N, M;
int **A;//activity
int TopSort() {
	int Indegree[maxsize] = {0}; //���
	int Earliest[maxsize] = {0}; //�������������ʱ��
	queue<int>Q;
	//��ʼ����������ȣ�ÿ��һ��A[i][j]!=infinity,Indegree[j]+1
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (A[i][j] != infinity) {
				Indegree[j]++;
			}
		}
	}
	//��ʽ��ʼ�㷨���Ƚ��������Ϊ0�����
	for (int i = 0; i < N; i++) {
		if (!Indegree[i]) Q.push(i);
	}
	int V,cnt=0; //cntΪ��������ͳ���Ѽ�¼�Ļ�����
	while (!Q.empty()){     //����Ϊ����ֹ
		V = Q.front();
		Q.pop();
		cnt++;
		for (int j = 0; j < N; j++) {
			if (A[V][j] != infinity) {  //V��j���ڽӵģ����ڱ�
				if (Earliest[V] + A[V][j] > Earliest[j]) {    //Ѱ��E+��Ȩ�� ���ֵ��Ϊj�������翪ʼʱ��
					Earliest[j] = Earliest[V] + A[V][j];
			}
				if (--Indegree[j] == 0) {  //ȥ��V��j���Ϊ0�������
					Q.push(j);
				}

			}
		}
	}
	int EarliestTime = *max_element(Earliest, Earliest + N);//��Ŀ�������ʱ�������л����������ʱ�������ֵ�������һ�����ڵ��������ʱ�䣩
	if (cnt != N) return 0;     //δȫ����¼���л�·����
	else return EarliestTime;

}


int main() {
	cin >> N >> M;
	A = new int*[N];
	for (int i = 0; i < N; i++) {
		A[i] = new int[N];
		for (int j = 0; j < N; j++) {
			A[i][j] = infinity;    //ȫ����ʼ��Ϊ����,����֮�����
		}
	}
	for (int k = 0; k < M; k++) {  //��¼��������֮��ʱ��
		int i, j, time;
		cin >> i >> j >> time;
		A[i][j] = time;
	}
	int EarliestTime = TopSort();
	if (!EarliestTime) cout << "Impossible";
	else cout << EarliestTime;
	free(A);
	return 0;
}