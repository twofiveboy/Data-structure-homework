#include "pch.h"
#include <iostream> //难度比Insert or Merge容易很多
using namespace std;
int N;
int *A, *B;
int IsInsert() {   //判断是否是插入排序
	int i, jump = 0;  //jump代表跳出地点
	for (i = 0; i < N - 1; i++) {   //扫描到无序点终止
		if (B[i] > B[i + 1])  break;
	}
	jump = i;
	for (i = jump + 1; i < N; i++) {  //若跳出点后与原始序列不同，那么则不是插入排序，令jump=0
		if (B[i] != A[i]) {
			jump = 0;
			break;
		}
	}
	return jump;
}
int FindNext() {
	int i;
	for (i = N - 1; i >= 0; i--)
		if (B[i] < B[i - 1])break;
    return i;
}
int main() {
	int i;
	cin >> N;
	A = new int[N];
	B = new int[N];
	for (i = 0; i < N; i++) {
		cin >> A[i];
	}
	for (i = 0; i < N; i++) {
		cin >> B[i];
	}
	int judge = IsInsert();
	if (judge != 0) //若judge！=0,是插入排序再进行一次后输出
	{
		int tmp = B[judge + 1];
		for (i = judge + 1; i > 0 && B[i - 1] > tmp; i--) {
			B[i] = B[i - 1];
		}
		B[i] = tmp;
		cout << "Insertion Sort" << endl << B[0];
		for (i = 1; i < N; i++) {
			cout << " " << B[i];
		}
	}
	else {
		int next = FindNext();
		cout << "Heap Sort" << endl;
		int tmp = B[next];
		B[next] = B[0]; B[0] = tmp;
		//进行一次perdown调整为最大堆
		int Parent, Child;
		for (Parent = 0; (Parent * 2 + 1) < next; Parent = Child) {
			Child = Parent * 2 + 1;
			if (Child != next - 1 && B[Child] < B[Child + 1]) Child++;
			if (tmp >= B[Child]) break;
			else B[Parent] = B[Child];
		}
		B[Parent] = tmp;
		cout << B[0];
		for (i = 1; i < N; i++) {
			cout << " " << B[i];
		}
	}
	delete[]A;
	delete[]B;
	return 0;
}