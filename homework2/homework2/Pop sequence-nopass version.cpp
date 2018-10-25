#include "pch.h"
#include <iostream>
#define Maxsize 1000
using namespace std;
bool Judge(int a[],int M,int N)
{
	int i,j,tmp,counter;
	bool judge;
	for (i = 0; i < N; i++)
	{
		tmp = a[i];
		judge = true;
		counter = 1;
		for (j = i + 1; j < N; j++)
		{
			if (a[j] < a[i])
			{
				if (a[j] < tmp)
				{
					tmp = a[j];
					counter++;
				}
				else
				{
					judge = false;
					break;
				}
				if (counter > M)
				{
					judge = false;
					break;
				}  
			}

		}
		if (!judge) break;
	}
	return judge;
}
int main()
{
	int i,j,M, N, K;    //M (the maximum capacity of the stack), N (the length of push sequence), and K (the number of pop sequences to be checked).
	int a[Maxsize];
	cin >> M >> N >> K;
	bool judge[Maxsize];
	for (i = 0; i < K; i++)
	{
		for (j = 0; j < N; j++)
		{
			cin >> a[j];
		}
		judge[i] = Judge(a,M,N);
	}
	for (i = 0; i < K; i++)
	{
		if (judge[i]) cout << "Yes" << endl;
		else  cout << "No" << endl;
	}
} 