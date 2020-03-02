#include "lib.h"
#include "menu.h"

bool checkFile(char *file)
{
	int x;
	FILE *path = fopen(file, "r");
	if (path == NULL)
	{
		textcolor(12);
		puts("File not found!");
		textcolor(10);
		puts("Press any key to exit!");
		textcolor(15);
		x = _getch();
		return false;
	}
	return true;
}

void textcolor(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
void ClearScreen() // Source: http://www.cstartstart.com/articles/4z18T05o/
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}
void readString(char string[], FILE *f)
{
	int j = 0;
	while (1)
	{
		if (fscanf(f, "%c", &string[j]) == 1)
			j++;
		else
		{
			string[j] = '\0';
			return;
		}

		if (string[j - 1] == ',' || string[j - 1] == '\n') break;
	}
	string[j - 1] = '\0';
}
void ImportStudentList(char* filename, User studarr[], int &n)
{

	FILE *f = fopen(filename, "r");
	char t, temp[255];
	int i = n;
	fgets(temp, 255, f);
	while (!feof(f))
	{
		readString(studarr[i].username, f);
		readString(studarr[i].fullname, f);
		readString(studarr[i].email, f);
		readString(studarr[i].mbphone, f);
		fscanf(f, "%d", &studarr[i].type);
		fscanf(f, "%c", &t);
		readString(studarr[i].password, f);
		readString(studarr[i].Class, f);
		i++;
	}
	n = i;
	fclose(f);
}
void ExportStudent(FILE *f, User stud)
{
	fseek(f, 0, SEEK_END);
	fprintf(f, "\n");
	fprintf(f, "%s", stud.username);
	fprintf(f, ",");
	for (int i = 0; i < strlen(stud.fullname); i++)
		fprintf(f, "%c", stud.fullname[i]);
	fprintf(f, ",");
	fprintf(f, "%s", stud.email);
	fprintf(f, ",");
	fprintf(f, "%s", stud.mbphone);
	fprintf(f, ",");
	fprintf(f, "%d", stud.type);
	fprintf(f, ",");
	fprintf(f, "%s", stud.password);
	fprintf(f, ",");
	fprintf(f, "%s", stud.Class);

}
void ExportStudentList(char* filename, User arr[], char header[], int n)
{
	FILE *f = fopen(filename, "w");
	for (int i = 0; i < strlen(header); i++)
		fprintf(f, "%c", header[i]);
	for (int i = 0; i < n; i++)
	{
		ExportStudent(f, arr[i]);
	}
	fclose(f);

}
void ImportCourseList(char* filename, Course carr[], int &n)
{

	FILE *f = fopen(filename, "r");
	char t, temp[255];
	int i = n, dem, intc;
	fgets(temp, 255, f);
	while (!feof(f))
	{
		readString(carr[i].code, f);
		fscanf(f, "%d", &carr[i].year);
		fscanf(f, "%c", &t);
		fscanf(f, "%d", &carr[i].semester);
		fscanf(f, "%c", &t);
		readString(carr[i].name, f);
		readString(carr[i].lecname, f);
		readString(temp, f);
		dem = 0;
		carr[i].start.d = 0;
		carr[i].start.m = 0;
		carr[i].start.y = 0;
		for (int j = 0; j < strlen(temp); j++)
		{
			//printf("%d-%c-%d ", i,temp[j], temp[j] - '0' );
			if (temp[j] == '/')
				dem++;
			if (temp[j] != '/')
			{
				intc = temp[j] - '0';
				switch (dem)
				{
				case 0:
				{
					carr[i].start.d = carr[i].start.d * 10 + (intc);
					break;
				}
				case 1:
				{
					carr[i].start.m = carr[i].start.m * 10 + (intc);
					break;
				}
				case 2:
				{
					carr[i].start.y = carr[i].start.y * 10 + (intc);
					break;
				}
				}
			}
		}
		readString(temp, f);
		dem = 0;
		carr[i].end.d = 0;
		carr[i].end.m = 0;
		carr[i].end.y = 0;
		for (int j = 0; j < strlen(temp); j++)
		{
			if (temp[j] == '/')
				dem++;
			if (temp[j] != '/')
			{
				intc = temp[j] - '0';
				switch (dem)
				{
				case 0:
				{
					carr[i].end.d = carr[i].end.d * 10 + (intc);
					break;
				}
				case 1:
				{
					carr[i].end.m = carr[i].end.m * 10 + (intc);
					break;
				}
				case 2:
				{
					carr[i].end.y = carr[i].end.y * 10 + (intc);
					break;
				}
				}
			}
		}
		readString(temp, f);
		dem = 0;
		carr[i].from.m = 0;
		carr[i].from.h = 0;
		for (int j = 0; j < strlen(temp); j++)
		{
			if (temp[j] == ':')
				dem++;
			if (temp[j] != ':')
			{
				intc = temp[j] - '0';
				switch (dem)
				{
				case 0:
				{
					carr[i].from.h = carr[i].from.h * 10 + (intc);
					break;
				}
				case 1:
				{
					carr[i].from.m = carr[i].from.m * 10 + (intc);
					break;
				}
				}
			}
		}
		readString(temp, f);
		dem = 0;
		carr[i].to.m = 0;
		carr[i].to.h = 0;
		for (int j = 0; j < strlen(temp); j++)
		{
			if (temp[j] == ':')
				dem++;
			if (temp[j] != ':')
			{
				intc = temp[j] - '0';
				switch (dem)
				{
				case 0:
				{
					carr[i].to.h = carr[i].to.h * 10 + (intc);
					break;
				}
				case 1:
				{
					carr[i].to.m = carr[i].to.m * 10 + (intc);
					break;
				}
				}
			}
		}
		fscanf(f, "%d", &carr[i].dow);
		fscanf(f, "%c", &t);
		i++;
	}
	n = i;
	fclose(f);
}
void ExportCourse(FILE *f, Course cour)
{
	fseek(f, 0, SEEK_END);
	fprintf(f, "\n");
	fprintf(f, "%s", cour.code);
	fprintf(f, ",");
	fprintf(f, "%d", cour.year);
	fprintf(f, ",");
	fprintf(f, "%d", cour.semester);
	fprintf(f, ",");
	for (int i = 0; i < strlen(cour.name); i++)
		fprintf(f, "%c", cour.name[i]);
	fprintf(f, ",");
	for (int i = 0; i < strlen(cour.lecname); i++)
		fprintf(f, "%c", cour.lecname[i]);
	fprintf(f, ",");
	fprintf(f, "%d", cour.start.d);
	fprintf(f, "/");
	fprintf(f, "%d", cour.start.m);
	fprintf(f, "/");
	fprintf(f, "%d", cour.start.y);
	fprintf(f, ",");
	fprintf(f, "%d", cour.end.d);
	fprintf(f, "/");
	fprintf(f, "%d", cour.end.m);
	fprintf(f, "/");
	fprintf(f, "%d", cour.end.y);
	fprintf(f, ",");
	fprintf(f, "%d", cour.from.h);
	fprintf(f, ":");
	fprintf(f, "%d", cour.from.m);
	fprintf(f, ",");
	fprintf(f, "%d", cour.to.h);
	fprintf(f, ":");
	fprintf(f, "%d", cour.to.m);
	fprintf(f, ",");
	fprintf(f, "%d", cour.dow);

}
void ExportCourseList(char* filename, Course arr[], char header[], int n)
{
	FILE *f = fopen(filename, "w");
	for (int i = 0; i < strlen(header); i++)
		fprintf(f, "%c", header[i]);
	for (int i = 0; i < n; i++)
	{
		ExportCourse(f, arr[i]);
	}
	fclose(f);

}
void ImportScoreboardList(char* filename, Score scrarr[], int &n)
{

	FILE *f = fopen(filename, "r");
	char t, temp[255];
	int i = n;
	fgets(temp, 255, f);
	while (!feof(f))
	{
		readString(scrarr[i].code, f);
		fscanf(f, "%d", &scrarr[i].year);
		fscanf(f, "%c", &t);
		fscanf(f, "%d", &scrarr[i].semester);
		fscanf(f, "%c", &t);
		readString(scrarr[i].sid, f);
		fscanf(f, "%f", &scrarr[i].mids);
		fscanf(f, "%c", &t);
		fscanf(f, "%f", &scrarr[i].labs);
		fscanf(f, "%c", &t);
		fscanf(f, "%f", &scrarr[i].finals);
		fscanf(f, "%c", &t);
		i++;
	}
	n = i;
	fclose(f);
}
void ExportScore(FILE *f, Score scr)
{
	fseek(f, 0, SEEK_END);
	fprintf(f, "\n");
	fprintf(f, "%s", scr.code);
	fprintf(f, ",");
	fprintf(f, "%d", scr.year);
	fprintf(f, ",");
	fprintf(f, "%d", scr.semester);
	fprintf(f, ",");
	fprintf(f, "%s", scr.sid);
	fprintf(f, ",");
	fprintf(f, "%f", scr.mids);
	fprintf(f, ",");
	fprintf(f, "%f", scr.labs);
	fprintf(f, ",");
	fprintf(f, "%f", scr.finals);

}
void ExportScoreList(char* filename, Score arr[], char header[], int n)
{
	FILE *f = fopen(filename, "w");
	for (int i = 0; i < strlen(header); i++)
		fprintf(f, "%c", header[i]);
	for (int i = 0; i < n; i++)
	{
		ExportScore(f, arr[i]);
	}
	fclose(f);

}
void ImportPresenceList(char* filename, Presence parr[], int &n)
{

	FILE *f = fopen(filename, "r");
	char t, temp[255], temp1[255], temp2[255];
	int i = n - 1, check = 0, t1, pos, t2;
	fgets(temp, 255, f);
	while (!feof(f))
	{
		check = 0;
		readString(temp1, f);
		readString(temp2, f);
		for (int j = 0; j <= i; j++)
		{
			if (strcmp(temp1, parr[j].code) == 0 && strcmp(temp2, parr[j].sid) == 0)
			{
				check = 1;
				pos = j;
				break;
			}
		}
		if (check == 0) {
			i++;
			for (int j = 0; j < strlen(temp1); j++)
				parr[i].code[j] = temp1[j];
			parr[i].code[strlen(temp1)] = '\0';
			for (int j = 0; j < strlen(temp2); j++)
				parr[i].sid[j] = temp2[j];
			parr[i].sid[strlen(temp2)] = '\0';
		}
		else { t2 = i; i = pos; }
		fscanf(f, "%d", &parr[i].year);
		fscanf(f, "%c", &t);
		fscanf(f, "%d", &parr[i].semester);
		fscanf(f, "%c", &t);
		fscanf(f, "%d", &t1);
		fscanf(f, "%c", &t);
		parr[i].week[t1] = 1;
		if (check == 1) i = t2;
	}
	n = i + 1;
	fclose(f);
}
void ExportPresence(FILE *f, Presence pre, int duration)
{
	for (int i = 1; i <= duration * 4; i++)
	{
		if (pre.week[i] == 1)
		{
			fseek(f, 0, SEEK_END);
			fprintf(f, "\n");
			fprintf(f, "%s", pre.code);
			fprintf(f, ",");
			fprintf(f, "%s", pre.sid);
			fprintf(f, ",");
			fprintf(f, "%d", pre.year);
			fprintf(f, ",");
			fprintf(f, "%d", pre.semester);
			fprintf(f, ",");
			fprintf(f, "%d", i);
		}
	}

}
void ExportPresenceList(char* filename, Presence arr[], char header[], int n, Course cor[], int nc)
{
	FILE *f = fopen(filename, "w");
	int pos, dur;
	for (int i = 0; i < strlen(header); i++)
		fprintf(f, "%c", header[i]);
	for (int i = 0; i < n; i++)
	{
		pos = -1;
		for (int j = 0; j < nc; j++)
		{

			if (strcmp(cor[j].code, arr[i].code) == 0)
			{
				pos = j;
				break;
			}
		}
		if (pos != -1) dur = cor[pos].end.m - cor[pos].start.m + 1;
		else dur = 4;
		if (dur < 0)
			dur = 12 + dur;
		ExportPresence(f, arr[i], dur);
	}
	fclose(f);

}
void ImportStuCourList(char* filename, StuCour scarr[], int &n)
{

	FILE *f = fopen(filename, "r");
	char t, temp[255], temp1[255];
	int i = n - 1, check = 0, t1, pos, t2;
	fgets(temp, 255, f);
	while (!feof(f))
	{
		check = 0;
		readString(temp1, f);
		for (int j = 0; j <= i; j++)
		{
			if (strcmp(temp1, scarr[j].code) == 0)
			{
				check = 1;
				pos = j;
				break;
			}
		}
		if (check == 0) {
			i++;
			scarr[i].size = 0;
			for (int j = 0; j < strlen(temp1); j++)
				scarr[i].code[j] = temp1[j];
			scarr[i].code[strlen(temp1)] = '\0';
		}
		else { t2 = i; i = pos; scarr[i].size += 1; }
		readString(scarr[i].sid[scarr[i].size], f);
		if (check == 1) i = t2;
	}
	n = i + 1;
	fclose(f);
}
void ExportStuCour(FILE *f, StuCour scr)
{
	for (int i = 0; i <= scr.size; i++)
	{
		fseek(f, 0, SEEK_END);
		fprintf(f, "\n");
		fprintf(f, "%s", scr.code);
		fprintf(f, ",");
		fprintf(f, "%s", scr.sid[i]);
	}

}
void ExportStuCourList(char* filename, StuCour arr[], char header[], int n)
{
	FILE *f = fopen(filename, "w");
	for (int i = 0; i < strlen(header); i++)
		fprintf(f, "%c", header[i]);
	for (int i = 0; i < n; i++)
	{
		ExportStuCour(f, arr[i]);
	}
	fclose(f);

}
void PrintNameTable(char *s)
{
	int n = strlen(s);
	n = 25 - n / 2;
	gotoxy(35 + n, 4);
	textcolor(12);
	printf("%s", s);
	gotoxy(0, 0);
}
void createMainMenu(Array &arr, Size &n)
{
	Menu menu;
	int x;
	int number = 3, start = 0;
	int line = 6;
	bool thoat = false;
	menu.printMenu(start, number);
	PrintNameTable("Student Info Manager");
	gotoxy(36, line);
	textcolor(4);
	cout << (char)32; //Vẽ con trỏ trỏ tới men3
	while (!thoat) {

		if (_kbhit()) {

			x = move();

			gotoxy(36, line);
			printf(" "); //Xóa con trỏ ở vị trí cũ

			switch (x) {

			case 1:

			case 3:
			{
				line++;
				if (line >= number + 6) line = 6;
				break;

			}

			case 2:

			case 4:
			{
				line--;
				if (line < 6) line = number - 1 + 6;
				break;
			}

			case 5:
			{

				/*gotoxy(0, 10);
				cout << "                                           ";

				gotoxy(0, 10);
				cout << "Ban chon " << menu.getItem()[line];*/
				switch (line) {
				case 6: // Chon Log In
				{
					menu.deleteMenu(start, number);
					createLogIn(arr, n);
					break;
				}
				case 7:
				{
					ViewCredit();
					break;
				}
				case 8:
				{
					return;
				}
				}
				ClearScreen();
				menu.printMenu(start, number);
				PrintNameTable("Student Info Manager");
				break;

			}

			case 8:
				thoat = true;
			}

			gotoxy(36, line);
			cout << (char)32;

		}

	}
	menu.deleteMenu(start, number);
}
void createLogIn(Array &arr, Size &n)
{
	Menu menu;
	int x, dem = 0;
	int start = 42;
	int number = 3;
	int line = 6;
	bool thoat = false;
	int kt = 0, vt = 0, ktlogout = 0;
	char  username[15], pass[30];
	ClearScreen();
	menu.printMenu(start, number);
	PrintNameTable("Login your account");
	gotoxy(36, line);
	textcolor(12);
	cout << (char)32; //Vẽ con trỏ trỏ tới menu

	while (!thoat) {

		if (_kbhit()) {

			x = move();
			gotoxy(36, line);
			cout << " "; //Xóa con trỏ ở vị trí cũ

			switch (x) {
			case 1:
			case 3:
			{
				line++;
				if (line >= number + 6)
					line = 6;
				break;
			}
			case 2:
			case 4:
			{
				line--;
				if (line < 6)
					line = number - 1 + 6;
				break;
			}
			case 5:
			{
				/*gotoxy(0, 10);
				cout << "                                           ";
				gotoxy(0, 10);
				cout << "Ban chon " << menu.getItem()[line];*/
				switch (line) {
				case 6:
				{
					kt = 0;
					while (kt == 0)
					{
						textcolor(15);
						ClearScreen();
						printf("Enter Username: \n");
						printf("Press Esc to exit!\n");
						gotoxy(16, 0);
						fflush(stdin);
						int i = 0;
						char ch = _getch();
						while (ch != 13) {//character 13 is enter
							if (ch == 8 || ch == 127) {
								i--;
								if (i != -1)
								{
									gotoxy(16 + i, 0);
									cout << " ";
									gotoxy(16 + i, 0);
								}
							}
							else if (ch == 27)
							{
								kt = 3;
								break;
							}
							else
							{
								username[i] = ch;
								i++;
								cout << ch;
							}
							if (i < 0) i = 0;

							ch = _getch();
						}
						if (kt == 3) break;
						username[i] = '\0';
						for (int i = 0; i < n.stud; i++)
							if (strcmp(username, arr.stud[i].username) == 0)
							{
								kt = 1;
								vt = i;
								break;
							}
						if (kt == 0)
						{
							textcolor(12);

							dem = dem + 1;
							gotoxy(0, 2);
							if (dem == 4)
							{

								printf("Wrong Username\n");
								Sleep(500);
								break;
							}

							printf("Wrong Username\n");
							printf("You have %d more tries", 4 - dem);
							Sleep(1000);
							textcolor(15);
						}
					}
					dem = 0;
					break;
				}
				case 7:
				{
					if (kt == 1)
						kt = 0;
					else
					{
						ClearScreen();
						textcolor(12);
						printf("Enter username first");
						textcolor(15);
						Sleep(500);
						break;
					}
					while (kt == 0)
					{
						ClearScreen();
						textcolor(15);
						printf("Enter password: \n");
						cout << "Press Esc to exit!";
						gotoxy(16, 0);
						fflush(stdin);
						int i = 0;
						char ch = _getch();
						while (ch != 13) {//character 13 is enter
							if (ch == 8 || ch == 127) {
								i--;
								if (i != -1)
								{
									gotoxy(16 + i, 0);
									cout << " ";
									gotoxy(16 + i, 0);
								}
							}
							else
							{
								if (ch == 27)
								{
									kt = 1;
									break;
								}
								pass[i] = ch;
								i++;
								cout << '*';
							}
							if (i < 0) i = 0;

							ch = _getch();
						}
						if (kt == 1) break;
						pass[i] = '\0';
						if (strcmp(arr.stud[vt].password, pass) == 0)
						{
							kt = 1;
							switch (arr.stud[vt].type)
							{
							case 0:
							{
								if (createStuMenu(arr, n, vt) == 1)
									ktlogout = 1;
								break;
							}
							case 1:
							{
								if (createAcaMenu(arr, n, vt) == 1)
									ktlogout = 1;
								break;
							}
							case 2:
							{
								if (createLecMenu(arr, n, vt) == 1)
									ktlogout = 1;
								break;
							}
							}
						}
						else
						{
							textcolor(12);
							gotoxy(0, 1);
							printf("\n");
							printf("Wrong Password\n");
							dem = dem + 1;
							if (dem == 4)
							{
								printf("Wrong Password\n");
								Sleep(500);
								break;
							}
							printf("You have %d more tries", 4 - dem);
							Sleep(500);
							textcolor(15);
						}
					}
					dem = 0;
					break;
				}
				case 8:
				{
					ClearScreen();
					if (kt == 1)
						ChangePassword(arr.stud, vt);
					else {
						printf("Enter Username first");
						Sleep(500);
					}
					break;
				}
				}
				ClearScreen();
				menu.printMenu(start, number);
				PrintNameTable("Login your account");
				break;

			}
			case 8:
				thoat = true;
			}
			gotoxy(36, line);
			cout << (char)32;
		}
	}
	menu.deleteMenu(start, number);
}
void ChangePassword(User arr[], int vt)
{
	char pass[20], newpass[20], newpass1[20];
	while (1)
	{
		printf("Enter old password (enter N to quit): ");
		fflush(stdin);
		gets_s(pass, 20);
		if (strcmp(pass, "N") == 0)
			return;
		if (strcmp(arr[vt].password, pass) == 0)
		{
			while (1)
			{
				ClearScreen();
				printf("Enter new password: ");
				fflush(stdin);
				gets_s(newpass, 20);
				printf("Enter new password again: ");
				fflush(stdin);
				gets_s(newpass1, 20);
				if (strcmp(newpass, newpass1) == 0)
				{
					for (int i = 0; i < strlen(newpass); i++)
					{
						arr[vt].password[i] = newpass[i];
					}
					arr[vt].password[strlen(newpass)] = '\0';
					printf("Change password sucessful");
					Sleep(1000);
					return;
				}
				else {
					printf("Enter password again wrong");
					Sleep(1000);
				}
			}
		}
		else {
			printf("Enter old password wrong");
			Sleep(1000);
			ClearScreen();
		}
	}
}
int createAcaMenu(Array &arr, Size &n, int pos)
{
	Menu menu;
	int x;
	int start = 3;
	int number = 6;
	int line = 0;
	bool thoat = false;
	ClearScreen();
	menu.printMenu(start, number);
	PrintNameTable("Academic staff menu");

	gotoxy(36, line + 6);
	cout << (char)32; //Vẽ con trỏ trỏ tới menu

	while (!thoat) {

		if (_kbhit()) {

			x = move();
			gotoxy(36, line + 6);
			cout << " "; //Xóa con trỏ ở vị trí cũ

			switch (x) {
			case 1:
			case 3:
			{
				line++;
				if (line >= number)
					line = 0;
				break;
			}
			case 2:
			case 4:
			{
				line--;
				if (line < 0)
					line = number - 1;
				break;
			}
			case 5:
			{
				/*gotoxy(0, 10);
				cout << "                                           ";
				gotoxy(0, 10);
				cout << "Ban chon " << menu.getItem()[line];*/
				switch (line) {
				case 0:
				{
					return 1;
				}
				case 1:
				{
					ShowInfo(arr.stud[pos]);
					break;
				}
				case 2:
				{
					createStudMaMenu(arr.stud, n.stud);
					break;
				}
				case 3:
				{
					createCourseMaMenu(arr.course, n.course);
					break;
				}
				case 4:
				{
					createCourseScheMaMenu(arr.course, n.course);
					break;
				}
				case 5:
				{
					createScoreandAttendMaMenu(arr, n);
					break;
				}
				}
				ClearScreen();
				menu.printMenu(start, number);
				PrintNameTable("Academic staff menu");
				break;

			}
			case 8:
				thoat = true;
			}
			gotoxy(36, line + 6);
			cout << (char)32;
		}
	}
	menu.deleteMenu(start, number);
	return 0;
}
int createStuMenu(Array &arr, Size &n, int pos) {
	Menu menu;
	int x;
	int start = 36;
	int number = 6;
	int line = 0;
	bool thoat = false;
	ClearScreen();
	menu.printMenu(start, number);
	PrintNameTable("Student menu ");
	gotoxy(36, line + 6);
	cout << (char)32; //Vẽ con trỏ trỏ tới menu

	while (!thoat) {

		if (_kbhit()) {

			x = move();
			gotoxy(36, line + 6);
			cout << " "; //Xóa con trỏ ở vị trí cũ

			switch (x) {
			case 1:
			case 3:
			{
				line++;
				if (line >= number)
					line = 0;
				break;
			}
			case 2:
			case 4:
			{
				line--;
				if (line < 0)
					line = number - 1;
				break;
			}
			case 5:
			{
				/*gotoxy(0, 10);
				cout << "                                           ";
				gotoxy(0, 10);
				cout << "Ban chon " << menu.getItem()[line];*/
				switch (line) {
				case 0:
				{
					return 1;
				}
				case 1:
				{
					ShowInfo(arr.stud[pos]);
					break;
				}
				case 2:
				{
					CheckIn(arr, n, pos);
					break;
				}
				case 3:
				{
					ViewCheckIn(arr, n, pos);
					break;
				}
				case 4:
				{
					ViewScoreBoard(arr, n, pos);
					break;
				}
				case 5:
				{
					ViewSchedule(arr, n, pos);
					break;
				}
				}
				ClearScreen();
				menu.printMenu(start, number);
				PrintNameTable("Student menu ");
				break;

			}
			case 8:
				thoat = true;
			}
			gotoxy(36, line + 6);
			cout << (char)32;
		}
	}
	menu.deleteMenu(start, number);
	return 0;
}
int createLecMenu(Array &arr, Size &n, int pos) {
	Menu menu;
	int x;
	int start = 31;
	int number = 5;
	int line = 0;
	bool thoat = false;
	ClearScreen();
	menu.printMenu(start, number);
	PrintNameTable("Lecturer menu");
	gotoxy(36, line + 6);
	cout << (char)32; //Vẽ con trỏ trỏ tới menu

	while (!thoat) {

		if (_kbhit()) {

			x = move();
			gotoxy(36, line + 6);
			cout << " "; //Xóa con trỏ ở vị trí cũ

			switch (x) {
			case 1:
			case 3:
			{
				line++;
				if (line >= number)
					line = 0;
				break;
			}
			case 2:
			case 4:
			{
				line--;
				if (line < 0)
					line = number - 1;
				break;
			}
			case 5:
			{
				/*gotoxy(0, 10);
				cout << "                                           ";
				gotoxy(0, 10);
				cout << "Ban chon " << menu.getItem()[line];*/
				switch (line) {
				case 0:
				{
					return 1;
				}
				case 1:
				{
					ShowInfo(arr.stud[pos]);
					break;
				}
				case 2:
				{
					ImportScoreBoard(arr.score, n.score);
					break;
				}
				case 3:
				{
					EditGrade(arr.score, n.score);
					break;
				}
				case 4:
				{
					ViewScore(arr.score, n.score);
					break;
				}
				}
				ClearScreen();
				menu.printMenu(start, number);
				PrintNameTable("Lectuer menu");
				break;

			}
			case 8:
				thoat = true;
			}
			gotoxy(36, line + 6);
			cout << (char)32;
		}
	}
	menu.deleteMenu(start, number);
	return 0;
}
void ShowInfo(User user)
{
	char ex;
	ClearScreen();
	textcolor(10);
	printf("Username: ");
	puts(user.username);
	printf("Fullname: ");
	puts(user.fullname);
	printf("Email: ");
	puts(user.email);
	printf("Mobile Phone: ");
	puts(user.mbphone);
	printf("Type: ");
	if (user.type == Student)
		printf("Student");
	else if (user.type == Academic_Staff)
		printf("Academic Staff");
	else
		printf("Lecturer");
	printf("\n");
	if (user.type == Student)
	{
		printf("Class: ");
		puts(user.Class);
	}
	printf("\n\n\n");
	textcolor(15);
	printf("Enter any character to exit: ");
	fflush(stdin);
	scanf_s("%c", &ex);
	char c;
	scanf_s("%c", &c);
}
void createStudMaMenu(User stud[], int &n)
{
	Menu menu;
	int x;
	int start = 9;
	int number = 8;
	int line = 0;
	int ncl;
	bool thoat = false;
	char arrclass[100][15];
	ClearScreen();

	createClassArr(stud, n, arrclass, ncl);

	menu.printMenu(start, number);
	PrintNameTable("Student manager menu");

	gotoxy(36, line + 6);
	cout << (char)32; //Vẽ con trỏ trỏ tới menu

	while (!thoat) {

		if (_kbhit()) {

			x = move();
			gotoxy(36, line + 6);
			cout << " "; //Xóa con trỏ ở vị trí cũ

			switch (x) {
			case 1:
			case 3:
			{
				line++;
				if (line >= number)
					line = 0;
				break;
			}
			case 2:
			case 4:
			{
				line--;
				if (line < 0)
					line = number - 1;
				break;
			}
			case 5:
			{
				/*gotoxy(0, 10);
				cout << "                                           ";
				gotoxy(0, 10);
				cout << "Ban chon " << menu.getItem()[line];*/
				switch (line) {
				case 0:
				{
					ImportClass(stud, n, arrclass, ncl);
					break;
				}
				case 1:
				{
					AddStudenttoClass(stud, n, arrclass, ncl);
					break;
				}
				case 2:
				{
					EditStudent(stud, n);
					break;
				}
				case 3:
				{
					RemoveStudent(stud, n);
					break;
				}
				case 4:
				{
					ChangeStudentClass(stud, n, arrclass, ncl);
					break;
				}
				case 5:
				{
					AddNewClass(arrclass, ncl);
					break;
				}
				case 6:
				{
					ViewListofClass(arrclass, ncl);
					break;
				}
				case 7:
				{
					ViewListofStudentinClass(stud, n, arrclass, ncl);
					break;
				}
				}
				ClearScreen();
				menu.printMenu(start, number);
				PrintNameTable("Student manager menu");
				break;

			}
			case 8:
				thoat = true;
			}
			gotoxy(36, line + 6);
			cout << (char)32;
		}
	}
	menu.deleteMenu(start, number);
}

