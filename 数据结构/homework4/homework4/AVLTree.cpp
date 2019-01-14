#include"pch.h"
#include <iostream>
using namespace std;
typedef struct  Treenode* Tree;
struct Treenode
{
	int value;
	Tree lson;
	Tree rson;
	int height;
	/*Treenode(int v) :value(v), lson(NULL), rson(NULL), height(0) {}
	Treenode() :lson(NULL), rson(NULL) {}*/

};
int getHeight(Tree T)      //规定空树高度为1
{
	if (!T) return -1;
	return T->height;
}
int Max(int a, int b)
{
	return a > b ? a : b;
}
Tree LLrotate(Tree k2)
{
	Tree k1;
	k1 = k2->lson;
	k2->lson = k1->rson;
	k1->rson = k2;

	k2->height = Max(getHeight(k2->lson), getHeight(k2->rson)) + 1;
	k1->height = Max(getHeight(k1->lson), k2->height) + 1;
	return k1;
}
Tree RRrotate(Tree k2)
{
	Tree k1;
	k1 = k2->rson;
	k2->rson = k1->lson;
	k1->lson = k2;

	k2->height = Max(getHeight(k2->lson), getHeight(k2->rson)) + 1;
	k1->height = Max(k2->height, getHeight(k1->rson)) + 1;
	return k1;
}
Tree LRrotate(Tree k3)
{
	k3->lson = RRrotate(k3->lson);
	return LLrotate(k3);
}
Tree RLrotate(Tree k3)
{
	k3->rson = LLrotate(k3->rson);
	return RRrotate(k3);
}
bool isBalanced(Tree left, Tree right) {
	return abs(getHeight(left) - getHeight(right)) < 2;
}
Tree Insert(int v, Tree T)
{
	if (!T) {
		T = (Tree)malloc(sizeof(Treenode));
		T->value = v;
		T->lson = NULL;
		T->rson = NULL;
		T->height = 0;
		return T;
	}
	if (v < T->value) {
		T->lson = Insert(v, T->lson);
		if (!isBalanced(T->lson, T->rson)) {
			if (v < T->lson->value)
				T = LLrotate(T);
			else
				T = LRrotate(T);
		}
	}
	else
	{
		T->rson = Insert(v, T->rson);
		if (!isBalanced(T->lson, T->rson)) {
			if (v > T->rson->value)
				T = RRrotate(T);
			else
				T = RLrotate(T);
		}
	}
	T->height = Max(getHeight(T->lson), getHeight(T->rson)) + 1;
	return T;
}
int main()
{
	int n;
	while (cin >> n) {
		int data;
		Tree T = NULL;
		for (int i = 0; i < n; i++) {
			cin >> data;
			T = Insert(data, T);
		}
		cout << T->value << endl;
	}
	return 0;
}
