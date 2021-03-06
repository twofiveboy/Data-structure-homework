#include <iostream>
#define maxsize 10
typedef struct node
{
	char data;
	int left, right;
}Tree;
Tree T1[maxsize], T2[maxsize];
using namespace std;
bool isomorphic(Tree R1, Tree R2)
{

	if ((R1.data == '\0') && (R2.data == '\0'))   //'\0'既是R1==NULL时，data的取值 
		return true;
	if (((R1.data == '\0') && (R2.data != '\0')) || ((R1.data != '\0') && (R2.data == '\0')))
		return false;
	if (R1.data != R2.data)
		return false;
	if (R1.left == -1 && R2.left == -1)
		return isomorphic(T1[R1.right], T2[R2.right]);

	if (R1.left != -1 && R2.left != -1 && (T1[R1.left].data == T2[R2.left].data))
		return (isomorphic(T1[R1.left], T2[R2.left]) && isomorphic(T1[R1.right], T2[R2.right]));
	else return(isomorphic(T1[R1.left], T2[R2.right]) && isomorphic(T1[R1.right], T2[R2.left]));
}
int buildTree(Tree T[])
{
	char left, right;
	int i, root, n, check[maxsize];
	cin >> n;
	if (n)            //n=0弹出
	{
		for (i = 0; i < n; i++)
			check[i] = 0;
		for (i = 0; i < n; i++)
		{
			cin >> T[i].data;
			cin >> left >> right;
			if (left != '-')
			{
				T[i].left = left - '0';  //字符型数字-'0'即为 int 型该数字
				check[T[i].left] = 1;
			}
			else T[i].left = -1;

			if (right != '-')
			{
				T[i].right = right - '0';
				check[T[i].right] = 1;
			}
			else T[i].right = -1;
		}
		for (i = 0; i < n; i++)
			if (!check[i]) break;
		root = i;
	}
	return root;

}
int main()
{
	int root1, root2;
	root1 = buildTree(T1);
	root2 = buildTree(T2);
	bool judge = isomorphic(T1[root1], T2[root2]);
	if (judge) cout << "Yes";
	else cout << "No";
}

int main()
{   
	int root1, root2;
	root1=buildTree(T1);
	root2=buildTree(T2);
	bool judge=isomorphic(T1[root1], T2[root2]);
	if (judge) cout << "Yes";
	else cout << "No";
}

