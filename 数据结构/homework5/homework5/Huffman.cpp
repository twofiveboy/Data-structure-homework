#include "pch.h"
#include<cstdlib>
#include<string>
#include <iostream>
#define maxsize 64
#define minNum -1
using namespace std;
int f[maxsize]; char c[maxsize]; string codes[maxsize];
typedef struct TreeNode* HuffmanTree;
struct TreeNode
{
	int weight;
	TreeNode* left;
	TreeNode* right;
	TreeNode();
};
TreeNode::TreeNode() {
	left = NULL;
	right = NULL;
}
typedef struct Heap* MinHeap;
struct Heap
{
	HuffmanTree Elements;      //����Ԫ�ص�����
	int size;           //��ǰԪ�ظ���

};
MinHeap createHeap(int N)    //��ʼ������ΪN����С��
{
	MinHeap H = new(Heap);/*(MinHeap)malloc(sizeof(Heap));*/
	//H->Elements = (HuffmanTree)malloc((N + 1) * sizeof(TreeNode));
	H->Elements = new(TreeNode[N+1]);
	H->Elements[0].weight = minNum;
	H->size = 0;
	return H;
}
void percUp(MinHeap H, int i)     //����Ϊ��С��
{
	int father, son;
	TreeNode tmp = H->Elements[i];
	for (father = i; father*2 <= H->size ; father = son) {
		son = father * 2;
		if ((son+1<= H->size) && (H->Elements[son + 1].weight < H->Elements[son].weight))//���Ҷ����ұ������С
			son++;
		if (tmp.weight <= H->Elements[son].weight) break;      //�����ٵ���
		else H->Elements[father] = H->Elements[son];
	}
	H->Elements[father] = tmp;
}
void BuildHeap(MinHeap H, int N)
{
	int i;
	for (i = 1; i < N + 1; i++) {
		H->Elements[i].weight = f[i];
		H->size++;
	}
	for (i = H->size / 2; i > 0; i--) {   //�ӱ����С�ķ�֧��㵽���ڵ�
		percUp(H, i);
	}
}
HuffmanTree DeleteMin(MinHeap H)  //ȡ����СԪ�ز�ɾ�������
{
	HuffmanTree Min=new TreeNode;
	*Min=H->Elements[1];
	H->Elements[1] = H->Elements[H->size];
	H->size--;
	percUp(H,1);
	return Min;
	/*lastWeight = H->Elements[H->size--].weight;
	for (father = 1; father * 2 <= H->size; father = son) {
		son = father * 2;
		if (son != H->size&&H->Elements[son + 1].weight < H->Elements[son].weight) son++;
		if (lastWeight < H->Elements[son].weight) break;
		else H->Elements[father].weight = H->Elements[son].weight;
	}
	H->Elements[father].weight = lastWeight;*/
	
}
void Insert(MinHeap H, HuffmanTree T)
{
	int i = ++H->size;
	for (; T->weight < H->Elements[i / 2].weight; i /= 2)
		H->Elements[i] = H->Elements[i / 2];
	H->Elements[i] = *T;
}
HuffmanTree Huffman(MinHeap H,int N)
{
	int i; HuffmanTree T;
	for (i = 1; i < N; i++) { //n���ַ�����Ҫn-1�κϲ� 
		T = (HuffmanTree)malloc(sizeof(TreeNode));
		T->left = DeleteMin(H);
		T->right = DeleteMin(H);
		T->weight = T->left->weight + T->right->weight;
		Insert(H, T);
	}
	T = DeleteMin(H);
	return T;

}
int WPL(HuffmanTree T, int depth) {
	if (!T->right && !T->right) return depth * T->weight;
	else return (WPL(T->left, depth + 1) + WPL(T->right,depth + 1));
}
bool check(int N) {
	bool judge = true;
	int len1, len2;
	for (int i = 1; i < N; i++) {
		string tmp;
		len1 = codes[i].length();
		for (int j = i + 1; j < N + 1; j++) {
			len2 = codes[j].length();
			if (len1 >= len2) {
				tmp = codes[i].substr(0, len2);
				if (tmp.compare(codes[j]) == 0) {
					judge = false;
					break;
				}
			}
			else {
				tmp = codes[j].substr(0, len1);
				if (tmp.compare(codes[i]) == 0) {
					judge = false;
					break;
				}
			}
		}
		if (!judge) break;
	}
	return judge;
}
int main() {
	int N;
	cin >> N;
	MinHeap H = createHeap(N);
	for (int i = 1; i < N + 1; i++){
		cin >> c[i] >> f[i];
	}
	BuildHeap(H,N);
	HuffmanTree T = Huffman(H,N);
	int wpl = WPL(T, 0);
	
	int M, len; char ch;
	bool judge;
	cin >> M;
	for (int i = 1; i < M + 1; i++) {
		len = 0;  //�ܳ���
		judge = true;      //��ȷ���
		for (int i = 1; i < N + 1; i++) {
			cin >> ch >> codes[i];
			len += codes[i].length()*f[i];
		}
		if (len != wpl) judge = false; //���Ȳ���
		if (judge) judge = check(N);
		if (judge) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;


}