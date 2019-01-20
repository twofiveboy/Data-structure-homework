#include <iostream>
using namespace std;
constexpr auto MAXSIZE = 10001;
typedef int SetName;   //���ڵ���±���Ϊ������
typedef int SetType[MAXSIZE];
void Initilization(SetType s, int n)
{
	for (int i = 0; i < n; i++)
	{
		s[i] = -1;
	}
}
SetName Find(SetType s, int x)
{
	for (; s[x] >= 0; x = s[x]);
	return x;
	//if (s[x] < 0)return x;   //·��ѹ����
	//else return s[x]=Find(s, s[x]);
}
void Union(SetType s, SetName Root1, SetName Root2)
{
	//s[Root2]=Root1;
	  /*if (s[Root2] < s[Root1])//���ȹ鲢1�������ߣ����ڵ��ֵs[Root]=-���ߣ�R2<R1���� R2�߶ȱ�R1��
	  {
		  s[Root1] = Root2;
	  }
	  else
	  {
		  if (s[Root1] == s[Root2]) s[Root1]--;
		  s[Root2] = Root1;
	  }*/
	if (s[Root2] < s[Root1])  //���ȹ鲢2������ģ�����ڵ��ֵs[Root]=-Ԫ�ظ�����R2<R1���� R2��ģ��R1��
	{
		s[Root2] += s[Root1];
		s[Root1] = Root2;
	}
	else
	{
		s[Root1] += s[Root2];
		s[Root2] = Root1;
	}
}
void Input_Connection(SetType s)
{
	int u, v;
	SetName Root1, Root2;
	cin >> u >> v;
	Root1 = Find(s, u - 1);  // n��Ӧ�������±�Ϊn-1
	Root2 = Find(s, v - 1);
	if (Root1 != Root2) Union(s, Root1, Root2);

}
void Check_Connection(SetType s)
{
	int u, v;
	SetName Root1, Root2;
	cin >> u >> v;
	Root1 = Find(s, u - 1);
	Root2 = Find(s, v - 1);
	if (Root1 == Root2) cout << "yes" << endl;
	else cout << "no" << endl;


}
void Check_Network(SetType s, int n)
{
	int counter = 0;
	for (int i = 0; i < n; i++)
	{
		if (s[i] < 0) counter++;
	}
	if (counter == 1) cout << "The network is connected." << endl;
	else cout << "There are " << counter << " components." << endl;
}
int main()
{
	SetType S;
	int n;
	char in;
	cin >> n;
	Initilization(S, n);
	do {
		cin >> in;
		switch (in)
		{
		case'I':Input_Connection(S); break;
		case'C':Check_Connection(S); break;
		case'S':Check_Network(S, n); break;
		}

	} while (in != 'S');

}