void createCourseMaMenu(Course course[], int &n)
{
	Menu menu;
	int x;
	int start = 17;
	int number = 5;
	int line = 0;
	bool thoat = false;
	ClearScreen();
	menu.printMenu(start, number);
	PrintNameTable("Course manager menu");
	gotoxy(36, line + 6);
	cout << (char)32; //Vẽ con trỏ trỏ tới menu

	while (!thoat) {

		if (_kbhit()) {

			x = move();
			gotoxy(36, line + 6);
			cout << " "; //Xóa con trỏ ở vị trí cũ

			switch (x) {
			case 1:
			case 3:
			{
				line++;
				if (line >= number)
					line = 0;
				break;
			}
			case 2:
			case 4:
			{
				line--;
				if (line < 0)
					line = number - 1;
				break;
			}
			case 5:
			{
				/*gotoxy(0, 10);
				cout << "                                           ";
				gotoxy(0, 10);
				cout << "Ban chon " << menu.getItem()[line];*/
				switch (line) {
				case 0:
				{
					ImportCourse(course, n);
					break;
				}
				case 1:
				{
					AddNewCourse(course, n);
					break;
				}
				case 2:
				{
					EditCourse(course, n);
					break;
				}
				case 3:
				{
					RemoveCourse(course, n);
					break;
				}
				case 4:
				{
					ViewListofCourse(course, n);
					break;
				}
				}
				ClearScreen();
				menu.printMenu(start, number);
				PrintNameTable("Course manager menu");
				break;

			}
			case 8:
				thoat = true;
			}
			gotoxy(36, line + 6);
			cout << (char)32;
		}
	}
	menu.deleteMenu(start, number);
}
void createCourseScheMaMenu(Course course[], int &n)
{
	Menu menu;
	int x;
	int start = 22;
	int number = 5;
	int line = 0;
	bool thoat = false;
	ClearScreen();
	menu.printMenu(start, number);
	PrintNameTable("Course schedule menu");
	gotoxy(36, line + 6);
	cout << (char)32; //Vẽ con trỏ trỏ tới menu

	while (!thoat) {

		if (_kbhit()) {

			x = move();
			gotoxy(36, line + 6);
			cout << " "; //Xóa con trỏ ở vị trí cũ

			switch (x) {
			case 1:
			case 3:
			{
				line++;
				if (line >= number)
					line = 0;
				break;
			}
			case 2:
			case 4:
			{
				line--;
				if (line < 0)
					line = number - 1;
				break;
			}
			case 5:
			{
				/*gotoxy(0, 10);
				cout << "                                           ";
				gotoxy(0, 10);
				cout << "Ban chon " << menu.getItem()[line];*/
				switch (line) {
				case 0:
				{
					ImportSchedule(course, n);
					break;
				}
				case 1:
				{
					AddCourseSchedules(course, n);
					break;
				}
				case 2:
				{
					EditCourseSchedules(course, n);
					break;
				}
				case 3:
				{
					RemoveCourseSchedules(course, n);
					break;
				}
				case 4:
				{
					ViewListOfSchedules(course, n);
					break;
				}
				}
				ClearScreen();
				menu.printMenu(start, number);
				PrintNameTable("Course schedule menu");
				break;

			}
			case 8:
				thoat = true;
			}
			gotoxy(36, line + 6);
			cout << (char)32;
		}
	}
	menu.deleteMenu(start, number);
}
void createScoreandAttendMaMenu(Array &arr, Size &n)
{
	Menu menu;
	int x;
	int start = 27;
	int number = 4;
	int line = 0;
	bool thoat = false;
	ClearScreen();
	menu.printMenu(start, number);
	PrintNameTable("Score and Attend manager menu");
	gotoxy(36, line + 6);
	cout << (char)32; //Vẽ con trỏ trỏ tới menu

	while (!thoat) {

		if (_kbhit()) {

			x = move();
			gotoxy(36, line + 6);
			cout << " "; //Xóa con trỏ ở vị trí cũ

			switch (x) {
			case 1:
			case 3:
			{
				line++;
				if (line >= number)
					line = 0;
				break;
			}
			case 2:
			case 4:
			{
				line--;
				if (line < 0)
					line = number - 1;
				break;
			}
			case 5:
			{
				/*gotoxy(0, 10);
				cout << "                                           ";
				gotoxy(0, 10);
				cout << "Ban chon " << menu.getItem()[line];*/
				switch (line) {
				case 0:
				{
					Search_and_view_attendance_list_of_a_course(arr.presence, n.presence);
					break;
				}
				case 1:
				{
					Export_attendance_list_to_a_csv_file(arr, n);
					break;
				}
				case 2:
				{
					Search_and_view_scoreboard_of_a_course(arr.score, n.score);
					break;
				}
				case 3:
				{
					Export_a_scoreboard_to_a_csv_file(arr, n);
					break;
				}
				}
				ClearScreen();
				menu.printMenu(start, number);
				PrintNameTable("Score and Attend manager menu");
				break;

			}
			case 8:
				thoat = true;
			}
			gotoxy(36, line + 6);
			cout << (char)32;
		}
	}
	menu.deleteMenu(start, number);
}

