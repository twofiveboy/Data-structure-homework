#include "pch.h"
#include <iostream>
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
int Howlong() {
	int l;//归并段长度
	int judge = 1;
	for (l = 2; l <= N; l *= 2) {
		for (int i = l - 1; i < N - 1; i += 2 * l) {   //数组下标从0开始，所以i初始化为l-1
			if (B[i] > B[i + 1]) {      //如果两段衔接点不再有序，那么显然此时的l就是归并段长度
				judge = 0;
				break;
			}
		}
		if (judge == 0) break;
	}
	return l;
}
void Merge(int A[], int TmpA[], int L, int R, int RightEnd) {  //有序子列归并模块
	int LeftEnd, NumElements, Tmp;
	LeftEnd = R - 1;   //左有序序列终点为R-1
	NumElements = RightEnd - L + 1;
	Tmp = L;
	//类似两个有序数列合并
	while (L <= LeftEnd && R <= RightEnd) {  //循环进行条件，两个序列都未到达终点
		if (A[L] <= A[R])    TmpA[Tmp++] = A[L++];/* 左序列元素较小则将左边元素复制到TmpA */
		else                 TmpA[Tmp++] = A[R++];
	}
	//执行完毕后看哪个序列还有剩余，全部放入tmpA
	while (L <= LeftEnd)  TmpA[Tmp++] = A[L++]; /* 直接复制左边剩下的 */
	while (R <= RightEnd) TmpA[Tmp++] = A[R++];/* 直接复制右边剩下的 */
	//将tmpA转移给A
	for (int i = 0; i < NumElements; i++, RightEnd--)
		A[RightEnd] = TmpA[RightEnd]; /* 从最后将有序的TmpA[]复制回A[] */
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
		int length = Howlong();
		int* tmpB = new int[N];
		for (i = 0; i <= N - 2 * length; i += 2 * length) {
			Merge(B, tmpB, i, i + length, i + 2 * length - 1);
		}
		if (i + length < N) Merge(B, tmpB, i, i + length, N - 1);
		cout << "Merge Sort" << endl << B[0];
		for (i = 1; i < N; i++) {
			cout << " " << B[i];
		}
		delete[]tmpB;
	}
	delete[]A;
	delete[]B;
	return 0;
}