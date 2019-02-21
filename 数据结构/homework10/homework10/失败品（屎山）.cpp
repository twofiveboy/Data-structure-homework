#include "pch.h"
#include<iomanip>
#include <iostream>
#include<cstring>
#include<string>
#include<vector>
using namespace std;  //用表排序和桶排序解决问题
struct users { 
	int score[5];//每题成绩
	int totalscore=0;  //总成绩
	int perfectNum = 0;//完美解决的问题个数
	int noSubmit = 0;//是否提交过
	users() : totalscore(0), perfectNum(0), noSubmit(0) {
		for (int i = 0; i < 5; i++)score[i] = -2;
	};
};
users* user;

typedef struct Node* PtrNode;
struct Node {
	vector<int>id ;
	int score;
	int size=0;
	int rank;
};
//堆排序模块
void Swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void Percdown(int table[],int p,int N) {  //将排序表根据user调整为最小堆
	int parent, child;
	int tmp = table[p];
	int X = user[table[p]].totalscore;
	for (parent = p; parent*2<N; parent = child) {
		child = parent * 2;
		if (child != N && user[table[child + 1]].totalscore > user[table[child]].totalscore)  child++;//孩子不是最后一个元素且右儿子更大
		if (X >= user[table[child]].totalscore) break;
		else table[parent] = table[child];
	}
	table[parent] = tmp;
}
void HeapSort(int table[],int N) {
	int i;
	for (i = N / 2; i > 0; i--) Percdown(table,i,N);   //数组元素从1开始做出相应调整
	for (i = N; i > 1; i--) {
		Swap(&table[i], &table[1]);
		Percdown(table, 1, i-1);
	}
}
int main() {
	int N, M, K, i;   //N：人数，M：提交数，K：题目数
	int maxScore[5];

	cin >> N >> K >> M;
	for (i = 0; i < K; i++) {
		cin >> maxScore[i];
	}

	user = new users[N + 1];  //0号不使用

	for (i = 0; i < M; i++) {    //录入每次提交的成绩
		int user_id, problem_id, score;
		cin >> user_id >> problem_id >> score;
		problem_id--;//数列从0开始，id要减去1
		if (score > user[user_id].score[problem_id]) user[user_id].score[problem_id] = score;  //如果成绩比以往高就录入
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 0; j < K; j++)
		{
			if (user[i].score[j] >= 0)//大于等于0，即通过编译器
				user[i].totalscore += user[i].score[j];
			else //-1为提交了没通过编译器,-2为没提交
				user[i].noSubmit++;
			if (user[i].score[j] == maxScore[j])//如果分数是满分，perfect++
				user[i].perfectNum++;
		}
	}
		//排序表  
		int* table = new int[N + 1];
		for (i = 1; i <= N; i++) {
			table[i] = i;
		}
		HeapSort(table, N);


		//鉴于使用了最大堆从小到大排序，下面以反序进入桶
		PtrNode Buckets = new Node[N + 1];
		int j = 1;

		Buckets[j].score = user[table[N]].totalscore;
		Buckets[j].size++;
		Buckets[j].rank = 1;
		Buckets[j].id.push_back(table[N]);       //先将table中最后一位压入（最高成绩）
		int RankCounter = 1;
		for (i = N - 1; i > 0; i--) {
			if (user[table[i]].totalscore == user[table[i + 1]].totalscore) {  //如果和前一个的成绩相同
				if (user[table[i]].totalscore > 0) {
					int tmp, k;
					Buckets[j].id.push_back(table[i]);
					int n = ++Buckets[j].size;    //先插入
					tmp = table[i];  //再实行插入排序后半部分
					for (k = n - 1; k > 0 && user[Buckets[j].id[k - 1]].perfectNum < user[tmp].perfectNum; k--) {
						Buckets[j].id[k] = Buckets[j].id[k - 1];
					}
					//找到合适位置插入
					Buckets[j].id[k] = tmp;
					//对perfectNum相同的项按序号从小到大排序,用一趟冒泡排序将其置于合适位置
					int start = k;
					if (start > 0) {
						while (start > 0 && user[Buckets[j].id[start]].perfectNum == user[Buckets[j].id[start - 1]].perfectNum) start--;
						int sameNumber = k - start;
						for (; k >= start && k > 0; k--) {
							if (Buckets[j].id[k] > Buckets[j].id[k - 1])break;
							else Swap(&Buckets[j].id[k], &Buckets[j].id[k - 1]);
						}
					}
					RankCounter++;//总排名计数器+1
				}
				else {
					int tmp, k;
					Buckets[j].id.push_back(table[i]);
					int n = ++Buckets[j].size;    //先插入
					tmp = table[i];  //再实行插入排序后半部分
					for (k = n - 1; k > 0 && user[Buckets[j].id[k - 1]].noSubmit > user[tmp].noSubmit; k--) {
						Buckets[j].id[k] = Buckets[j].id[k - 1];
					}
					//找到合适位置插入
					Buckets[j].id[k] = tmp;
					//对perfectNum相同的项按序号从小到大排序,用一趟冒泡排序将其置于合适位置
					int start = k;
					if (start > 0) {
						while (start > 0 && user[Buckets[j].id[start]].noSubmit == user[Buckets[j].id[start - 1]].noSubmit) start--;
						int sameNumber = k - start;
						for (; k > start && k > 0; k--) {
							if (Buckets[j].id[k] > Buckets[j].id[k - 1])break;
							else Swap(&Buckets[j].id[k], &Buckets[j].id[k - 1]);
						}
					}
				}
			}
			else  //成绩低，直接压入(只有比前一个小或者相等两种可能)
			{
				j++;
				Buckets[j].id.push_back(table[i]);
				Buckets[j].score = user[table[i]].totalscore;
				Buckets[j].size++;
				Buckets[j].rank = ++RankCounter;
			}
		}
		//所有人都是0分，输出一个人的成绩
		if (Buckets[1].score == 0) {
			cout << Buckets[1].rank << " " << setw(5) << setfill('0') << Buckets[1].id[0] << " " << Buckets[1].score;
			for (int k = 0; k < K; k++) {
				cout << " ";
				if (user[Buckets[1].id[0]].score[k] >= 0) cout << user[Buckets[1].id[0]].score[k];
				else if (user[Buckets[1].id[0]].score[k] == -1) cout << "0";//-1，提交了不通过，0分
				else cout << "-";//没有提交过，输出横线
			}
			return 0;
		}
		int judge = 0;
		for (int i = 1; i <= N; i++) {
			if (user[Buckets[i].id[0]].totalscore == 0) {
				for (int j = 0; j < Buckets[i].size; j++) {
					if (user[Buckets[i].id[j]].noSubmit == K) return 0;
					cout << Buckets[i].rank << " " << setw(5) << setfill('0') << Buckets[i].id[j] << " " << Buckets[i].score;
					for (int k = 0; k < K; k++) {
						cout << " ";
						if (user[Buckets[i].id[j]].score[k] >= 0) {  //如果用户的分数大于等于0，则输出分数
							cout << user[Buckets[i].id[j]].score[k];
						}
						else if (user[Buckets[i].id[j]].score[k] == -1) cout << "0";//-1，提交了不通过，0分
						else cout << "-";//没有提交过，输出横线

					}
					cout << endl;
				}
			}
				for (int j = 0; j < Buckets[i].size; j++) {
					cout << Buckets[i].rank << " " << setw(5) << setfill('0') << Buckets[i].id[j] << " " << Buckets[i].score;
					for (int k = 0; k < K; k++) {
						cout << " ";
						if (user[Buckets[i].id[j]].score[k] >= 0) {  //如果用户的分数大于等于0，则输出分数
							cout << user[Buckets[i].id[j]].score[k];
						}
						else if (user[Buckets[i].id[j]].score[k] == -1) cout << "0";//-1，提交了不通过，0分
						else cout << "-";//没有提交过，输出横线

					}
					cout << endl;
				}
				

		}

		
	
	return 0;
	
}
//排序算法要修改成都为0时Nosubmit小的排在前面
//15 1 5
//100
//00001 1 50
//00002 1 -1
//00005 1 0
//00004 1 100
//00015 1 90
//00003 1 0