////////////////////// PA03 //////////////////////////////////
void AddStudenttoClass(User arr[], int &n, char arrclass[][15],int &ncl)
{
	ClearScreen();
	char name[15];
	int x;
	textcolor(15);
	printf("Enter Class Name: ");
	fflush(stdin);
	gets_s(name,15);
	for (int i = 0;i < ncl;i++)
	{
		if (strcmp(name, arrclass[i]) == 0)
		{
			
			printf("Enter Username:");
			fflush(stdin);
			gets_s(arr[n].username, 15);
			printf("Enter Full Name:");
			fflush(stdin);
			gets_s(arr[n].fullname, 15);
			printf("Enter Email:");
			fflush(stdin);
			gets_s(arr[n].email, 50);
			printf("Enter mobilephone:");
			fflush(stdin);
			gets_s(arr[n].mbphone, 15);
			printf("Enter password:");
			fflush(stdin);
			gets_s(arr[n].password, 20);
			arr[n].type = Student;
			for (int j = 0;j < strlen(name);j++)
				arr[n].Class[j] = name[j];
			arr[n].Class[strlen(name)] = '\0';
			n++;
			textcolor(10);
			printf("Add Student Successfully!\n");
			puts("Press any key to continue.");
			x = _getch();
			return;
		}
	}
	textcolor(12);
	printf("Class not found!\n");
	puts("Press any key to continue.");
	x = _getch();
	return;
}
void EditStudent(User arr[], int n)
{
	ClearScreen();
	char name[15];
	int x;
	textcolor(15);
	printf("Enter Student ID: ");
	fflush(stdin);
	gets_s(name, 15);
	for (int i = 0;i < n;i++)
	{
		if (strcmp(name, arr[i].username) == 0)
		{
			textcolor(10);
			printf("Enter Username:");
			fflush(stdin);
			gets_s(arr[i].username, 15);
			printf("Enter Full Name:");
			fflush(stdin);
			gets_s(arr[i].fullname, 15);
			printf("Enter Email:");
			fflush(stdin);
			gets_s(arr[i].email, 50);
			printf("Enter mobilephone:");
			fflush(stdin);
			gets_s(arr[i].mbphone, 15);
			textcolor(10);
			printf("Edit Student Successfully!\n");
			puts("Press any key to continue.");
			x = _getch();
			return;
		}
	}
	textcolor(12);
	printf("Student ID not found!\n");
	puts("Press any key to continue.");
	x = _getch();
	return;
}
void RemoveStudent(User arr[], int &n)
{
	ClearScreen();
	char name[15];
	int x;
	textcolor(15);
	printf("Enter Student ID: ");
	fflush(stdin);
	gets_s(name, 15);
	for (int i = 0;i < n;i++)
	{
		if (strcmp(name, arr[i].username) == 0)
		{
			n--;
			for (int j = i; j < n; j++)
				arr[j] = arr[j + 1];
			textcolor(10);
			printf("Remove Student Successfully!\n");
			puts("Press any key to continue.");
			x = _getch();
			return;
		}
	}
	textcolor(12);
	printf("Student ID not found!\n");
	puts("Press any key to continue.");
	x = _getch();
	return;
}
void ChangeStudentClass(User arr[], int &n, char arrclass[][15], int &ncl)
{
	ClearScreen();
	char name[15];
	int x,kt=0;
	textcolor(15);
	printf("Enter Student ID: ");
	fflush(stdin);
	gets_s(name, 15);
	for (int i = 0;i < n;i++)
	{
		if (strcmp(name, arr[i].username) == 0)
		{
			kt = 2;
			printf("Enter Class Name: ");
			fflush(stdin);
			gets_s(name, 15);
			for (int j = 0;j < ncl;j++)
			{
				if (strcmp(name, arrclass[j]) == 0)
				{
					kt = 1;
					for (int k = 0;k < strlen(name);k++)
						arr[i].Class[k] = name[k];
					arr[i].Class[strlen(name)] = '\0';
					textcolor(10);
					printf("Change Student's Class Successfully!\n");
					puts("Press any key to continue.");
					x = _getch();
					return;
				}
			}
		
		}
	}
	textcolor(12);
	if (kt==0) printf("Student ID not found!\n");
	else printf("Class not found!\n");
	puts("Press any key to continue.");
	x = _getch();
	return;
}
bool CheckSameName(char *s, char arrclass[][15], int &ncl)
{
	for (int i = 0; i < ncl; ++i)
	{
		if (!strcmp(s, arrclass[i]))
			return true;
	}
	return false;
}
void createClassArr(User arr[], int &n, char arrclass[][15], int &ncl)
{
	ncl = 0;
	for (int i = 0; i < n; ++i)
	{
		if ((!CheckSameName(arr[i].Class, arrclass, ncl)) && (arr[i].type == 0))
		{
			strcpy(arrclass[ncl], arr[i].Class);
			++ncl;
		}
	}
}

