#include "pch.h"
#include <iostream>
using namespace std;  
//�������뻷
int A[100000];
int P[100000];//��¼ÿ������λ��
//int* A;
//int* P;
int UnitLoop() {
	int tmp, counter=0;
	int next=0;
	tmp = A[0];
	while (P[next] != next) {
		int next_new = P[next];//��һ����λ��
		A[next] = A[P[next]];//��A��next������Ϊ��һ��
		P[next] = next;  //����P��λ��c
		next = next_new;  //��һ��
		counter++;
	}
	return counter - 1;
}
int MultipleLoop(int i) {
	int tmp, counter = 0;
	int next = i;
	tmp = A[i];
	while (P[next] != next) {
		int next_new = P[next];//��һ����λ��
		A[next] = A[P[next]];//��A��next������Ϊ��һ��
		P[next] = next;  //����P��λ��c
		next = next_new;  //��һ��
		counter++;
	}
	return counter + 1;
}

int main() {
	int N,i;
	cin >> N;
	//A = new int[N];
	//int * P = new int[N];  //��¼ÿ������λ��
	for (i = 0; i < N; i++) {
		cin >> A[i];
		P[A[i]] = i;   //��xλ��i��
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