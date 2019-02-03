#include <iostream>
using namespace std;
constexpr auto Maxsize = 100000;

int MaxSubseqSum3(int a[], int n)
{
	int i, thissum = 0, maxsum = 0;
	for (i = 0; i < n; i++)
	{
		thissum += a[i];
		if (thissum < 0)
			thissum = 0;
		if (thissum > maxsum)
			maxsum = thissum;

	}
	return maxsum;
}
int main()
{
	int i, n, a[Maxsize];
	cin >> n;
	for (i = 0; i < n; i++)
		cin >> a[i];
	MaxSubseqSum3(a, n);
	cout << MaxSubseqSum3(a, n);

	return 0;



}