void ImportClass(User studarr[], int &n, char arrclass[][15], int &ncl)
{
	textcolor(15);
	ClearScreen();
	char filename[50];
	printf("Name of csv file which have a list of students of a class: ");
	gets_s(filename, 50);

	if (!checkFile(filename)) return;
	ImportStudentList(filename, studarr, n);
	createClassArr(studarr, n, arrclass, ncl);
}


void AddNewClass(char arrclass[][15], int &ncl)
{
	int x;
	textcolor(15);
	ClearScreen();
	char nameClass[15];
	while (1)
	{
		printf("Name of new class: ");
		gets_s(nameClass, 15);
		if (CheckSameName(nameClass, arrclass, ncl) == true)
		{
			textcolor(12);
			printf("Class already exist\n");
			puts("Press any key to continue.");
			x = _getch();
			return;
		}
		else break;
	}
	strcpy(arrclass[ncl], nameClass);
	++ncl;
}


void ViewListofClass(char arrclass[][15], int ncl)
{
	textcolor(15);
	ClearScreen();
	printf("Number of Class: %d\n", ncl);
	for (int i = 0; i < ncl; ++i)
	{
		printf("%d. %s.\n", i + 1, arrclass[i]);
	}
	textcolor(10);
	printf("---->Press Esc to back");
	while (1)
	{
		if (_kbhit())
		{
			int x = _getch();
			if (x == 27) break;
		}
	}
}


