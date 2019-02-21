#include "pch.h"
#include<iomanip>
#include <iostream>
#include<cstring>
#include<string>
#include<vector>
using namespace std;  //�ñ������Ͱ����������
struct users { 
	int score[5];//ÿ��ɼ�
	int totalscore=0;  //�ܳɼ�
	int perfectNum = 0;//����������������
	int noSubmit = 0;//�Ƿ��ύ��
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
//������ģ��
void Swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void Percdown(int table[],int p,int N) {  //����������user����Ϊ��С��
	int parent, child;
	int tmp = table[p];
	int X = user[table[p]].totalscore;
	for (parent = p; parent*2<N; parent = child) {
		child = parent * 2;
		if (child != N && user[table[child + 1]].totalscore > user[table[child]].totalscore)  child++;//���Ӳ������һ��Ԫ�����Ҷ��Ӹ���
		if (X >= user[table[child]].totalscore) break;
		else table[parent] = table[child];
	}
	table[parent] = tmp;
}
void HeapSort(int table[],int N) {
	int i;
	for (i = N / 2; i > 0; i--) Percdown(table,i,N);   //����Ԫ�ش�1��ʼ������Ӧ����
	for (i = N; i > 1; i--) {
		Swap(&table[i], &table[1]);
		Percdown(table, 1, i-1);
	}
}
int main() {
	int N, M, K, i;   //N��������M���ύ����K����Ŀ��
	int maxScore[5];

	cin >> N >> K >> M;
	for (i = 0; i < K; i++) {
		cin >> maxScore[i];
	}

	user = new users[N + 1];  //0�Ų�ʹ��

	for (i = 0; i < M; i++) {    //¼��ÿ���ύ�ĳɼ�
		int user_id, problem_id, score;
		cin >> user_id >> problem_id >> score;
		problem_id--;//���д�0��ʼ��idҪ��ȥ1
		if (score > user[user_id].score[problem_id]) user[user_id].score[problem_id] = score;  //����ɼ��������߾�¼��
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 0; j < K; j++)
		{
			if (user[i].score[j] >= 0)//���ڵ���0����ͨ��������
				user[i].totalscore += user[i].score[j];
			else //-1Ϊ�ύ��ûͨ��������,-2Ϊû�ύ
				user[i].noSubmit++;
			if (user[i].score[j] == maxScore[j])//������������֣�perfect++
				user[i].perfectNum++;
		}
	}
		//�����  
		int* table = new int[N + 1];
		for (i = 1; i <= N; i++) {
			table[i] = i;
		}
		HeapSort(table, N);


		//����ʹ�������Ѵ�С�������������Է������Ͱ
		PtrNode Buckets = new Node[N + 1];
		int j = 1;

		Buckets[j].score = user[table[N]].totalscore;
		Buckets[j].size++;
		Buckets[j].rank = 1;
		Buckets[j].id.push_back(table[N]);       //�Ƚ�table�����һλѹ�루��߳ɼ���
		int RankCounter = 1;
		for (i = N - 1; i > 0; i--) {
			if (user[table[i]].totalscore == user[table[i + 1]].totalscore) {  //�����ǰһ���ĳɼ���ͬ
				if (user[table[i]].totalscore > 0) {
					int tmp, k;
					Buckets[j].id.push_back(table[i]);
					int n = ++Buckets[j].size;    //�Ȳ���
					tmp = table[i];  //��ʵ�в��������벿��
					for (k = n - 1; k > 0 && user[Buckets[j].id[k - 1]].perfectNum < user[tmp].perfectNum; k--) {
						Buckets[j].id[k] = Buckets[j].id[k - 1];
					}
					//�ҵ�����λ�ò���
					Buckets[j].id[k] = tmp;
					//��perfectNum��ͬ�����Ŵ�С��������,��һ��ð�����������ں���λ��
					int start = k;
					if (start > 0) {
						while (start > 0 && user[Buckets[j].id[start]].perfectNum == user[Buckets[j].id[start - 1]].perfectNum) start--;
						int sameNumber = k - start;
						for (; k >= start && k > 0; k--) {
							if (Buckets[j].id[k] > Buckets[j].id[k - 1])break;
							else Swap(&Buckets[j].id[k], &Buckets[j].id[k - 1]);
						}
					}
					RankCounter++;//������������+1
				}
				else {
					int tmp, k;
					Buckets[j].id.push_back(table[i]);
					int n = ++Buckets[j].size;    //�Ȳ���
					tmp = table[i];  //��ʵ�в��������벿��
					for (k = n - 1; k > 0 && user[Buckets[j].id[k - 1]].noSubmit > user[tmp].noSubmit; k--) {
						Buckets[j].id[k] = Buckets[j].id[k - 1];
					}
					//�ҵ�����λ�ò���
					Buckets[j].id[k] = tmp;
					//��perfectNum��ͬ�����Ŵ�С��������,��һ��ð�����������ں���λ��
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
			else  //�ɼ��ͣ�ֱ��ѹ��(ֻ�б�ǰһ��С����������ֿ���)
			{
				j++;
				Buckets[j].id.push_back(table[i]);
				Buckets[j].score = user[table[i]].totalscore;
				Buckets[j].size++;
				Buckets[j].rank = ++RankCounter;
			}
		}
		//�����˶���0�֣����һ���˵ĳɼ�
		if (Buckets[1].score == 0) {
			cout << Buckets[1].rank << " " << setw(5) << setfill('0') << Buckets[1].id[0] << " " << Buckets[1].score;
			for (int k = 0; k < K; k++) {
				cout << " ";
				if (user[Buckets[1].id[0]].score[k] >= 0) cout << user[Buckets[1].id[0]].score[k];
				else if (user[Buckets[1].id[0]].score[k] == -1) cout << "0";//-1���ύ�˲�ͨ����0��
				else cout << "-";//û���ύ�����������
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
						if (user[Buckets[i].id[j]].score[k] >= 0) {  //����û��ķ������ڵ���0�����������
							cout << user[Buckets[i].id[j]].score[k];
						}
						else if (user[Buckets[i].id[j]].score[k] == -1) cout << "0";//-1���ύ�˲�ͨ����0��
						else cout << "-";//û���ύ�����������

					}
					cout << endl;
				}
			}
				for (int j = 0; j < Buckets[i].size; j++) {
					cout << Buckets[i].rank << " " << setw(5) << setfill('0') << Buckets[i].id[j] << " " << Buckets[i].score;
					for (int k = 0; k < K; k++) {
						cout << " ";
						if (user[Buckets[i].id[j]].score[k] >= 0) {  //����û��ķ������ڵ���0�����������
							cout << user[Buckets[i].id[j]].score[k];
						}
						else if (user[Buckets[i].id[j]].score[k] == -1) cout << "0";//-1���ύ�˲�ͨ����0��
						else cout << "-";//û���ύ�����������

					}
					cout << endl;
				}
				

		}

		
	
	return 0;
	
}
//�����㷨Ҫ�޸ĳɶ�Ϊ0ʱNosubmitС������ǰ��
//15 1 5
//100
//00001 1 50
//00002 1 -1
//00005 1 0
//00004 1 100
//00015 1 90
//00003 1 0
