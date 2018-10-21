#include "pch.h"
#include <iostream>
using namespace std;
constexpr auto Maxsize = 100000;
int max(int a, int b, int c)
{
	return a > b ? (a > c ? a : c) : (b > c ? b : c);
}
int MaxSubseqSum2(int a[], int left,int right)
{
	int MaxLeftSum, MaxRightSum, MaxLeftBorderSum, MaxRightBorderSum;
	int leftBorderSum, rightBorderSum, center,i;
	if (left == right)
	{
		if (a[left]>0) return a[left];
		else return 0;
	}
	center = (left + right) / 2;
	MaxLeftSum = MaxSubseqSum2(a, left, center);
	MaxRightSum = MaxSubseqSum2(a, center + 1, right);
	leftBorderSum = MaxLeftBorderSum = 0;
	for (i = center; i >= left; i--)
	{
		leftBorderSum += a[i];
		if (leftBorderSum > MaxLeftBorderSum)
			MaxLeftBorderSum = leftBorderSum;
	}
	rightBorderSum = MaxRightBorderSum = 0;
	for (i = center+1; i <= right; i++)
	{
		rightBorderSum += a[i];
		if (rightBorderSum > MaxRightBorderSum)
			MaxRightBorderSum = rightBorderSum;
	}
	return max(MaxLeftSum, MaxRightSum, MaxLeftBorderSum + MaxRightBorderSum);
	

}
int main()
{
	int i, n, a[Maxsize];
	cin >> n;
	for (i = 0; i < n; i++)
		cin >> a[i];
	MaxSubseqSum2(a, 0, n - 1);
	cout<<MaxSubseqSum2(a,0,n-1);

	return 0;



}