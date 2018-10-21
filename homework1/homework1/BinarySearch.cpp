#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
	ElementType Data[MAXSIZE];
	Position Last; /* 保存线性表中最后一个元素的位置 */
};

//List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
//Position BinarySearch(List L, ElementType X);

int main()
{
	List L;
	ElementType X;
	Position P;
	L->Data[0] = 1;
	L->Last;
	/*L = ReadInput();
	scanf("%d", &X);
	P = BinarySearch(L, X);
	printf("%d\n", P);*/

	return 0;
}
Position BinarySearch(List L, ElementType X)
{
	Position left, right,center;
	left = 1;
	right = L->Last;
	
	while (left <= right)
	{
		center = (left+right)/ 2;
		if (L->Data[center] == X)
			return center;
		else if (L->Data[center] < X)
			left = center + 1;
		else if (L->Data[center] > X)
			right = center - 1;
		
	}
	return NotFound;


}