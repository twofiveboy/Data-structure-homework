#include "pch.h"
#include <iostream>
using namespace std;

void Swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void InsertionSort(int A[], int N) {
	int P, i, tmp;
	for (P = 1; P < N; P++) {  //默认0号元素已有序
		tmp = A[P];      /* 取出未排序序列中的第一个元素*/
		for (i = P; i>0&&A[i-1]>tmp; i--) {/*tmp依次与已排序序列中元素比较并往左移动*/
			A[i] = A[i - 1];
		}
		/* 此时i为tmp合适位置,放进合适的位置 */
		A[i] = tmp;
	}
}
void BubbleSort(int A[], int N) {   //冒泡排序
	
	for (int p = N - 1; p > 0; p--) {
		int flag = 0;   //标志变量，若一趟冒泡中没有发生任何交换，说明已经有序，可以提前结束
		for (int i = 0; i < p; i++) {   //每次将最大的沉到底层
			if (A[i] > A[i + 1]) {
				swap(A[i], A[i + 1]);
				flag = 1;
			}
		}
		if (flag == 0) break;

	}
}
void ShellSort(int A[], int N){  /* 希尔排序 - 用Sedgewick增量序列 */
	int Si, D, P, i;
	int tmp;
	int Sedgewick[] = { 36289,16001, 8929,3905,2161,929, 505, 209, 109, 41, 19, 5, 1, 0 };  //https://oeis.org/A033622
	for (Si = 0; Sedgewick[Si] >= N; Si++);/* 初始的增量Sedgewick[Si]不能超过待排序列长度 */
	for (D = Sedgewick[Si]; D > 0; D=Sedgewick[++Si]) {    //Sedgewick增量序列
		for (P = D; P < N; P++) {             //从D到N向前作间隔为Sedgewick[Si]的插入排序
			tmp = A[P];                   
			for (i = P; i>=D&&A[i-D]>tmp; i -= D) {
				A[i] = A[i - D];
			}
			A[i] = tmp;
		}
	}

}

void PercDown(int A[], int p, int N)
	{ /* 改编代码4.24的PercDown( MaxHeap H, int p )    */
	  /* 将N个元素的数组中以A[p]为根的子堆调整为最大堆 */
	int Parent, Child;
    int X;
	X = A[p]; /* 取出根结点存放的值 */
	for (Parent = p; (Parent * 2 + 1) < N; Parent = Child) {    
			        Child = Parent * 2 + 1;    //堆排序中数组元素下标从0开始（无哨兵），左右儿子下标为2i+1,2i+2
		      if ((Child != N - 1) && (A[Child] < A[Child + 1]))
			            Child++;  /* Child指向左右子结点的较大者 */
			  if (X >= A[Child]) break; /* 找到了合适位置 */
			  else  /* 下滤X */A[Parent] = A[Child];
		
	}
	A[Parent] = X;   //X放于合适的位置
}
void HeapSort(int A[], int N) {
	int i;
	for (i = N/2-1; i >= 0; i--) PercDown(A, i, N);  //此时最后一个有孩子的结点为 N/2-1
	for (i = N - 1; i > 0; i--) {
		Swap(&A[0], &A[i]);  //交换最大堆与最后一个元素（即将最大元素排到未排序列最后）
		PercDown(A, 0, i);  //重新调整规模为i的最大堆（交换最大元素后缩小规模重新调整）
	}
}
     
	/* L = 左边起始位置, R = 右边起始位置, RightEnd = 右边终点位置*/
void Merge(int A[], int TmpA[], int L, int R, int RightEnd) {  //有序子列归并模块
	int LeftEnd, NumElements, Tmp;
	LeftEnd = R - 1;   //左有序序列终点为R-1
	NumElements = RightEnd - L + 1;
	Tmp = L;
	//类似两个有序数列合并
	while (L <= LeftEnd && R <= RightEnd) {  //循环进行条件，两个序列都未到达终点
		if (A[L] <= A[R])    TmpA[Tmp++] = A[L++];/* 左序列元素较小则将左边元素复制到TmpA */
		else                 TmpA[Tmp++] = A[R++];
	}
	//执行完毕后看哪个序列还有剩余，全部放入tmpA
	while (L <= LeftEnd)  TmpA[Tmp++] = A[L++]; /* 直接复制左边剩下的 */
	while (R <= RightEnd) TmpA[Tmp++] = A[R++];/* 直接复制右边剩下的 */
	//将tmpA转移给A
	for (int i = 0; i < NumElements; i++, RightEnd--)
		A[RightEnd] = TmpA[RightEnd]; /* 从最后将有序的TmpA[]复制回A[] */
}
/* 归并排序 - 递归实现 */
void Msort(int A[], int TmpA[], int L, int RightEnd)
{ /* 核心递归排序函数 */
	int Center;
	if (L < RightEnd) {
		Center = (L + RightEnd) / 2;
		Msort(A, TmpA, L, Center); /* 递归解决左边 */
		Msort(A, TmpA, Center + 1, RightEnd);     /* 递归解决右边 */
		Merge(A, TmpA, L, Center + 1, RightEnd);  /* 左右两段子序列都有序后,合并为一段有序序列 */
	}
}
//统一的函数接口
void MergeSort1(int A[], int N)   
	{ /* 归并排序 */
		     int *TmpA;
			 
			 TmpA = new int[N];
		     if (TmpA != NULL) {
			      Msort(A, TmpA, 0, N - 1);//L=0,RightEnd=N-1
				  delete[]TmpA;
		
	}
		     else cout<<"空间不足";
}


/* 归并排序 - 循环实现 这里Merge函数在递归版本中给出 */
/* length = 当前有序子列的长度*/
void Merge_pass(int A[], int TmpA[], int N, int length) {
	/* 两两归并相邻有序子列 */
	int i, j;
	for (i = 0; i <= N - 2 * length; i += 2 * length) {   
		Merge(A, TmpA, i, i + length, i + 2 * length - 1);  //L=i,Lend=i+length-1,R=i+length,Rend=i+2*length-1,此处Merge中可以不用将tmpA复制到A上
	}  //腾出最后一段序列在下面处理
	if(i+length<N) Merge(A, TmpA, i, i + length, N - 1);  //元素个数为偶数时,，最后还剩下2个子列,直接再执行一次即可
	else /* 最后还剩1个子列,直接将A赋给tmpA，待下次length增长时在解决剩下序列*/
	{
		for (j = i; j < N; j++) TmpA[j] = A[j];
	}
}
//统一的函数接口
void Merge_Sort2(int A[], int N)
{
	int length = 1; //初始化子序列长度=1
	int *TmpA = new int[N];
	if (TmpA != NULL) {
		while (length < N) {  //每次循环执行两次归并以保证最后tmpA数据能转移到A
			Merge_pass(A, TmpA, N, length);
			length *= 2;
			Merge_pass(TmpA, A, N, length);
			length *= 2;
		}
		delete[]TmpA;
	}
	else cout << "空间不足";
}

int main()
{
	int n;
	cin >> n;
	int* A = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> A[i];
	}
	//InsertionSort(A, n);
	//BubbleSort(A, n);
	//ShellSort(A, n);
	//HeapSort(A, n);
	//MergeSort1(A, n);
	Merge_Sort2(A, n);
	cout << A[0];
	for (int i = 1; i < n; i++) {
		cout << " " << A[i];
	}
}

