#include "pch.h"
#include <iostream>
using namespace std;
constexpr auto Maxsize = 100000;

int MaxSubseqSum3(int a[], int n,int& firstnumber,int &lastnumber)
{
	int i,thissum=0, maxsum = 0,length=0;
	bool judge=true;
	firstnumber = lastnumber = 0;
	for (i = 0; i < n; i++)
	{ 
		thissum += a[i]; 
		length++;
		if (thissum < 0)
		{
			thissum = 0;
			length = 0; 
		}
		if (thissum > maxsum)
		{
			maxsum = thissum;
			lastnumber = a[i];
		    firstnumber = a[i+1 - length];
		}
		if (a[i] >= 0)
			judge = false;
		

	}
	if (judge)
	{
		firstnumber = a[0];
		lastnumber = a[n-1];
	}

	return maxsum;
}
int main()
{
	int i, n, a[Maxsize],firstnumber,lastnumber;
	cin >> n;
	for (i = 0; i < n; i++)
		cin >> a[i];
	cout << MaxSubseqSum3(a, n, firstnumber, lastnumber);
	cout<< " " << firstnumber << " " << lastnumber;
	
	
	return 0;
}