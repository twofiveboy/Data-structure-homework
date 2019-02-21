#include "pch.h"
#include <iostream>
using namespace std;
//采用桶排序解决
int main()
{
	int N, x, A[51] = { 0 };
	cin >> N;
	int i;
	for (i = 0; i < N; i++)
	{
		cin >> x;
		A[x]++;
	}
	for (i = 0; i < 51; i++) {
		if (A[i]) cout << i << ":" << A[i] << endl;
	}
	return 0;
}

