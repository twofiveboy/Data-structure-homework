#include "pch.h"
#include <iostream>
using namespace std;
int N;
int *A, *B;
int IsInsert() {   //�ж��Ƿ��ǲ�������
	int i, jump = 0;  //jump���������ص�
	for (i = 0; i < N - 1; i++) {   //ɨ�赽�������ֹ
		if (B[i] > B[i + 1])  break;
	}
	jump = i;
	for (i = jump + 1; i < N; i++) {  //�����������ԭʼ���в�ͬ����ô���ǲ���������jump=0
		if (B[i] != A[i]) {
			jump = 0;
			break;
		}
	}
	return jump;
}
int Howlong() {
	int l;//�鲢�γ���
	int judge = 1;
	for (l = 2; l <= N; l *= 2) {
		for (int i = l - 1; i < N - 1; i += 2 * l) {   //�����±��0��ʼ������i��ʼ��Ϊl-1
			if (B[i] > B[i + 1]) {      //��������νӵ㲻��������ô��Ȼ��ʱ��l���ǹ鲢�γ���
				judge = 0;
				break;
			}
		}
		if (judge == 0) break;
	}
	return l;
}
void Merge(int A[], int TmpA[], int L, int R, int RightEnd) {  //�������й鲢ģ��
	int LeftEnd, NumElements, Tmp;
	LeftEnd = R - 1;   //�����������յ�ΪR-1
	NumElements = RightEnd - L + 1;
	Tmp = L;
	//���������������кϲ�
	while (L <= LeftEnd && R <= RightEnd) {  //ѭ�������������������ж�δ�����յ�
		if (A[L] <= A[R])    TmpA[Tmp++] = A[L++];/* ������Ԫ�ؽ�С�����Ԫ�ظ��Ƶ�TmpA */
		else                 TmpA[Tmp++] = A[R++];
	}
	//ִ����Ϻ��ĸ����л���ʣ�࣬ȫ������tmpA
	while (L <= LeftEnd)  TmpA[Tmp++] = A[L++]; /* ֱ�Ӹ������ʣ�µ� */
	while (R <= RightEnd) TmpA[Tmp++] = A[R++];/* ֱ�Ӹ����ұ�ʣ�µ� */
	//��tmpAת�Ƹ�A
	for (int i = 0; i < NumElements; i++, RightEnd--)
		A[RightEnd] = TmpA[RightEnd]; /* ����������TmpA[]���ƻ�A[] */
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
	if (judge != 0) //��judge��=0,�ǲ��������ٽ���һ�κ����
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