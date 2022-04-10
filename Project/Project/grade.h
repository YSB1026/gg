#pragma once
#ifndef GRADE_H
#define GRADE_H
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <random>
#include <algorithm>
using namespace std;


class grade {
private:
	struct info {
		int num, sub1, sub2, rank1, rank2;
		char name[13] = "null";
	}; typedef struct info info;

public:
	void input_data() {
		srand((unsigned)time(NULL));
		int n; //��� ��,�����ͼ�
		ofstream fout("grade.bin", ios::binary);
		cout << "�л� ���� �Է��ϼ��� : ";
		cin >> n;
		//info �迭 ���� �Ҵ��� info�� ���� ���� ���� ���Ͽ� �Ѳ����� ����!
		//����  �̸� / ��ȣ, ����1,2 / ��� ������ info *student ���� �ۼ�
		info* student = new info[n];

		//���� �̸�
		string* sname = new string[n];
		for (int i = 0; i < n; i++) {
			string fn[] = { "��","��","��","��","��","��","��","��","��","��","ȫ","��","��","��","ȫ","��", "��","��"};
			string sn[] = { "����","����","����","����","�ÿ�","�ֿ�","����","��ȣ","�ؼ�","�ؿ�","����","����","����","����","����","����","����","�ѿ�",
			"����","����","����","����","����","����","�¿�","��ȯ","����","����","����","����","����","��ȣ","����","�α�","���","���","����","��", "�ʷ�",
			"����","�ÿ�","����","���","��ȣ","��","����","����","����","�¿�","����","��ȣ","����","����","�μ�","����","����","����","����","����","����",
			"����","����","ä��","����","����","����","����","����","ä��","����","����","�ܿ�","��","����","����","����","����","�þ�","����","����","�ο�",
			"�ٿ�","����","����","����","����","����","����","�ҿ�","����","��ä","����","�Ը�","����","����","���","����" ,"����","ä��","�ٿ�","���",
			"��","����","��","��","��","����","����","����","����","�ٺ�","�ƶ�","�̳�","�ƶ�","�̼�","�ϳ�","����","����","����","��", "�α�","���",
			"�ο�","����","����","����","�¿�","����","����","����","ȣ��","����","�Ѻ�","����","����","�̽�","�ٶ�","��ȫ","����","����","����","�ú�","����",
			"����","����","��","����","����","����","����","���","����","����","����","�μ�","����","����","����","����","����","����","����","�ҹ�","����","����" };
			int size1 = sizeof(fn) / sizeof(fn[0]);
			int size2 = sizeof(sn) / sizeof(sn[0]);
			sname[i] = fn[rand() % size1] + sn[rand() % size2];
		}
		sort(sname, sname + n); // �����ټ� ����

		for (int i = 0; i < n; i++) {
			student[i].num = i + 1;
			strcpy_s(student[i].name, sname[i].c_str());
			student[i].sub1 = rand() % 101;
			student[i].sub2 = rand() % 101;
		}

		vector<pair<int, int>> temp1; //���� 1 ��� vector<pair<int,int>> first : ����1 / second : �л� ��ȣ
		vector<pair<int, int>> temp2; //���� 2 ��� vector<pair<int,int>> first : ����2 / second : �л� ��ȣ
		//pair������ �ִ� ������ ������ ������ �޾ƿͼ� �����ϸ� � �л��� �������� �𸣱� ������
		//���� - ��ȣ pair ������ �ִ´�. �����ص� � �л��� �������� �� �� ���� -> second(�л���ȣ)���� �Բ� ����Ǳ� ����

		for (int i = 0; i < n; i++) {
			temp1.push_back(make_pair(student[i].sub1, student[i].num));
		}

		for (int i = 0; i < n; i++) {
			temp2.push_back(make_pair(student[i].sub2, student[i].num));
		}

		//100 100 90 85 ó�� ������ ���� �� 1�� 1�� 3�� 4������ ��� ó��
		//����1
		for (int i = 0; i < n; i++) {
			student[i].rank1 = 1;
			for (int j = 1; j < n; j++) {
				if (temp1[i].first < temp1[j].first) {
					student[temp1[i].second - 1].rank1++;
				}
			}
		}

		//����2
		for (int i = 0; i < n; i++) {
			student[i].rank2 = 1;
			for (int j = 1; j < n; j++) {
				if (temp2[i].first < temp2[j].first) {
					student[temp2[i].second - 1].rank2++;
				}
			}
		}
	
		//bin ���� �Է�
		fout.write((char*)&n, sizeof(n));
		for (int i = 0; i < n; i++)
			fout.write((char*)student, n*sizeof(info));

		fout.close();
		delete[] student;
		delete[] sname;
	}

	void output_data() {
		int n;
		ifstream fin("grade.bin", ios::binary);

		fin.read((char*)&n, sizeof(n));
		info* student = new info[n];

		fin.read((char*)student, n * sizeof(info));
		for (int i = 0; i < n; i++) {
			printf("||��ȣ : %5d || �̸� : %8s || ����1: %3d || ����2 : %3d || ����1 ���: %5d || ����2 ��� : %5d ||\n", student[i].num, student[i].name,
				student[i].sub1, student[i].sub2,student[i].rank1,student[i].rank2);
		}
		fin.close();
		delete[] student;
	}

	void update_data() {
		int n,sel;
		char search[13];
		bool t = false;
		info student;

		fstream fio("grade.bin", ios::binary|ios::out|ios::in);
		fio.read((char*)&n, sizeof(n));

		cout << "������ ������ �л� �̸� �Է� : ";
		cin >> search;

		for (int i = 0; i < n; i++) {
			fio.read((char*)&student, sizeof(info));
			char* ptr = strstr(student.name, search);
			if (ptr != NULL) {
				t = true;
				do {
					printf("0. ����1 ���� ����");
					printf("1. ����2 ���� ����");
					printf("�޴� ���� : ");
					cin >> sel;

					system("cls");
				} while (sel < 0 || sel>1);
				if (sel == 0) {
					
				}
				else {
					;
				}
			}
		}
		if (t == false) {
			printf("\n�Է��� �л��� �����ϴ�!\n");
		}

		

	}
	void find_data() {
		int n;
		char search[13];
		bool t = false;

		ifstream fin("grade.bin", ios::binary);
		fin.read((char*)&n, sizeof(n));
		info* student = new info[n];
		fin.read((char*)student, n * sizeof(info));

		cout << "=============�ڷ� �˻�=============" << endl;
		cout << "ã�� ���� �л� �̸� �Է� : ";
		cin >> search;

		for(int i = 0; i < n; i++) {
			char* ptr = strstr(student[i].name, search);
			if (ptr != NULL) {
				t = true;
				printf("\n�л��� ã�ҽ��ϴ�!\n");
				printf("||��ȣ : %5d || �̸� : %8s || ����1: %3d || ����2 : %3d || ����1 ���: %5d || ����2 ��� : %5d ||\n",
					student[i].num, student[i].name,student[i].sub1, student[i].sub2, student[i].rank1, student[i].rank2);
			}
		}
		if (t == false) {
			printf("\n�Է��� �л��� �����ϴ�!\n");
		}
	}
};
#endif