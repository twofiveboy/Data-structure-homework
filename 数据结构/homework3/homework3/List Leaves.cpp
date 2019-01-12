#include <iostream>
#define maxsize 10
typedef struct node
{
	int left, right;
	int isNullptr;
	int address;
}Tree;
Tree T[maxsize];
using namespace std;
class Queue
{
public:
	Queue()
	{
		rear = front = -1;
	}
	void Add(Tree R)
	{
		if ((rear + 1) % maxsize == front)
		{
			cout << "队满";
			return;
		}
		rear = (rear + 1) % maxsize;
		data[rear] = R;
	}
	Tree Delete()
	{
		if (front == rear)
		{
			cout << "队空";
			
		}
		front = (front + 1) % maxsize;
		return data[front];
	}
	bool isEmpty()
	{
		if (front == rear)return true;
		else return false;

	}
private:
	Tree data[maxsize];
	int front, rear;
};
class Stack
{
public:
	Stack()
	{
		int top = -1;
	}
	void push(Tree R)
	{
		if (top == maxsize - 1)
			cout << "stack overflow";
		data[++top] = R;
	}
	Tree pop()
	{
		if (top == -1)  cout << "stack empty";
		return data[top--];
	}
private:
	Tree data[maxsize];
	int top;
};   //在下个作业中才用到

int buildTree(Tree T[])
{
	char left, right;
	int i, root, n, check[maxsize];
	cin >> n;
	if (n)            //n=0弹出
	{
		for (i = 0; i < n; i++)
		{
			check[i] = 0;
			T[i].address = i;
		}
		for (i = 0; i < n; i++)
		{
			cin >> left >> right;
			if (left != '-')
			{
				T[i].left = left - '0';  //字符型数字-'0'即为 int 型该数字
				T[T[i].left].isNullptr = 0;     
				check[T[i].left] = 1;
			}
			else
			{
				T[i].left = -1;
				T[T[i].left].isNullptr = 1; //指向的位置是NULL
			}

			if (right != '-')
			{
				T[i].right = right - '0';
				T[T[i].right].isNullptr = 0;
				check[T[i].right] = 1;
			}
			else 
			{ 
				T[i].right = -1; 
			    T[T[i].right].isNullptr = 1;
			}
		}
		for (i = 0; i < n; i++)
		{
			if (!check[i] && (T[i].left != -1 || T[i].right != -1)) break;
			if (n == 1) break;
		}
		root = i;
	}
	else
	{
		root = 0;
		T[0].isNullptr = 1;
	}
	return root;          

}
void listLeaves(Tree R)
{   
	Tree tmp;
	Queue ins;
	int firstleave = 1;
	if (R.isNullptr) return;
	ins.Add(R);
	while (!ins.isEmpty())
	{
		tmp = ins.Delete();
		if (T[tmp.left].isNullptr == 1 && T[tmp.right].isNullptr == 1) //左右孩子都为NULL既是叶子结点
		{
			if (firstleave)
			{
				cout<< tmp.address;
				firstleave = 0;
			}
			else cout <<" " << tmp.address;

	    }
		if (tmp.left != -1)  ins.Add(T[tmp.left]);
		if (tmp.right != -1) ins.Add(T[tmp.right]);

	}

}
int main()
{
	int root = buildTree(T);
	listLeaves(T[root]);
}