void ViewListofStudentinClass(User studarr[], int &n, char arrclass[][15], int &ncl)
{
	textcolor(15);
	ClearScreen();
	char nameclass[15];
	printf("Name of Class: ");
	gets_s(nameclass, 15);
	int j = 1;
	for (int i = 0; i < n; ++i)
	{
		if (!strcmp(studarr[i].Class, nameclass))
		{
			printf("%d. %s %s\n", j, studarr[i].fullname, studarr[i].username);
			++j;
		}
	}
	textcolor(10);
	printf("---->Press Esc to back");
	while (1)
	{
		if (_kbhit())
		{
			int x = _getch();
			if (x == 27) break;
		}
	}
}
////////////////////// PA03 //////////////////////////////////

////////////////////// PA04 //////////////////////////////////
void ImportCourse(Course carr[], int &n)
{
	textcolor(15);
	ClearScreen();
	printf("Name of csv file which have a list of courses: ");
	char filename[255];
	gets_s(filename);
	if (!checkFile(filename)) return;
	ImportCourseList(filename, carr, n);
	textcolor(10);
	puts("Import List of Courses successfully!");
	puts("Press any key to continue.");
	char anyk[256];
	gets_s(anyk);
}
void AddNewCourse(Course carr[], int &n)
{
	textcolor(15);
	ClearScreen();
	puts("ADDING NEW COURSE:");
	printf("Enter course code: ");
	gets_s(carr[n].code);
	printf("Enter course year: ");
	scanf_s("%d", &carr[n].year);
	printf("Enter course semster: ");
	scanf_s("%d", &carr[n].semester);
	gets_s(carr[n].name);
	printf("Enter course name: ");
	gets_s(carr[n].name);
	printf("Enter course lecturer name: ");
	gets_s(carr[n].lecname);
	/*printf("Enter course starting year: ");
	scanf_s("%d", &carr[n].start.y);
	printf("Enter course starting month: ");
	scanf_s("%d", &carr[n].start.m);
	printf("Enter course starting day: ");
	scanf_s("%d", &carr[n].start.d);
	printf("Enter course starting hour: ");
	scanf_s("%d", &carr[n].from.h);
	printf("Enter course starting min: ");
	scanf_s("%d", &carr[n].from.m);
	printf("Enter course ending year: ");
	scanf_s("%d", &carr[n].end.y);
	printf("Enter course ending month: ");
	scanf_s("%d", &carr[n].end.m);
	printf("Enter course ending day: ");
	scanf_s("%d", &carr[n].end.d);
	printf("Enter course ending hour: ");
	scanf_s("%d", &carr[n].to.h);
	printf("Enter course ending min: ");
	scanf_s("%d", &carr[n].to.m);
	printf("Enter course day of week(0->6): ");
	scanf_s("%d", &carr[n].dow);*/
	carr[n].start.y = NULL;
	carr[n].start.m = NULL;
	carr[n].start.d = NULL;
	carr[n].end.m = NULL;
	carr[n].end.y = NULL;
	carr[n].end.d = NULL;
	carr[n].from.m = NULL;
	carr[n].from.h = NULL;
	carr[n].to.m = NULL;
	carr[n].to.h = NULL;
	carr[n].dow = Nullday;
	n++;
	textcolor(10);
	puts("Add Course successfully!");
	puts("Press any key to continue.");
	char anyk[256];
	gets_s(anyk);
}
void EditCourse(Course carr[], int &n)
{
	textcolor(15);
	ClearScreen();
	char code[15];
	char anyk[256];
	printf("Enter course code: ");
	gets_s(code);
	for (int i = 0; i < n; i++)
		if (strcmp(code, carr[i].code) == 0)
		{
			printf("EDITING COURSE CODE %s\n", carr[i].code);
			printf("Enter course code: ");
			gets_s(carr[i].code);
			printf("Enter course year: ");
			scanf_s("%d", &carr[i].year);
			printf("Enter course semster: ");
			scanf_s("%d", &carr[i].semester);
			gets_s(carr[i].name);
			printf("Enter course name: ");
			gets_s(carr[i].name);
			printf("Enter course lecturer name: ");
			gets_s(carr[i].lecname);
			/*printf("Enter course starting year: ");
			scanf_s("%d", &carr[i].start.y);
			printf("Enter course starting month: ");
			scanf_s("%d", &carr[i].start.m);
			printf("Enter course starting day: ");
			scanf_s("%d", &carr[i].start.d);
			printf("Enter course starting hour: ");
			scanf_s("%d", &carr[i].from.h);
			printf("Enter course starting min: ");
			scanf_s("%d", &carr[i].from.m);
			printf("Enter course ending year: ");
			scanf_s("%d", &carr[i].end.y);
			printf("Enter course ending month: ");
			scanf_s("%d", &carr[i].end.m);
			printf("Enter course ending day: ");
			scanf_s("%d", &carr[i].end.d);
			printf("Enter course ending hour: ");
			scanf_s("%d", &carr[i].to.h);
			printf("Enter course ending min: ");
			scanf_s("%d", &carr[i].to.m);
			printf("Enter course day of week(0->6): ");
			scanf_s("%d", &carr[i].dow);*/
			textcolor(10);
			puts("Edit Course successfully!");
			puts("Press any key to continue.");
			gets_s(anyk);
			return;
		}
	textcolor(12);
	puts("Course not found!");
	puts("Press any key to continue!");
	gets_s(anyk);
}
void RemoveCourse(Course carr[], int &n)
{
	textcolor(15);
	ClearScreen();
	char code[15];
	char anyk[256];
	printf("Enter Course Code: ");
	gets_s(code);
	for (int i = 0; i < n; i++)
		if (strcmp(carr[i].code, code) == 0)
		{
			n--;
			for (int j = i; j < n; j++)
				carr[j] = carr[j + 1];
			textcolor(10);
			puts("Delete course successfully!");
			puts("Press any key to continue!");
			gets_s(anyk);
			return;
		}
	textcolor(12);
	puts("Course not found!");
	puts("Press any key to continue!");
	gets_s(anyk);
}

