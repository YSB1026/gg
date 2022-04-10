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
		int n; //사람 수,데이터수
		ofstream fout("grade.bin", ios::binary);
		cout << "학생 수를 입력하세요 : ";
		cin >> n;
		//info 배열 동적 할당후 info의 내용 먼저 적고 파일에 한꺼번에 쓰기!
		//순서  이름 / 번호, 과목1,2 / 등수 순으로 info *student 내용 작성
		info* student = new info[n];

		//랜덤 이름
		string* sname = new string[n];
		for (int i = 0; i < n; i++) {
			string fn[] = { "김","박","이","서","유","조","윤","강","장","노","홍","임","한","류","홍","임", "최","정"};
			string sn[] = { "민준","서준","예준","도윤","시우","주원","하준","지호","준서","준우","도현","지훈","선영","주혜","다혜","혜지","영빈","한울",
			"현우","선우","민재","현준","연우","유준","승우","지환","지우","유찬","윤우","지원","재윤","수호","태윤","민규","재원","재민","성빈","설", "초롱",
			"이준","시온","하율","우빈","민호","준","예찬","준희","도훈","승원","정현","경호","서연","서윤","민서","은아","하윤","윤서","지유","지후","슬아",
			"지민","하은","채원","은서","다은","예은","지윤","소율","채은","윤아","유나","겨울","봄","보미","여름","가을","예진","시아","예서","지은","로운",
			"다연","서은","유빈","나은","나연","민주","혜원","소연","은비","은채","다윤","규리","태희","지수","사랑","현수" ,"하진","채린","다온","루다",
			"선","세연","율","영","비","은영","은지","슬아","눈꽃","다빈","아라","미나","아라","이솔","하나","수아","성훈","찬우","현", "민기","노아",
			"로운","리아","시후","도원","태연","다희","하진","재준","호준","서율","한별","은별","소윤","이슬","바람","수홍","장훈","병훈","샛별","늘봄","도담",
			"서영","소율","율","원준","은유","지영","선재","라움","보람","현주","명훈","인성","재하","석훈","연수","설현","영하","영수","수지","소미","나라","규현" };
			int size1 = sizeof(fn) / sizeof(fn[0]);
			int size2 = sizeof(sn) / sizeof(sn[0]);
			sname[i] = fn[rand() % size1] + sn[rand() % size2];
		}
		sort(sname, sname + n); // 가나다순 정렬

		for (int i = 0; i < n; i++) {
			student[i].num = i + 1;
			strcpy_s(student[i].name, sname[i].c_str());
			student[i].sub1 = rand() % 101;
			student[i].sub2 = rand() % 101;
		}

		vector<pair<int, int>> temp1; //과목 1 등수 vector<pair<int,int>> first : 과목1 / second : 학생 번호
		vector<pair<int, int>> temp2; //과목 2 등수 vector<pair<int,int>> first : 과목2 / second : 학생 번호
		//pair값으로 넣는 이유는 과목의 점수만 받아와서 정렬하면 어떤 학생의 점수인지 모르기 때문에
		//성적 - 번호 pair 값으로 넣는다. 정렬해도 어떤 학생의 점수인지 알 수 있음 -> second(학생번호)값과 함께 저장되기 떄문

		for (int i = 0; i < n; i++) {
			temp1.push_back(make_pair(student[i].sub1, student[i].num));
		}

		for (int i = 0; i < n; i++) {
			temp2.push_back(make_pair(student[i].sub2, student[i].num));
		}

		//100 100 90 85 처럼 점수가 같을 때 1등 1등 3등 4등으로 등수 처리
		//과목1
		for (int i = 0; i < n; i++) {
			student[i].rank1 = 1;
			for (int j = 0; j < n; j++) {
				if (temp1[i].first < temp1[j].first) {
					//r1[i] += 1;
					student[temp1[i].second - 1].rank1++;
				}
			}
		}

		//과목2
		for (int i = 0; i < n; i++) {
			student[i].rank2 = 1;
			for (int j = 0; j < n; j++) {
				if (temp2[i].first < temp2[j].first) {
					student[temp2[i].second - 1].rank2++;
				}
			}
		}
	
		//bin 파일 입력
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
			printf("||번호 : %5d || 이름 : %8s || 과목1: %3d || 과목2 : %3d || 과목1 등수: %5d || 과목2 등수 : %5d ||\n", student[i].num, student[i].name,
				student[i].sub1, student[i].sub2,student[i].rank1,student[i].rank2);
		}
		fin.close();
		delete[] student;
	}

	void update_data() {
		
	}
	void find_data() {
		int n;
		char search[13];
		info student;

		ifstream fin("grade.bin", ios::binary);
		fin.read((char*)&n, sizeof(n));

		cout << "=============자료 검색=============" << endl;
		cout << "찾고 싶은 학생 이름 입력 : ";
		cin >> search;

		for(int i = 0; i < n; i++) {
			fin.read((char*)&student, sizeof(student));
			char* ptr = strstr(student.name, search);
			if (ptr != NULL) {
				printf("\n학생을 찾았습니다!\n");
				printf("||번호 : %5d || 이름 : %8s || 과목1: %3d || 과목2 : %3d || 과목1 등수: %5d || 과목2 등수 : %5d ||\n", student.num, student.name,
				student.sub1, student.sub2, student.rank1, student.rank2);
			}
			if (i == n - 1 && ptr==NULL)
				printf("\n찾으시는 학생이 없습니다!\n");
		}
	}


private:
	struct info {
		int num, sub1, sub2, rank1, rank2;
		char name[13]="null";
	}; typedef struct info info;
};
#endif