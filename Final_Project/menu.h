#pragma once 
#ifndef _MENU_H_
#define _MENU_H_
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
using namespace std;

void gotoxy(int column, int line)

{

	COORD coord;

	coord.X = column;

	coord.Y = line;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

int move() {

	char c = _getch();

	if ((int)c == -32) c = _getch();

	switch ((int)c) {

	case 80:
		return 1; //cout << "Xuong";

	case 72:
		return 2; //cout << "Len";

	case 77:
		return 3; //cout << "Phai";       

	case 75:
		return 4; //cout << "Trai";

	case 27:
		return 8; //Nut ESC thoat

	case 13:
		return 5; //Nut Enter

	default:
		return 0; //cout << "Sai";

	}

}

class Menu {

public:

	Menu();

	~Menu() {}

	void printMenu(int start,int number); // có nhiệm vụ in ra menu, start là vị trí đầu tiên của phần tử cần dùng trong mảng item ở dưới, number là số phần tử cần dùng 

	void deleteMenu(int start,int number); //Xóa menu khi kết thúc chương trình bằng cách viết đè kí tự trắng

	/*int numberOfItem() {
		return _numberOfItem;
	}*/

	string * getItem() {
		return item;
	}

private:

	string * item; //Mảng lưu tên của các menu

	//int _numberOfItem; //Số lượng menu

};

Menu::Menu() {

	item = new string[100];

	int i = 0;

	item[i] = "Log In";

	item[i+1] = "View Credit";

	item[i+2] = "Exit";

	//3->26 cua Academic Staff

	item[i+3] = "Log Out";

	item[i+4] = "View Info";

	item[i+5] = "Student Management";

	item[i+6] = "Courses Management";

	item[i+7] = "Courses's Schedule Management";

	item[i+8] = "Attendance list and Scoreboard";

	//9->13 cua Student Management
	item[i+9] = "Import Student of a Class";

	item[i+10] = "Add a Student to a Class";

	item[i+11] = "Edit a Student";

	item[i+12] = "Remove a Student";

	item[i+13] = "Change Student from Class A to B";

	item[i + 14] = "Add a new Empty Class";

	item[i + 15] = "View list of classes";

	item[i + 16] = "View list of students in a class";

	i = 3;
	//14->18 cua Course Management
	item[i+14] = "Import Course";

	item[i+15] = "Add a new Course";

	item[i+16] = "Edit a Course";

	item[i+17] = "Remove a Course";

	item[i+18] = "View list of Course";

	//19->23 cua Schedule Management
	item[i+19] = "Import Course Schedule";

	item[i+20] = "Add a Course's Schedule";
	
	item[i+21] = "Edit a Course Schedule";

	item[i+22] = "Remove a Course Schedule";

	item[i+23] = "View list of Schedule";

	//24->27 cua Attendance and Scoreboard Management
	item[i+24] = "View Attendance list of a Course";

	item[i+25] = "Export Attendance list to a CSV file";

	item[i+26] = "Search and view Scoreboard of a Course";

	item[i+27] = "Export Scoreboard to a CSV file";
	//28->32 cua Lecturer
	item[i+28] = "Log Out";

	item[i+29] = "View Info";

	item[i+30] = "Import Scoreboard of a Course";

	item[i+31] = "Edit grade of a Student";

	item[i+32] = "View a Scoreboard";
	//33->38 cua Student
	item[i+33] = "Log out";

	item[i+34] = "View Info";

	item[i+35] = "Check in";
	
	item[i+36] = "View Check-in result";

	item[i+37] = "View score of a course";
	
	item[i+38] = "View Schedules";
	//39-41 cua Log In Menu
	item[i+39] = "Enter Username";

	item[i+40] = "Enter Password";

	item[i+41] = "Change Password";

}

void Menu::printMenu(int start,int number) {

	textcolor(5);
	gotoxy(35, 3);
	int n = number;
	int m = 50;
	printf("%c", 201);
	for (int i = 0; i <m ; ++i)
		printf("%c", 205);
	printf("%c", 187);
	for (int i = 4; i < 5+n+3; ++i)
	{
		gotoxy(36+m, i );
		printf("%c", 186);
	}
	gotoxy(m+35+1, 5+n+3);
	printf("%c", 188);
	for (int i = 36+m-1; i >= 35; --i)
	{
		gotoxy(i, 5+n+3);
		printf("%c", 205);
	}
	gotoxy(35, 5+n+3);
	printf("%c", 200);
	
	for (int i = 5+n+2; i > 3; --i)
	{
		gotoxy(35, i );
		printf("%c", 186);
	}
	gotoxy(36, 5);
	for (int i = 0; i <m; ++i)
		printf("%c", 205);
	textcolor(10);
	for (int i = 0; i < number; i++) {

		gotoxy(3+36, i+6);

		cout << item[start+i];

		Sleep(10); //Tạm dừng 100ms

	}
	gotoxy(0+36, number + 6);
	printf("---->Press Esc to back");
	textcolor(15);
}

void Menu::deleteMenu(int start,int number) {

	for (int i = 0; i < number; i++) {

		Sleep(100);

		gotoxy(0, i);

		for (int j = 0; j < item[start+i].size() + 3; j++) {

			cout << " "; //Xóa bằng cách ghi đè kí tự trắng

		}

	}
	gotoxy(0, number);
	printf("                    ");

}

#endif