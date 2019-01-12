#include"pch.h"
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode {
	ElementType Data;
	BinTree Left;
	BinTree Right;
};

void PreorderTraversal(BinTree BT); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal(BinTree BT);  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);

int main()
{
	BinTree BST, MinP, MaxP, Tmp;
	ElementType X;
	int N, i;

	BST = NULL;
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf("%d", &X);
		BST = Insert(BST, X);
	}
	printf("Preorder:"); PreorderTraversal(BST); printf("\n");
	MinP = FindMin(BST);
	MaxP = FindMax(BST);
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf("%d", &X);
		Tmp = Find(BST, X);
		if (Tmp == NULL) printf("%d is not found\n", X);
		else {
			printf("%d is found\n", Tmp->Data);
			if (Tmp == MinP) printf("%d is the smallest key\n", Tmp->Data);
			if (Tmp == MaxP) printf("%d is the largest key\n", Tmp->Data);
		}
	}
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf("%d", &X);
		BST = Delete(BST, X);
	}
	printf("Inorder:"); InorderTraversal(BST); printf("\n");

	return 0;
}
BinTree Insert(BinTree BST, ElementType X)
{
	if (!BST)
	{
		BST = (Position)malloc(sizeof(BinTree));
		BST->Data = X;
		BST->Left = NULL;
		BST->Right = NULL;
	}
	else {
		if (X < BST->Data) {
			BST->Left = Insert(BST->Left, X);
		}
		else
		{
			BST->Right = Insert(BST->Right, X);
		}
	}
	return BST;
}
BinTree Delete(BinTree BST, ElementType X)
{
	if (!BST)
		printf("Not Found\n");
	else if (X < BST->Data)
		BST->Left = Delete(BST->Left, X);
	else if (X > BST->Data)
		BST->Right = Delete(BST->Right, X);
	else    //找到该节点
	{
		if (BST->Left && BST->Right)
		{
			BinTree temp = FindMax(BST->Left);//此处找的是左子树的最大值
			BST->Data = temp->Data;
			BST->Left = Delete(BST->Left, BST->Data);
		}
		else
		{

			if (!BST->Left&& BST->Right)
				BST = BST->Right;
			else if (!BST->Right && BST->Left)
				BST = BST->Left;
			else return NULL;

		}
	}

	return BST;
}
Position Find(BinTree BST, ElementType X)
{
	if (!BST) return NULL;
	if (X < BST->Data) Find(BST->Left, X);
	else if (X > BST->Data) Find(BST->Right, X);
	else return BST;
}
Position FindMin(BinTree BST)
{
	if (!BST) return NULL;
	while (BST->Left) BST = BST->Left;
	return BST;
}
Position FindMax(BinTree BST)
{
	if (!BST) return NULL;
	while (BST->Right) BST = BST->Right;
	return BST;
}