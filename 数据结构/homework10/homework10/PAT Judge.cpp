#include "pch.h"
#include<iomanip>  //��ʽ�����
#include <iostream>
#include<algorithm>
#include<vector>
using namespace std;  //�ñ������Ͱ����������
struct UserNode {
	int score[5];//ÿ��ɼ�
	int id;
	int totalScore ;  //�ܳɼ�
	int perfectNum ;//����������������
	int noSubmit ;//�Ƿ��ύ��
	int rank;
	UserNode() :id(0), rank(0), totalScore(0), perfectNum(0), noSubmit(0) {
		for (int i = 0; i < 5; i++)score[i] = -2;
	};
};
bool cmp(const UserNode&a, const UserNode&b)
{
	if (a.totalScore > b.totalScore)
		return true;
	else if (a.totalScore == b.totalScore)
	{
		if (a.perfectNum > b.perfectNum)
			return true;
		else if (a.perfectNum == b.perfectNum && a.id < b.id)
			return true;
		else
			return false;
	}
	else return false;
}
int main() {
	int N,K,M, i;   //N��������K����Ŀ����M���ύ��
	int maxScore[5];
	cin >> N >> K >> M;
	for (i = 0; i < K; i++) {
		cin >> maxScore[i];
	}
     //0�Ų�ʹ��
	vector<UserNode> user(N+1);
	for (i = 1; i <= N; i++) {
		user[i].id = i;
	}
	for (i = 0; i < M; i++) {    //¼��ÿ���ύ�ĳɼ�
		int id, problem_id, score;
		cin >> id >> problem_id >> score;
		problem_id--;//���д�0��ʼ��idҪ��ȥ1
		if (score > user[id].score[problem_id]) user[id].score[problem_id] = score;  //����ɼ��������߾�¼��
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 0; j < K; j++)
		{
			if (user[i].score[j] >= 0)//���ڵ���0����ͨ��������
				user[i].totalScore += user[i].score[j];
			else //-1Ϊ�ύ��ûͨ��������,-2Ϊû�ύ
				user[i].noSubmit++;
			if (user[i].score[j] == maxScore[j])//������������֣�perfect++
				user[i].perfectNum++;
		}
	}
	UserNode* begin = &user[1];
	sort(user.begin()+1, user.end(), cmp);
	user[1].rank = 1;//һ���û�������һ
	cout << user[1].rank << " " <<setw(5)<< setfill('0') << user[1].id << " " << user[1].totalScore;
	for (i = 0; i < K; i++)
	{
		if (user[1].score[i] >= 0)
			cout<<" "<<user[1].score[i];
		else if (user[1].score[i] == -1)
			cout<<" 0";//-1���ύ�˲�ͨ����0��
		else//-2,û���ύ��
			cout<<" -";
	}
	cout << endl;
	for (int i = 2; i <= N; i++)
	{
		//��ʹ����Ϊ0�ģ�ҲҪͳ������
		if (user[i].totalScore == user[i - 1].totalScore)
			user[i].rank = user[i - 1].rank;
		else
			user[i].rank = i;

		if (user[i].noSubmit != K)
		{		//����û���Ϣ
			cout << user[i].rank << " " << setw(5) << setfill('0') << user[i].id << " " << user[i].totalScore;
			for (int j = 0; j < K; j++)
			{
				if (user[i].score[j] >= 0)//����û��ķ������ڵ���0�����������
					cout << " " << user[i].score[j];
				else if (user[i].score[j] == -1)
					cout << " 0";//-1���ύ�˲�ͨ����0��
				else//-2,û���ύ��
					cout << " -";
			}
			cout << endl;
		}
	}
	return 0;

}

