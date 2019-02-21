#include "pch.h"
#include<iomanip>  //格式化输出
#include <iostream>
#include<algorithm>
#include<vector>
using namespace std;  //用表排序和桶排序解决问题
struct UserNode {
	int score[5];//每题成绩
	int id;
	int totalScore ;  //总成绩
	int perfectNum ;//完美解决的问题个数
	int noSubmit ;//是否提交过
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
	int N,K,M, i;   //N：人数，K：题目数，M：提交数
	int maxScore[5];
	cin >> N >> K >> M;
	for (i = 0; i < K; i++) {
		cin >> maxScore[i];
	}
     //0号不使用
	vector<UserNode> user(N+1);
	for (i = 1; i <= N; i++) {
		user[i].id = i;
	}
	for (i = 0; i < M; i++) {    //录入每次提交的成绩
		int id, problem_id, score;
		cin >> id >> problem_id >> score;
		problem_id--;//数列从0开始，id要减去1
		if (score > user[id].score[problem_id]) user[id].score[problem_id] = score;  //如果成绩比以往高就录入
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 0; j < K; j++)
		{
			if (user[i].score[j] >= 0)//大于等于0，即通过编译器
				user[i].totalScore += user[i].score[j];
			else //-1为提交了没通过编译器,-2为没提交
				user[i].noSubmit++;
			if (user[i].score[j] == maxScore[j])//如果分数是满分，perfect++
				user[i].perfectNum++;
		}
	}
	UserNode* begin = &user[1];
	sort(user.begin()+1, user.end(), cmp);
	user[1].rank = 1;//一个用户排名第一
	cout << user[1].rank << " " <<setw(5)<< setfill('0') << user[1].id << " " << user[1].totalScore;
	for (i = 0; i < K; i++)
	{
		if (user[1].score[i] >= 0)
			cout<<" "<<user[1].score[i];
		else if (user[1].score[i] == -1)
			cout<<" 0";//-1，提交了不通过，0分
		else//-2,没有提交过
			cout<<" -";
	}
	cout << endl;
	for (int i = 2; i <= N; i++)
	{
		//即使分数为0的，也要统计排名
		if (user[i].totalScore == user[i - 1].totalScore)
			user[i].rank = user[i - 1].rank;
		else
			user[i].rank = i;

		if (user[i].noSubmit != K)
		{		//输出用户信息
			cout << user[i].rank << " " << setw(5) << setfill('0') << user[i].id << " " << user[i].totalScore;
			for (int j = 0; j < K; j++)
			{
				if (user[i].score[j] >= 0)//如果用户的分数大于等于0，则输出分数
					cout << " " << user[i].score[j];
				else if (user[i].score[j] == -1)
					cout << " 0";//-1，提交了不通过，0分
				else//-2,没有提交过
					cout << " -";
			}
			cout << endl;
		}
	}
	return 0;

}

