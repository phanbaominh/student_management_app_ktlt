#pragma once 
#ifndef _LIB_H_
#define _LIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

const int N = 50;

enum DaysofWeek{
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday,
	Nullday
};

enum Type{
	Student,
	Academic_Staff,
	Lecturer
};

struct Date{
	int d;
	int m;
	int y;
};

struct Time{
	int h;
	int m;
};

struct User{
	char username[15];
	char fullname[30];
	char email[N];
	char mbphone[15];
	Type type;
	char password[20];
	char Class[15];
};

struct Course{
	char code[15];
	int year;
	int semester;
	char name[30];
	char lecname[30];
	Date start;
	Date end;
	Time from;
	Time to;
	DaysofWeek dow;
};

struct Presence{
	char code[15];
	int year;
	int semester;
	char sid[15];
	int week[30];
};

struct Score{
	char code[15];
	int year;
	int semester;
	char sid[15];
	float mids;
	float labs;
	float finals;
};

struct StuCour {
	char code[15];
	char sid[50][15];
	int size;
};
struct Size{ // Struct chứa cac bien luu lai kich thuoc cac mang trong struct array
	int stud;
	int course;
	int presence;
	int score;
	int stucour;
};
struct Array{ // Struct chứa tat ca cac mang? can dung` de luu tru thong tin
	User stud[500];
	Course course[500];
	Score score[500];
	Presence presence[500];
	StuCour stucour[500];
};

void ClearScreen();// Hàm xóa màn hình



void textcolor(int x);
void PrintNameTable(char *s);

//Các hàm liên quan tới việc đọc file
void readString(char string[], FILE *f);
void ImportCourseList(char* filename, Course carr[], int &n);
void ImportScoreboardList(char* filename, Score scrarr[], int &n);
void ImportPresenceList(char* filename, Presence parr[], int &n);
void ImportStudentList(char* filename, User studarr[], int &n); 
void ImportStuCourList(char* filename, StuCour scarr[], int &n);

//Các hàm liên quan tới việc in ra file
void ExportCourseList(char* filename, Course arr[], char header[], int n);
void ExportCourse(FILE *f, Course cour);
void ExportScoreList(char* filename, Score arr[], char header[], int n);
void ExportScore(FILE *f, Score scr);
void ExportStudent(FILE *f, User stud);
void ExportStuCour(FILE *f, StuCour scr);
void ExportStudentList(char* filename, User arr[], char header[], int n);
void ExportPresence(FILE *f, Presence pre, int duration);
void ExportPresenceList(char* filename, Presence arr[], char header[], int n,Course cor[],int nc);
void ExportStuCourList(char* filename, StuCour arr[], char header[], int n);

//Các hàm liên quan tới việc tạo menu
void createMainMenu(Array &arr, Size &n); // tạo menu chính
void createLogIn(Array &arr, Size &n);// tạo menu log in
int createStuMenu(Array &arr, Size &n, int pos); // Tạo menu bao gồm từ 31->34
int createAcaMenu(Array &arr, Size &n, int pos); // Tạo menu bao gồm từ 6->27
int createLecMenu(Array &arr, Size &n, int pos); // Tạo menu bao gồm từ 28->30
void createStudMaMenu(User stud[], int &n); // Tạo menu bao gồm từ #6->#13
void createCourseMaMenu(Course course[], int &n); // Tạo menu bao gồm từ 14->18
void createCourseScheMaMenu(Course course[], int &n); // Tạo menu bao gồm từ 19->23
void createScoreandAttendMaMenu(Array &arr, Size &n); // Tạo menu bao gồm từ 24->27

//Các hàm chức năng
void ChangePassword(User arr[], int vt);
void ShowInfo(User user);
void ViewCredit();

// Các hàm trong createStudMaMenu: (PA03)
// Cho vào mảng arr chứa thông tin người dùng và n là số phần tử trong mảng để tạo ra một mảng arrclass chứa các tên lớp có trong arr và có số lớp là ncl
void createClassArr(User arr[], int &n, char arrclass[][15],int &ncl); 
// Yêu cầu người dùng nhập tên file rồi dùng hàm ImportStudentList để thêm vào mảng studarr, lấy ra class của những student đó rồi thêm vào mảng arrclass
void ImportClass(User studarr[], int &n ,char arrclass[][15], int &ncl);
// Nhập tên class rồi thêm vào mảng
void AddNewClass(char arrclass[][15] ,int &ncl);
// In ra mảng arrclass
void ViewListofClass(char arrclass[][15] ,int ncl);
// Yêu cầu người dùng nhập tên Class, rồi dò class đó trong studarr để in ra học sinh
void ViewListofStudentinClass(User studarr[], int &n, char arrclass[][15], int &ncl);

// Các hàm trong createCourseMaMenu (PA04)
void ImportCourse(Course carr[], int &n);// Yêu cầu người dùng nhập tên file rồi dùng hàm ImportCourseList để thêm vào mảng carr
void AddNewCourse(Course carr[], int &n);// Nhập các thông tin liên quan tới course rồi thêm vào mảng carr
void EditCourse(Course carr[], int &n);// Yêu cầu nhập Course Code, rồi cho người dùng nhập thông tin mới cho course đó
void RemoveCourse(Course carr[], int &n);// Yêu cầu nhập course code, rồi xóa course đó
void ViewListofCourse(Course carr[], int &n);// In ra mảng carr
// 31-34
void CheckIn(Array &arr, Size &n, int pos);
void ViewCheckIn(Array &arr, Size &n, int pos);
void ViewScoreBoard(Array &arr, Size &n, int pos);
void ViewSchedule(Array &arr, Size &n, int pos);
//28-30 , gọi ở trong createLecMenu
void ImportScoreBoard(Score sarr[], int &n);// Yêu cầu nhập tên file rồi gọi hàm ImportScoreBoardList 
void EditGrade(Score sarr[], int n);// Yêu cầu nhập mssv,course code, rồi tìm trong mảng score phần tử thỏa 2 cái đó. Dùng các lệnh scanf_s để nhập lại điểm của phần tử
void ViewScore(Score sarr[], int n);// Yêu cầu nhập course code, rồi tìm trong mảng score phần tử thỏa  cái đó. In ra hết các phần tử có trùng course code đã nhập
void PrintfCoreTable(int Serial, char StudentID[25], float Midterm, float Labs, float Finals, int y);
void PrintfTable(int y);

void ImportSchedule(Course carr[], int n);
void AddCourseSchedules(Course carr[], int n);
void EditCourseSchedules(Course carr[], int n);
void RemoveCourseSchedules(Course carr[], int n);
void ViewListOfSchedules(Course carr[], int n);

// 24-27
void Search_and_view_scoreboard_of_a_course(Score score[], int n);
void Search_and_view_attendance_list_of_a_course(Presence presence[], int n);
void Export_attendance_list_to_a_csv_file(Array &arr, Size &n);
void Export_a_scoreboard_to_a_csv_file(Array &arr, Size &n);

void AddStudenttoClass(User arr[], int &n, char arrclass[][15], int &ncl);
void EditStudent(User arr[], int n);
void RemoveStudent(User arr[], int &n);
void ChangeStudentClass(User arr[], int &n, char arrclass[][15], int &ncl);
#endif