void ViewListofCourse(Course carr[], int &n)
{
	ClearScreen();
	textcolor(15);
	for (int i = 0; i < n; i++)
	{
		printf("%d.\n", i + 1);
		printf("Course Code: ");
		puts(carr[i].code);
		printf("Year: %d\n", carr[i].year);
		printf("Semester: %d\n", carr[i].semester);
		printf("Name: ");
		puts(carr[i].name);
		printf("Lecturer Name: ");
		puts(carr[i].lecname);
		/*printf("Start on : %d/%d/%d\n", carr[i].start.d, carr[i].start.m, carr[i].start.y);
		printf("End on : %d/%d/%d\n", carr[i].end.d, carr[i].end.m, carr[i].end.y);
		printf("From : %d:%d  ", carr[i].from.h, carr[i].from.m);
		printf("To : %d:%d  ", carr[i].to.h, carr[i].to.m);
		switch (carr[i].dow)
		{
		case Monday:printf("on Monday"); break;
		case Tuesday:printf("on Tuesday"); break;
		case Wednesday:printf("on Wednesday"); break;
		case Thursday:printf("on Thursday"); break;
		case Friday:printf("on Friday"); break;
		case Saturday:printf("on Saturday"); break;
		case Sunday:printf("on Sunday"); break;
		case Nullday:printf("on N/A");break;
		}
		printf("\n");*/
		puts("__________");
	}
	textcolor(10);
	puts("Press any key to continue.");
	char anyk[256];
	gets_s(anyk);
}
////////////////////// PA04 //////////////////////////////////
////////////////////// 31-34 /////////////////////////////////
void CheckIn(Array &arr, Size &n, int pos)
{
	int loc = 19, kt = 0, dem = 0, week, pos1, pos2, dur;
	char code[15];
	while (kt == 0)
	{
		textcolor(15);
		ClearScreen();
		printf("Enter Course Code: \n");
		printf("Press Esc to exit!\n");
		gotoxy(loc, 0);
		fflush(stdin);
		int i = 0;
		char ch = _getch();
		while (ch != 13) {//character 13 is enter
			if (ch == 8 || ch == 127) {
				i--;
				if (i != -1)
				{
					gotoxy(loc + i, 0);
					cout << " ";
					gotoxy(loc + i, 0);
				}
			}
			else if (ch == 27)
			{
				kt = 2;
				break;
			}
			else
			{
				code[i] = ch;
				i++;
				cout << ch;
			}
			if (i < 0) i = 0;

			ch = _getch();
		}
		if (kt == 2) return;
		code[i] = '\0';
		ClearScreen();
		for (int i = 0; i < n.stucour; i++)
		{
			if (strcmp(code, arr.stucour[i].code) == 0)
			{
				for (int j = 0; j <= arr.stucour[i].size; j++)
				{
					if (strcmp(arr.stud[pos].username, arr.stucour[i].sid[j]) == 0)
					{
						kt = 1;
						break;
					}
				}
			}
		}
		if (kt == 0)
		{
			textcolor(12);
			gotoxy(0, 2);
			printf("You have not registered this course\n");
			Sleep(1000);
			textcolor(15);
		}
	}
	for (int i = 0; i < n.course; i++)
		if (strcmp(code, arr.course[i].code) == 0)
		{
			pos1 = i;
			break;
		}
	for (int i = 0; i < n.presence; i++)
		if (strcmp(code, arr.presence[i].code) == 0 && (strcmp(arr.stud[pos].username, arr.presence[i].sid) == 0))
		{
			pos2 = i;
			break;
		}
	while (1)
	{
		ClearScreen();
		printf("Enter week to check in(-1 to exit): ");
		scanf_s("%d", &week);
		if (week == -1) return;
		if (pos1 != -1) dur = arr.course[pos1].end.m - arr.course[pos1].start.m + 1;
		else dur = 4;
		if (dur < 0)
			dur = 12 + dur;
		textcolor(12);
		if (arr.presence[pos2].week[week] != 1 && week >= 1 && week <= dur * 4)
		{
			textcolor(10);
			arr.presence[pos2].week[week] = 1;
			printf("Check in successfully!!");
			Sleep(1000);
			textcolor(15);
			return;
		}
		else if (week<1 || week>dur * 4)
		{
			textcolor(12);
			printf("Out of bound!");
			Sleep(1000);
		}
		else
		{
			textcolor(12);
			printf("Already Checked In!");
			Sleep(1000);
		}
		textcolor(15);
	}

}
void ViewCheckIn(Array &arr, Size &n, int pos)
{
	int pos1, dur, kt = 0;
	char x;
	ClearScreen();
	for (int i = 0; i < n.presence; i++)
	{
		if (strcmp(arr.presence[i].sid, arr.stud[pos].username) == 0)
		{
			kt = 1;
			textcolor(10);
			printf("Course Code: ");
			puts(arr.presence[i].code);
			printf("Check in result:\n");
			for (int j = 0; j < n.course; j++)
				if (strcmp(arr.presence[i].code, arr.course[j].code) == 0)
				{
					pos1 = j;
					break;
				}
			if (pos1 != -1) dur = arr.course[pos1].end.m - arr.course[pos1].start.m + 1;
			else dur = 4;
			if (dur < 0)
				dur = 12 + dur;
			textcolor(15);
			for (int j = 1; j <= dur * 4; j++)
				if (arr.presence[i].week[j] == 1)
					printf("Week %d\n", j);
		}
	}
	if (kt == 0)
	{
		textcolor(12);
		printf("No Check in result!");
	}
	textcolor(12);
	printf("Enter y to quit: ");
	while (1)
	{

		fflush(stdin);
		scanf_s("%c", &x);
		if (x == 'y')
			return;
	}
}
void ViewScoreBoard(Array &arr, Size &n, int pos)
{
	int loc = 19, kt = 0, dem = 0, week, pos1;
	char code[15], x;
	while (kt == 0)
	{
		textcolor(15);
		ClearScreen();
		printf("Enter Course Code: \n");
		printf("Press Esc to exit!\n");
		gotoxy(loc, 0);
		fflush(stdin);
		int i = 0;
		char ch = _getch();
		while (ch != 13) {//character 13 is enter
			if (ch == 8 || ch == 127) {
				i--;
				if (i != -1)
				{
					gotoxy(loc + i, 0);
					cout << " ";
					gotoxy(loc + i, 0);
				}
			}
			else if (ch == 27)
			{
				kt = 2;
				break;
			}
			else
			{
				code[i] = ch;
				i++;
				cout << ch;
			}
			if (i < 0) i = 0;

			ch = _getch();
		}
		if (kt == 2) return;
		code[i] = '\0';
		ClearScreen();
		for (int i = 0; i < n.stucour; i++)
		{
			if (strcmp(code, arr.stucour[i].code) == 0)
			{
				for (int j = 0; j <= arr.stucour[i].size; j++)
				{
					if (strcmp(arr.stud[pos].username, arr.stucour[i].sid[j]) == 0)
					{
						kt = 1;
						break;
					}
				}
			}
		}
		if (kt == 0)
		{
			textcolor(12);
			gotoxy(0, 2);
			printf("You have not registered this course\n");
			Sleep(1000);
			textcolor(15);
		}
	}
	ClearScreen;
	textcolor(10);
	printf("Course Code: %s\n", code);
	kt = 0;
	for (int i = 0; i < n.score; i++)
		if (strcmp(code, arr.score[i].code) == 0 && (strcmp(arr.stud[pos].username, arr.score[i].sid) == 0))
		{
			kt = 1;
			textcolor(10);
			printf("Year: %d\n", arr.score[i].year);
			printf("Semester: %d\n", arr.score[i].semester);
			textcolor(15);
			printf("Midterm Score: %f\n", arr.score[i].mids);
			printf("Lab Score: %f\n", arr.score[i].labs);
			printf("Final Score: %f\n", arr.score[i].finals);
		}
	if (kt != 1)
	{
		textcolor(12);
		printf("No result!");
	}
	textcolor(12);
	printf("Enter y to quit: ");
	while (1)
	{
		fflush(stdin);
		scanf_s("%c", &x);
		if (x == 'y')
			return;
	}
}
void ViewSchedule(Array &arr, Size &n, int pos)
{
	int pos1, kt = 0;
	char x;
	ClearScreen();
	for (int i = 0; i < n.stucour; i++)
	{
		for (int j = 0; j <= arr.stucour[i].size; j++)
		{
			if (strcmp(arr.stud[pos].username, arr.stucour[i].sid[j]) == 0)
			{
				kt = 1;
				textcolor(15);
				printf("Course Code: %s\n", arr.stucour[i].code);
				for (int k = 0; k < n.course; k++)
					if (strcmp(arr.stucour[i].code, arr.course[k].code) == 0)
					{
						printf("Course Name: %s\n", arr.course[k].name);
						textcolor(15);
						printf("From %d:%d ", arr.course[k].from.h, arr.course[k].from.m);
						printf("to %d:%d ", arr.course[k].to.h, arr.course[k].to.m);
						switch (arr.course[k].dow)
						{
						case Monday:printf("on Monday"); break;
						case Tuesday:printf("on Tuesday"); break;
						case Wednesday:printf("on Wednesday"); break;
						case Thursday:printf("on Thursday"); break;
						case Friday:printf("on Friday"); break;
						case Saturday:printf("on Saturday"); break;
						case Sunday:printf("on Sunday"); break;
						}
						printf("\n");
						textcolor(15);
					}
			}
		}
	}
	if (kt != 1)
	{
		textcolor(12);
		printf("No schedule!");
	}
	textcolor(12);
	printf("Enter y to quit: ");
	while (1)
	{

		fflush(stdin);
		scanf_s("%c", &x);
		if (x == 'y')
			return;
	}
}
////////////////////// 31-34 /////////////////////////////////
////////////////////// 28-30 /////////////////////////////////
void ImportScoreBoard(Score sarr[], int &n) {
	// Yêu cầu nhập tên file rồi gọi hàm ImportScoreBoardList 
	ClearScreen();
	textcolor(15);
	cout << "Name of csv file which have a Scoreboard of course: ";
	char s[255];
	fflush(stdin);
	gets_s(s, 255);
	if (!checkFile(s)) return;
	ImportScoreboardList(s, sarr, n);
	textcolor(10);
	puts("Import Scoreboard of course successfully!");
	puts("Press any key to continue.");
	int x;
	x = _getch();
}
void EditGrade(Score sarr[], int n) {
	// Yêu cầu nhập mssv,course code, rồi tìm trong mảng score phần tử thỏa 2 cái đó. Dùng các lệnh scanf_s để nhập lại điểm của phần tử
	ClearScreen();
	textcolor(15);
	char IDCourse[30], IDStudent[30];
	int check=0;
	cout << "Enter Course ID :";
	fflush(stdin);
	gets_s(IDCourse, 30);
	cout << "Enter Student ID :";
	fflush(stdin);
	gets_s(IDStudent, 30);
	for (int i = 0; i < n; i++)
		if (strcmp(IDCourse, sarr[i].code) == 0 && strcmp(IDStudent, sarr[i].sid) == 0)
		{
			check = 1;
			cout << "Enter Midterm point :";
			cin >> sarr[i].mids;
			cout << "Enter Lab point :";
			cin >> sarr[i].labs;
			cout << "Enter Final test point :";
			cin >> sarr[i].finals;
		}
	if (check == 1) {
		textcolor(10);puts("Update grade successfully!");
	}
	else {
		textcolor(12);puts("No grade to edit");
	}
	puts("Press any key to continue.");
	int y;
	y = _getch();

}
void PrintfTable(int y)
{
	textcolor(5);
	gotoxy(15, y);
	cout << "|";
	gotoxy(22, y);
	cout << "|";
	gotoxy(33, y);
	cout << "|";
	gotoxy(41, y);
	cout << "|";
	gotoxy(46, y);
	cout << "|";
	gotoxy(54, y);
	cout << "|";
}
void PrintfCoreTable(int Serial, char StudentID[25], float Midterm, float Labs, float Finals, int y)
{
	textcolor(15);
	gotoxy(16, y);
	cout << Serial;
	gotoxy(23, y);
	cout << StudentID;
	gotoxy(34, y);
	printf("%0.1f", Midterm);
	gotoxy(42, y);
	printf("%0.1f", Labs);
	gotoxy(47, y);
	printf("%0.1f", Finals);
}
void ViewScore(Score sarr[], int n) {
	// Yêu cầu nhập course code, rồi tìm trong mảng score phần tử thỏa  cái đó. In ra hết các phần tử có trùng course code đã nhập
	int kt = 0;
	textcolor(15);
	ClearScreen();
	cout << "Enter Course ID :";
	char s[255];
	fflush(stdin);
	gets_s(s, 255);
	printf("Year of a Course: ");
	int year;
	scanf_s("%d", &year);

	printf("Semester of a Course: ");
	int semester;
	scanf_s("%d", &semester);
	ClearScreen();
	gotoxy(25, 1);
	textcolor(12);
	cout << "Score Board\n";
	textcolor(15);
	textcolor(5);
	int x = 10;
	int y = 2;
	gotoxy(15, y);
	textcolor(5);
	cout << "________________________________________";
	int j = 0;
	y++;
	gotoxy(15, y);
	textcolor(9);
	cout << " Serial Student ID  Midterm Labs Finals ";
	PrintfTable(y);
	y++;
	for (int i = 0;i<n;i++)
		if (strcmp(s, sarr[i].code) == 0 && (year == sarr[i].year) && (semester == sarr[i].semester))
		{
			kt = 1;
			j++;
			gotoxy(15, y);
			cout << "________________________________________";
			y++;
			PrintfCoreTable(j, sarr[i].sid, sarr[i].mids, sarr[i].labs, sarr[i].finals, y);
			PrintfTable(y);
			//gotoxy(0, 18 + y);
			//printf("%s %0.2f %0.2f %0.2f", sarr[i].sid, sarr[i].mids, sarr[i].labs, sarr[i].finals);
			y++;
		}
	gotoxy(15, y);
	textcolor(10);
	cout << "________________________________________\n";
	if (kt == 1) {
		textcolor(10);puts("View Score Board successfully!");
	}
	else {
		textcolor(12);puts("Course not Found!");
	}
	puts("Press any key to continue.");
	y = _getch();
	char c;
	scanf_s("%c", &c);

}
////////////////////// 28-30 /////////////////////////////////
////////////////////// 19-23 /////////////////////////////////
void ImportSchedule(Course carr[], int n)
{
	char code[15],temp[255];
	int dem,i=-1,intc;
	char anyk[256];
	textcolor(15);
	ClearScreen();
	printf("Enter Course Code:");
	fflush(stdin);
	gets_s(code,15);

	for (int j = 0;j < n;j++)
	{
		if (strcmp(code, carr[j].code) == 0)
		{
			i = j;
			break;
		}
	}
	if (i == -1)
	{
		textcolor(12);
		puts("Course Not Found!");
		puts("Press any key to continue!");
		gets_s(anyk);
		return;
	}
	textcolor(15);
	printf("Enter File Name:");
	char s[255];
	fflush(stdin);
	gets_s(s, 255);

	if (!checkFile(s)) return;
	
	FILE *f = fopen(s, "r");
	fgets(temp, 255, f);
	readString(temp, f);
	dem = 0;
	carr[i].start.d = 0;
	carr[i].start.m = 0;
	carr[i].start.y = 0;
	for (int j = 0; j < strlen(temp); j++)
	{
		//printf("%d-%c-%d ", i,temp[j], temp[j] - '0' );
		if (temp[j] == '/')
			dem++;
		if (temp[j] != '/')
		{
			intc = temp[j] - '0';
			switch (dem)
			{
			case 0:
			{
				carr[i].start.d = carr[i].start.d * 10 + (intc);
				break;
			}
			case 1:
			{
				carr[i].start.m = carr[i].start.m * 10 + (intc);
				break;
			}
			case 2:
			{
				carr[i].start.y = carr[i].start.y * 10 + (intc);
				break;
			}
			}
		}
	}
	readString(temp, f);
	dem = 0;
	carr[i].end.d = 0;
	carr[i].end.m = 0;
	carr[i].end.y = 0;
	for (int j = 0; j < strlen(temp); j++)
	{
		if (temp[j] == '/')
			dem++;
		if (temp[j] != '/')
		{
			intc = temp[j] - '0';
			switch (dem)
			{
			case 0:
			{
				carr[i].end.d = carr[i].end.d * 10 + (intc);
				break;
			}
			case 1:
			{
				carr[i].end.m = carr[i].end.m * 10 + (intc);
				break;
			}
			case 2:
			{
				carr[i].end.y = carr[i].end.y * 10 + (intc);
				break;
			}
			}
		}
	}
	readString(temp, f);
	dem = 0;
	carr[i].from.m = 0;
	carr[i].from.h = 0;
	for (int j = 0; j < strlen(temp); j++)
	{
		if (temp[j] == ':')
			dem++;
		if (temp[j] != ':')
		{
			intc = temp[j] - '0';
			switch (dem)
			{
			case 0:
			{
				carr[i].from.h = carr[i].from.h * 10 + (intc);
				break;
			}
			case 1:
			{
				carr[i].from.m = carr[i].from.m * 10 + (intc);
				break;
			}
			}
		}
	}
	readString(temp, f);
	dem = 0;
	carr[i].to.m = 0;
	carr[i].to.h = 0;
	for (int j = 0; j < strlen(temp); j++)
	{
		if (temp[j] == ':')
			dem++;
		if (temp[j] != ':')
		{
			intc = temp[j] - '0';
			switch (dem)
			{
			case 0:
			{
				carr[i].to.h = carr[i].to.h * 10 + (intc);
				break;
			}
			case 1:
			{
				carr[i].to.m = carr[i].to.m * 10 + (intc);
				break;
			}
			}
		}
	}
	fscanf(f, "%d", &carr[i].dow);
	
	fclose(f);
	textcolor(10);
	puts("Import Successfully!");
	puts("Press any key to continue!");
	gets_s(anyk);
	return;
}
void AddCourseSchedules(Course carr[], int n)
{
	ClearScreen();

	puts("Add A Course's Schedule.");

	char code[15];
	char anyk[256];
	textcolor(15);
	printf("Enter Course Code: ");
	fflush(stdin);
	gets_s(code);

	for (int i = 0; i < n; i++)
		if (strcmp(code, carr[i].code) == 0 && carr[i].from.h==NULL)
		{
			printf("Enter course starting year: ");
			scanf_s("%d", &carr[i].start.y);
			printf("Enter course starting month: ");
			scanf_s("%d", &carr[i].start.m);
			printf("Enter course starting day: ");
			scanf_s("%d", &carr[i].start.d);
			printf("Enter course ending year: ");
			scanf_s("%d", &carr[i].end.y);
			printf("Enter course ending month: ");
			scanf_s("%d", &carr[i].end.m);
			printf("Enter course ending day: ");
			scanf_s("%d", &carr[i].end.d);
			printf("Enter course starting hour: ");
			scanf_s("%d", &carr[i].from.h);
			printf("Enter course starting min: ");
			scanf_s("%d", &carr[i].from.m);
			printf("Enter course ending hour: ");
			scanf_s("%d", &carr[i].to.h);
			printf("Enter course ending min: ");
			scanf_s("%d", &carr[i].to.m);
			printf("Enter course day of week(0->6): ");
			scanf_s("%d", &carr[i].dow);
			textcolor(10);
			puts("Press any key to continue!");
			gets_s(anyk);
			return;
		}
		else if (strcmp(code, carr[i].code) == 0 && carr[i].from.h != NULL)  {
			textcolor(12);
			puts("Course already have schedule!");
			puts("Press any key to continue!");
			gets_s(anyk);
			return;
		}
	textcolor(12);
	puts("Course Not Found!");
	puts("Press any key to continue!");
	gets_s(anyk);
	return;
};

