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
public:
	void input_data() {
		srand((unsigned)time(NULL));
		int n; //��� ��,�����ͼ�
		ofstream fout("grade.bin", ios::binary);
		cout << "�л� ���� �Է��ϼ��� : ";
		cin >> n;
		//info �迭 ���� �Ҵ��� info�� ���� ���� ���� ���Ͽ� �Ѳ����� ����!
		//���� : �̸� / ��ȣ, ����1,2 / ��� ������ info *student ���� �ۼ�
		info* student = new info[n];

		//���� �̸�
		string* sname = new string[n];
		for (int i = 0; i < n; i++) {
			string fn[] = { "��","��","��","��","��","��","��", "��","��","��","��","��","��","��","��","ȫ","��","��" };
			string sn[] = { "����","����","����","����","�ÿ�","�ֿ�","����","��ȣ","�ؼ�","�ؿ�","����","����","����","����","����","����","����","�ѿ�",
			"����","����","����","����","����","����","�¿�","��ȯ","����","����","����","����","����","��ȣ","����","�α�","���","���","����","��", "�ʷ�",
			"����","�ÿ�","����","���","��ȣ","��","����","����","����","�¿�","����","��ȣ","����","����","�μ�","����","����","����","����","����","����",
			"����","����","ä��","����","����","����","����","����","ä��","����","����","�ܿ�","��","����","����","����","����","�þ�","����","����","�ο�",
			"�ٿ�","����","����","����","����","����","����","�ҿ�","����","��ä","����","�Ը�","����","����","���","����" ,"����","ä��","�ٿ�","���",
			"��","����","��","��","��","����","����","����","����","�ٺ�","����","�ƶ�","�̳�","�ƶ�","�̼�","�ϳ�","����","����","����","��", "�α�","���",
			"�ο�","����","�ÿ�","����","�¿�","����","����","����","ȣ��","����","�Ѻ�","����","����","�̽�","�ٶ�","��ȫ","����","����","����","�ú�","����", };
			int size1 = sizeof(fn) / sizeof(fn[0]);
			int size2 = sizeof(sn) / sizeof(sn[0]);
			sname[i] = fn[rand() % size1] + sn[rand() % size2];
		}
		cout << endl;
		sort(sname, sname + n); // �����ټ� ����
		//���� �������� �ֱ� 0~100��
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
		int* r1 = new int[n];
		for (int i = 0; i < n; i++) {
			r1[i] = 1;
			for (int j = 0; j < n; j++) {
				if (temp1[i].first < temp1[j].first) { //temp1[i].second ���� �л��� ��ȣ 1~n , index�� 0~n-1������ -1����.
					r1[i] += 1;
					student[temp1[i].second - 1].rank1 = r1[i];
				}
			}
		}
		delete[] r1;

		//����2
		int* r2 = new int[n];
		for (int i = 0; i < n; i++) {
			r2[i] = 1;
			for (int j = 0; j < n; j++) {
				if (temp2[i].first < temp2[j].first) { //temp2[i].second ���� �л��� ��ȣ 1~n , index�� 0~n-1������ -1����.
					r2[i] += 1;
					student[temp2[i].second - 1].rank2 = r2[i];
				}
			}
		}
		delete[] r2;
	
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
		/*int n;
		int sel,sel2;

		fstream fio("grade.bin", ios::binary | ios::out | ios::in);
		fio.read((char*)&n, sizeof(n));
		info* student = new info[n];
		fio.read((char*)student, n * sizeof(info));

		do {
			cout << "�����ϰ� ���� �л��� ��ȣ or �̸�" << endl;
			cout << "1. ��ȣ" << endl;
			cout << "2. �̸�" << endl;
			cout << "���� �ϰ���� �޴� : ";
			cin >> sel;

			system("cls");
		} while (sel < 0 || sel > 1);

		cout << endl; 
		int search1;
		if (sel == 1) {
			cout << "�����ϰ� ���� �л��� ��ȣ�� �Է��ϼ��� : ";
			cin >> search1;
			for(int i=0; i<n; i++){
				if (search1 == student[i].num) {
					do {
						cout << "�����ϰ� ���� ����" << endl;
						cout << "1.    ��ȣ" << endl;
						cout << "2.    �̸�" << endl;
						cout << "3. ����1 ���� " << endl;
						cout << "4. ����2 ����" << endl;
						cout << "���� �ϰ���� �޴� : ";
						cin >> sel2;
						system("cls");
					} while (sel2 < 1 || sel2 > 4);

					switch (sel2) {
					case 1: break;
					case 2: break;
					case 3: break;
					case 4: break;
					}
				}
			}
		}

		char search2[13];
		if (sel == 2) {
			;
		}*/
	}

	void find_data() {
		int n;
		char search[13];
		ifstream fin("grade.bin", ios::binary);

		fin.read((char*)&n, sizeof(n));
		info* student = new info[n];

		fin.read((char*)student, n*sizeof(info));

		cout << "=============�ڷ� �˻�=============" << endl;
		cout << "ã�� ���� �л� �̸� �Է� : ";
		cin >> search;
		
		for (int i = 0; i < n; i++) {
			int cmp = strcmp(search, student[i].name);
			if (cmp == 0) {
				printf("||��ȣ : %5d || �̸� : %8s || ����1: %3d || ����2 : %3d || ����1 ���: %5d || ����2 ��� : %5d ||\n", student[i].num, student[i].name,
					student[i].sub1, student[i].sub2, student[i].rank1, student[i].rank2);
			}
		}
		
		delete[] student;
	}


private:
	struct info {
		int num=0, sub1=0, sub2=0, rank1 = 1, rank2 = 1;
		char name[13]="null";
	}; typedef struct info info;
};
#endif