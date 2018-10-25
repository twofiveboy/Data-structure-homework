#include "pch.h"
#include <iostream>
#include<stack>
#define Maxsize 1000
using namespace std;
int main()
{
	int i, j, M, N, K;    //M (the maximum capacity of the stack), N (the length of push sequence), and K (the number of pop sequences to be checked).
	cin >> M >> N >> K;
	int c, n;
	bool judge[Maxsize];
	for (i = 0; i < K; i++)    //K��������������
	{
		stack<int> ins;
		judge[i] = true;
		n = 1;                         //nΪҪ��ջ������
		for (j = 0; j < N; j++)
		{
			cin >> c;                              //cΪ�����е�Ԫ��
			while (n <= c && ins.size() < M)
			{
				ins.push(n);
				n++;
			}
			if (c == ins.top() && !ins.empty())
			{
				ins.pop();
			}
			else
			{
				judge[i] = false;
				break;
			}
		}

	}
	for (i = 0; i < K; i++)
	{
		if (judge[i]) cout << "Yes" << endl;
		else  cout << "No" << endl;
	}
}