//#include<string>
//#include <iomanip>
//#include<stack>
//#include<unordered_set>
//#include <sstream>
//#include "func.h"
//#include <list>
#include"pch.h"
#include<unordered_map>
#include<set>
#include<queue>
#include<map>
#include<vector>
#include <algorithm>
#include<stdio.h>
#include<iostream>
#include<string>
#include<memory.h>
#include<limits.h>
#include<stack>
using namespace std;
struct UserNode {
	int id;
	int rank;
	vector<int> score;
	int totalScore;
	int perfectSubmit;
	int noSubmit;
	UserNode() :id(0), rank(0), score(0), totalScore(0), perfectSubmit(0), noSubmit(0) {};
	UserNode(vector<int> a) :id(0), rank(0), score(a), totalScore(0), perfectSubmit(0), noSubmit(0) {};
};
bool cmp(const UserNode&a, const UserNode&b)
{
	if (a.totalScore > b.totalScore)
		return true;
	else if (a.totalScore == b.totalScore)
	{
		if (a.perfectSubmit > b.perfectSubmit)
			return true;
		else if (a.perfectSubmit == b.perfectSubmit && a.id < b.id)
			return true;
		else
			return false;
	}
	else return false;
}
int main(void)
{
	int userSum, problemSum, submitSum;
	cin >> userSum >> problemSum >> submitSum;
	vector<UserNode> user(userSum);
	for (int i = 0; i < user.size(); i++)
	{//初始化每个用户的每个题目的分数
		user[i].score = vector<int>(problemSum, -2);
	}
	vector<int> fullScore(problemSum);
	for (int i = 0; i < fullScore.size(); i++)
	{//输入满分的分值
		cin >> fullScore[i];
	}

	for (int i = 0; i < submitSum; i++)
	{//输入提交记录
		int id, problemID, score;
		scanf_s("%d %d %d", &id, &problemID, &score);
		user[id - 1].id = id;//记录id
		user[id - 1].score[problemID - 1] = max(user[id - 1].score[problemID - 1], score);//取最高分，-1表示没有通过编译
	}
	for (int i = 0; i < user.size(); i++)
	{//统计学生的具体成绩
		user[i].totalScore = 0;
		for (int j = 0; j < problemSum; j++)
		{
			if (user[i].score[j] >= 0)//大于等于0，即通过编译器
				user[i].totalScore += user[i].score[j];
			else //-1为提交了没通过编译器,-2为没提交
				user[i].noSubmit++;

			if (user[i].score[j] == fullScore[j])//如果分数是满分，perfect++
				user[i].perfectSubmit++;
		}
	}
	sort(user.begin(), user.end(), cmp);
	user[0].rank = 1;//一个用户排名第一
	printf("%d %05d %d", user[0].rank, user[0].id, user[0].totalScore);
	for (int j = 0; j < problemSum; j++)
	{
		if (user[0].score[j] >= 0)
			printf(" %d", user[0].score[j]);
		else if (user[0].score[j] == -1)
			printf(" 0");//-1，提交了不通过，0分
		else//-2,没有提交过
			printf(" -");
	}
	printf("\n");
	for (int i = 1; i < user.size(); i++)
	{
		//即使分数为0的，也要统计排名
		if (user[i].totalScore == user[i - 1].totalScore)
			user[i].rank = user[i - 1].rank;
		else
			user[i].rank = i + 1;

		if (user[i].noSubmit != problemSum)
		{		//输出用户信息
			printf("%d %05d %d", user[i].rank, user[i].id, user[i].totalScore);
			for (int j = 0; j < problemSum; j++)
			{
				if (user[i].score[j] >= 0)//如果用户的分数大于等于0，则输出分数
					printf(" %d", user[i].score[j]);
				else if (user[i].score[j] == -1)
					printf(" 0");//-1，提交了不通过，0分
				else //-2,没有提交过，输出横线
					printf(" -");
			}
			printf("\n");
		}
	}
	return 0;
}
