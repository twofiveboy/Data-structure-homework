#include "pch.h"
#include <iostream>
using namespace std;  
//表排序与环
int A[100000];
int P[100000];//记录每个数的位置
//int* A;
//int* P;
int UnitLoop() {
	int tmp, counter=0;
	int next=0;
	tmp = A[0];
	while (P[next] != next) {
		int next_new = P[next];//下一步的位置
		A[next] = A[P[next]];//将A【next】更新为下一轮
		P[next] = next;  //更新P的位置c
		next = next_new;  //下一步
		counter++;
	}
	return counter - 1;
}
int MultipleLoop(int i) {
	int tmp, counter = 0;
	int next = i;
	tmp = A[i];
	while (P[next] != next) {
		int next_new = P[next];//下一步的位置
		A[next] = A[P[next]];//将A【next】更新为下一轮
		P[next] = next;  //更新P的位置c
		next = next_new;  //下一步
		counter++;
	}
	return counter + 1;
}

int main() {
	int N,i;
	cin >> N;
	//A = new int[N];
	//int * P = new int[N];  //记录每个数的位置
	for (i = 0; i < N; i++) {
		cin >> A[i];
		P[A[i]] = i;   //数x位于i处
	}
	int number=0;
	for (i = 0; i < N; i++) {
		if (P[i] != i) {
			if (i == 0) {
				number += UnitLoop();
		}
			else {
				number += MultipleLoop(i);
			}
		}
	}
	
	cout << number;

}