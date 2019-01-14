#include <iostream>
using namespace std;
typedef struct treeNode* Tree;
struct treeNode
{
	int data;
	Tree left, right;
	int flag;

};

Tree NewNode(int data)
{
	Tree T = (Tree)malloc(sizeof(treeNode));
	T->data = data;
	T->left = T->right = NULL;
	T->flag = 0;
	return T;
}
Tree Insert(Tree T, int data)
{
	if (!T)  T = NewNode(data);
	else
	{
		if (data < T->data)
		{
			T->left = Insert(T->left, data);
		}
		else
		{
			T->right = Insert(T->right, data);
		}
	}
	return T;
}
Tree buildTree(int N)
{
	int data;
	cin >> data;
	Tree T = NewNode(data);
	for (int i = 1; i < N; i++)
	{
		cin >> data;
		T = Insert(T, data);
	}
	return T;
}
int check(Tree T, int data)
{
	if (T->flag)
	{
		if (data < T->data) check(T->left, data);
		else if (data > T->data) check(T->right, data);
		else T->flag = 0;
	}
	else
	{
		if (data == T->data)
		{
			T->flag = 1;
			return 1;
		}
		else return 0;
	}
}
int Judge(Tree T, int N)
{
	int data, judge = 1;  //1代表一致，0代表已经不同
	cin >> data;
	if (data != T->data) judge = 0;
	else T->flag = 1;
	for (int i = 1; i < N; i++)
	{
		cin >> data;
		if ((judge) && (!check(T, data)))judge = 0;
	}
	if (judge) return 1;
	else return 0;
}
void Reset(Tree T)
{
	if (T->left)Reset(T->left);
	if (T->right)Reset(T->right);
	T->flag = 0;
}
void FreeTree(Tree T)
{
	if (T->left) FreeTree(T->left);
	if (T->right)FreeTree(T->right);
	free(T);
}
int main()
{
	int N, L;
	Tree T;
	cin >> N;
	while (N) {
		cin >> L;
		T = buildTree(N);
		for (int i = 0; i < L; i++)
		{
			if (Judge(T, N)) cout << "Yes" << endl;
			else cout << "No" << endl;
			Reset(T);
		}
		FreeTree(T);
		cin >> N;
	}
	return 0;

}