void EditCourseSchedules(Course carr[], int n)
{
	ClearScreen();

	puts("Edit A Course's Schedule.");

	char code[15];
	char anyk[256];
	textcolor(15);
	printf("Enter Course Code: ");
	fflush(stdin);
	gets_s(code);

	for (int i = 0; i < n; i++)
		if (strcmp(code, carr[i].code) == 0)
		{
			printf("Enter course starting year: ");
			scanf_s("%d", &carr[i].start.y);
			printf("Enter course starting month: ");
			scanf_s("%d", &carr[i].start.m);
			printf("Enter course starting day: ");
			scanf_s("%d", &carr[i].start.d);
			printf("Enter course ending year: ");
			scanf_s("%d", &carr[i].end.y);
			printf("Enter course ending month: ");
			scanf_s("%d", &carr[i].end.m);
			printf("Enter course ending day: ");
			scanf_s("%d", &carr[i].end.d);
			printf("Enter course starting hour: ");
			scanf_s("%d", &carr[i].from.h);
			printf("Enter course starting min: ");
			scanf_s("%d", &carr[i].from.m);
			printf("Enter course ending hour: ");
			scanf_s("%d", &carr[i].to.h);
			printf("Enter course ending min: ");
			scanf_s("%d", &carr[i].to.m);
			printf("Enter course day of week(0->6): ");
			scanf_s("%d", &carr[i].dow);
			textcolor(10);
			puts("Press any key to continue!");
			gets_s(anyk);
			return;
		}
	textcolor(12);
	puts("Course Not Found!");
	puts("Press any key to continue!");
	gets_s(anyk);
	return;
};

