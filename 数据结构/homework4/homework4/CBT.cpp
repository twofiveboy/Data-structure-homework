#include"pch.h"
#include<math.h>
#include <iostream>
#define maxsize 1000
int A[maxsize];
int T[maxsize];
using namespace std;
void sort(int A[], int N) {
	for (int i = N - 1; i >= 0; i--) {
		int flag = 0;
		for (int j = 0; j < i; j++)
		{
			if (A[j] > A[j + 1]) {
				int tmp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = tmp;
				flag = 1;
			}
		}
		if (flag == 0) break;
	}
}
int getLeftNumber(int n) {                    //获得n个结点的CBT左子树结点数
	int H,X;
	H = floor(log10(n) / log10(2));
	X = n + 1 -pow(2,H);
	X= X < pow(2, H - 1) ? X : pow(2, H - 1);
	return X + pow(2, H - 1) - 1;
}
void solve(int left,int right,int Troot){
	int n = right - left + 1;
	if (n == 0) return;
	int L = getLeftNumber(n);
	T[Troot] = A[left+L];
	solve(left, left + L - 1, Troot * 2 + 1);
	solve(left + L + 1, right, Troot * 2 + 2);

}
int main()
{
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
	sort(A, N);
	solve(0, N-1, 0);
	cout << T[0];
	for (int i = 1; i < N; i++) {
		cout << " " << T[i];
	}
}





