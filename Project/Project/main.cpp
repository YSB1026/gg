#include "grade.h"
#include <Windows.h>

void gotoxy(int x, int y);
int main()
{
	grade d;
	int sel;
	do {
		cout << "1. �ڷ� �Է�" << endl;
		cout << "2. �ڷ� ���" << endl;
		cout << "3. �ڷ� �˻�" << endl;
		cout << "4. �ڷ� ����" << endl;
		cout << "0.   ����   " << endl;
		cout << "�����ϰ� ���� �޴� [ ]";
		gotoxy(20, 5);
		cin >> sel;
		system("cls");
	} while (sel < 0 || sel>4);

	switch (sel) {
	case 0: exit(0); break;
	case 1: d.input_data(); break;
	case 2: d.output_data(); break;
	case 3: d.find_data(); break;
	case 4: d.update_data(); break;
	}
		
	return 0;
}

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