void RemoveCourseSchedules(Course carr[], int n)
{
	ClearScreen();

	puts("Remove A Course's Schedule.");

	char code[15];
	char anyk[256];
	textcolor(15);
	printf("Enter Course Code: ");
	fflush(stdin);
	gets_s(code);

	for (int i = 0; i < n; i++)
		if (strcmp(code, carr[i].code) == 0)
		{
			carr[i].from.h = NULL;
			carr[i].from.m = NULL;
			carr[i].to.h = NULL;
			carr[i].to.m = NULL;
			carr[i].dow = Nullday;
			textcolor(10);
			puts("Press any key to continue!");
			gets_s(anyk);
			return;
		}
	textcolor(12);
	puts("Course Not Found!");
	puts("Press any key to continue!");
	gets_s(anyk);
	return;
};

void ViewListOfSchedules(Course carr[], int n)
{
	ClearScreen();

	puts("View A Course's Schedule.");

	char code[15];
	char anyk[256];
	textcolor(15);
	printf("Enter Course Code: ");
	fflush(stdin);
	gets_s(code);

	for (int i = 0; i < n; i++)
		if (strcmp(code, carr[i].code) == 0 && carr[i].from.h!=NULL)
		{
			puts(carr[i].name);
			printf("Start on : %d/%d/%d\n", carr[i].start.d, carr[i].start.m, carr[i].start.y);
			printf("End on : %d/%d/%d\n", carr[i].end.d, carr[i].end.m, carr[i].end.y);
			printf("From %d:%d ", carr[i].from.h, carr[i].from.m);
			printf("to %d:%d ", carr[i].to.h, carr[i].to.m);

			switch (carr[i].dow)
			{
			case Monday:printf("on Monday"); break;
			case Tuesday:printf("on Tuesday"); break;
			case Wednesday:printf("on Wednesday"); break;
			case Thursday:printf("on Thursday"); break;
			case Friday:printf("on Friday"); break;
			case Saturday:printf("on Saturday"); break;
			case Sunday:printf("on Sunday"); break;
			}
			puts("");
			textcolor(10);
			puts("Press any key to continue!");
			gets_s(anyk);
			return;
		}
		else if (strcmp(code, carr[i].code) == 0 && carr[i].from.h == NULL) {
			textcolor(12);
			puts("Course already have no schedule!");
			puts("Press any key to continue!");
			gets_s(anyk);
			return;
		}
	textcolor(12);
	printf("\n");
	puts("Course Not Found!");
	printf("\n");
	puts("Press any key to continue!");
	gets_s(anyk);
	return;
};
// 24-27 
void Search_and_view_scoreboard_of_a_course(Score score[], int n)
{
	ClearScreen();
	textcolor(15);
	printf("Course code: ");
	char code[15];
	gets_s(code, 15);

	printf("Year of a Course: ");
	int year;
	scanf_s("%d", &year);

	printf("Semester of a Course: ");
	int semester;
	scanf_s("%d", &semester);

	printf("\n\tStudent ID\tMidterm Score\tLab Score\tFinals Scores\n");

	for (int i = 0; i < n; ++i)
	{
		if ((strcmp(code, score[i].code) == 0) && (year == score[i].year) && (semester == score[i].semester))
		{
			printf("\t%s\t\t%f\t%f\t%f\n", score[i].sid, score[i].mids, score[i].labs, score[i].finals);
		}
	}
	textcolor(10);
	printf("\n---->Press Esc to back");
	while (1)
	{
		if (_kbhit())
		{
			int x = _getch();
			if (x == 27) break;
		}
	}
	char c;
	scanf("%c", &c);
}

void Search_and_view_attendance_list_of_a_course(Presence presence[], int n)
{
	ClearScreen();
	textcolor(15);
	printf("Course code: ");
	char code[15];
	gets_s(code, 15);

	printf("Year of a Course: ");
	int year;
	scanf_s("%d", &year);

	printf("Semester of a Course: ");
	int semester;
	scanf_s("%d", &semester);

	int number_week = 4;
	printf("Number of Week: ");
	scanf_s("%d", &number_week);

	printf("\nStudent ID");
	for (int i = 1; i <= number_week; ++i)
	{
		printf("\t%d", i);
	}

	for (int i = 0; i < n; ++i)
	{
		if ((strcmp(code, presence[i].code) == 0) && (year == presence[i].year) && (semester == presence[i].semester))
		{
			printf("\n%s\t", presence[i].sid);
			for (int j = 1; j <= number_week; ++j)
			{
				if (presence[i].week[j] == 1)
				{
					printf("\t+");
				}
				else printf("\t-");
			}
		}
	}
	textcolor(10);
	printf("\n\n---->Press Esc to back");
	while (1)
	{
		if (_kbhit())
		{
			int x = _getch();
			if (x == 27) break;
		}
	}
	char c;
	scanf("%c", &c);
}

void Export_attendance_list_to_a_csv_file(Array &arr, Size &n)
{
	ClearScreen();
	textcolor(15);
	printf("Export to file: ");
	char filename[50];
	gets_s(filename, 50);

	FILE *fo = fopen(filename, "w");

	printf("Course code: ");
	char code[15];
	gets_s(code, 15);

	printf("Year of a Course: ");
	int year;
	scanf_s("%d", &year);

	printf("Semester of a Course: ");
	int semester;
	scanf_s("%d", &semester);

	int number_week = 4;
	printf("Number of Week: ");
	scanf_s("%d", &number_week);

	fprintf(fo, "Student ID,");
	for (int i = 1; i <= number_week; ++i)
	{
		fprintf(fo, "%d,", i);
	}

	for (int i = 0; i < n.presence; ++i)
	{
		if ((strcmp(code, arr.presence[i].code) == 0) && (year == arr.presence[i].year) && (semester == arr.presence[i].semester))
		{
			fprintf(fo, "\n%s,", arr.presence[i].sid);
			for (int j = 1; j <= number_week; ++j)
			{
				if (arr.presence[i].week[j] == 1)
				{
					fprintf(fo, "v,");
				}
				else fprintf(fo, " ,");
			}
		}
	}

	Sleep(1000);
	textcolor(10);
	printf("\nFINISH!!!");
	printf("\n---->Press Esc to back");
	while (1)
	{
		if (_kbhit())
		{
			int x = _getch();
			if (x == 27) break;
		}
	}
	fclose(fo);
	char c;
	scanf("%c", &c);
}


void Export_a_scoreboard_to_a_csv_file(Array &arr, Size &n)
{
	ClearScreen();
	textcolor(15);
	printf("Export to file: ");
	char filename[50];
	gets_s(filename, 50);
	FILE *fo = fopen(filename, "w");
	printf("Course code: ");
	char code[15];
	gets_s(code, 15);

	printf("Year of a Course: ");
	int year;
	scanf_s("%d", &year);

	printf("Semester of a Course: ");
	int semester;
	scanf_s("%d", &semester);

	fprintf(fo, "Student ID,Midterm Score,Lab Score,Finals Scores\n");

	for (int i = 0; i < n.score; ++i)
	{
		if ((strcmp(code, arr.score[i].code) == 0) && (year == arr.score[i].year) && (semester == arr.score[i].semester))
		{
			fprintf(fo, "%s,%f,%f,%f\n", arr.score[i].sid, arr.score[i].mids, arr.score[i].labs, arr.score[i].finals);
		}
	}

	fclose(fo);
	textcolor(10);
	printf("\nFINISH!!!");
	printf("\n---->Press Esc to back");
	while (1)
	{
		if (_kbhit())
		{
			int x = _getch();
			if (x == 27) break;
		}
	}
	char c;
	scanf("%c", &c);
}
void ViewCredit()
{
	ClearScreen();
	textcolor(10);
	printf("MSSV   |");
	printf("Ho va ten\n");
	textcolor(15);
	printf("1712092");
	printf(" Phan Bao Minh\n");
	printf("1712212");
	printf(" Ly Thien An\n");
	printf("1712238");
	printf(" Luu Chi Tam\n");
	printf("1712206");
	printf(" Nguyen Huu Vinh\n");
	printf("\n---->Press Esc to back");
	while (1)
	{
		if (_kbhit())
		{
			int x = _getch();
			if (x == 27) break;
		}
	}
}