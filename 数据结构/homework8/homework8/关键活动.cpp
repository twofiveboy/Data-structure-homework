#include "pch.h"
#include<queue>
#include <iostream>
#include<algorithm>  //max_element����ͷ�ļ�
#define infinity 65535
#define maxsize 100
using namespace std;
int N, M;
int **A;//activity
int Earliest[maxsize] = { 0 }; //�������������ʱ��
int Latest[maxsize];
int TopSort() {
	int Indegree[maxsize] = { 0 }; //���
	
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
	int V, cnt = 0; //cntΪ��������ͳ���Ѽ�¼�Ļ�����
	while (!Q.empty()) {     //����Ϊ����ֹ
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
void FindMin(int x) {
	for (int i = 0; i < N; i++) {
		Latest[i] = x;
	}
	//memset(Latest, 17, sizeof(Latest)); ������memset��ʼ����������https://blog.csdn.net/melody_1016/article/details/83479778
	int Outdegree[maxsize] = { 0 }; //����
	queue<int>Q;  //���Ʒ���ִ��TopSort�㷨,�Գ��ȴ������
	//��ʼ����������ȣ�ÿ��һ��A[i][j]!=infinity,Indegree[j]+1
	for (int i = N-1; i >= 0; i--) {
		for (int j = N-1; j >=0; j--) {
			if (A[j][i] != infinity) {    //i��j���ڽӵ�
				Outdegree[j]++;
			}
		}
	}
	//��ʽ��ʼ�㷨���Ƚ��������Ϊ0�����
	for (int i = N-1; i >=0; i--) {
		if (!Outdegree[i]) Q.push(i);
	}
	int V; //�����������TopSort���Ѿ���֤�޻�·
	while (!Q.empty()) {     //����Ϊ����ֹ
		V = Q.front();
		Q.pop();
		for (int j = N-1; j >= 0; j--) {
			if (A[j][V] != infinity) {  //V��j���ڽӵģ����ڱ�
				if (Latest[V] - A[j][V] < Latest[j]) {    //Ѱ��L-��Ȩ�� ��Сֵ��Ϊj�������翪ʼʱ��
					Latest[j] = Latest[V] - A[j][V];
				}
				if (--Outdegree[j] == 0) {  //ȥ��V��j���Ϊ0�������
					Q.push(j);
				}
			}
		}
	}
	return;
}
void printKey() {
	for (int i = 0; i < N; i++) {
		if (Earliest[i] != Latest[i]) continue;   //E=L��i�ǹؼ����,��������
		for (int j = N - 1; j >= 0; j--) {              //Ϊ�����ĿҪ��ͬ��ʼ�ڵ㷴�������¼��㣬ѭ����ת
			if (Latest[j]==Earliest[i]+A[i][j] && Earliest[j] == Latest[j])//j�ǹؼ���㣬��i,jֱ������
				cout << i + 1 << "->" << j + 1 << endl;
		}
	}
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
			i--; j--;      //��Ŵ�1��ʼ
		A[i][j] = time;
	}
	int EarliestTime = TopSort();
	if (!EarliestTime) cout << "0";
	else { 
		FindMin(EarliestTime);
		cout << EarliestTime << endl; 
		printKey();
	}
	free(A);
	return 0;
}