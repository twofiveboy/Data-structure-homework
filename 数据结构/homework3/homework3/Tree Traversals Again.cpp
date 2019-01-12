#include <iostream>
#include<cstdio>
#include<string>
#include<vector>
#define maxsize 30
typedef struct node
{
	int address;
	int times;
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
	bool isEmpty()
	{
		if (top == -1) return true;
		else return false;
	}
	Tree getTop()
	{
		return data[top];
	}
private:
	Tree data[maxsize];
	int top;
};   

int main()
{
	int n, address;
	Tree T[maxsize],tmp,top;
	Stack stack;
	vector<int>vec;
	cin >> n;
	cin.get();
	char judge[5];
	for (int i = 0; i < 2 * n; i++)
	{
		cin >> judge;
		if (judge=="Push")
		{
			cin >> address;
			stack.push(T[address]);
			T[address].times = 1;
		}
		else 
		{
			tmp = stack.pop();
			if (tmp.times == 1)
			{
				tmp.times = 2;
				stack.push(tmp);
			}
			else if (tmp.times == 2)
			{
				vec.push_back(tmp.address);
				while (stack.getTop().times == 2)
				{
					vec.push_back(tmp.address);
					stack.pop();
				}
				if (!stack.isEmpty())
				{
					top = stack.pop();
					top.times = 2;
					stack.push(top);
				}
			}
		}

	}
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	while (!stack.isEmpty())
	{
		top = stack.pop();
		cout << top.address;
		if (!stack.isEmpty())
			cout << " ";
	}
	return 0;
}
//right version;
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
typedef struct node
{
	int data;
	int times;
	node(int d, int t)
		:data(d), times(t)
	{};
} Node;

int main()
{
	int n;
	cin >> n;
	string cmd;  //!PUSH or POP
	int x;
	stack<Node> sta;  //!栈：用来实现后序遍历
	vector<int> vec;  //!存放结果
	for (int i = 0; i < 2 * n; i++)
	{
		cin >> cmd;
		if (cmd == "Push")
		{
			cin >> x;
			sta.push(Node(x, 1));
		}
		if (cmd == "Pop")
		{
			Node node = sta.top();
			sta.pop();
			if (node.times == 1)  //!times==1：弹出来变成2压回栈
			{
				node.times = 2;
				sta.push(node);
			}
			else if (node.times == 2)  //!times==2：弹出，放入存放结果的vector中
			{
				vec.push_back(node.data);
				while (sta.top().times == 2)  //!重复这一过程，直到栈顶的times==1
				{
					vec.push_back(sta.top().data);
					sta.pop();
				}
				if (sta.size() != 0)  //!操作结束后栈还不为空，使栈顶的times=2
				{
					sta.top().times = 2;
				}
			}
		}
	}
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	while (sta.size() != 0)  //!PUSH/POP结束后栈中还有元素，直接pop()即可
	{
		cout << sta.top().data;
		sta.pop();
		if (sta.size() != 0)
			cout << " ";
	}
	return 0;
}