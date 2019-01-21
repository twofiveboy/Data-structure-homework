#include "pch.h"          //题目要求一个个插入。。。。而非先建堆再排序
#include <iostream>
#define maxsize 1000
#define minData -10000
using namespace std;
struct Heap
{ 
	int* Elements;      //储存元素的数组
	int size;           //当前元素个数
	int capacity;       //容量

};
typedef struct Heap* MinHeap;
MinHeap initialize()    //初始化最小堆
{
	MinHeap H = (MinHeap)malloc(sizeof(Heap));
	H->Elements = (int *)malloc((maxsize + 1)* sizeof(int));
	H->Elements[0] = minData;
	H->size = 0;
	H->capacity = maxsize;
	return H;

} 
void percUp(MinHeap H,int i)     //调整为最小堆
{
	int father, son;
	int tmp = H->Elements[i];
	for (father = i; father <= H->size / 2; father = son) {
		son = father * 2;
		if ((son != H->size) && (H->Elements[son + 1] < H->Elements[son]))//有右儿子且比左儿子小
		son++;
		if (tmp <= H->Elements[son]) break;      //无需再调整
		else H->Elements[father] = H->Elements[son];
	}
	H->Elements[father] = tmp;
}
void BuildHeap(MinHeap H, int N)
{
	int i;
	for (i = 1; i < N + 1; i++) {
		cin >> H->Elements[i];
		H->size++;
	}
	for (i = H->size / 2; i > 0; i--) {   //从编号最小的分支结点到根节点
		percUp(H, i);
	}
}
void HeapRoute(MinHeap H,int i)
{
	int counter = 0;
	if (i > 0) cout << H->Elements[i];
	for (i=i/2; i > 0; i /= 2) {
		cout << " " << H->Elements[i];
	}
	
}
int main()
{   
	int N, M,i,j;
	MinHeap H=initialize();
	cin >> N >> M;
	BuildHeap(H, N);
	/*for(int j = 0; j <M; j++) {
		cin >> i;
		HeapRoute(H,i);
		if(j!=M-1) cout << endl;
	}*/
	for (i = 0; i < M; i++)
	{
		cin >> j;
		cout << H->Elements[j];
		while (j > 1) {
			j /= 2;
			cout<<" "<< H->Elements[j];
		}
		cout << endl;
	}
}

