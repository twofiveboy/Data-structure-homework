#include "pch.h"          //��ĿҪ��һ�������롣�����������Ƚ���������
#include <iostream>
#define maxsize 1000
#define minData -10001;
int H[maxsize];
using namespace std;
void Insert(int x,int i)
{
	for (; i > 0; i /= 2) {
		if (x< H[i/2]) H[i] = H[i / 2];
		else break;
	}
	H[i] = x;

}
int main()
{
	H[0] = minData;
	int N, M,x,i,j;
	cin >> N >> M;
	/*cin >> H[1];*/
	for (i = 1; i < N + 1; i++) {
		cin >>x;
		Insert(x, i);
	}
	for (i = 0; i < M; i++)
	{
		cin >> j;
		cout << H[j];
		while (j > 1) {
			j /= 2;
			cout << " " << H[j];
		}
		cout << endl;
	}
}
	


