#include "lib.h"

void main()
{
	Array arr;
	Size n;
	n.stud = 0;
	n.course = 0;
	n.score = 0;
	n.presence = 0;
	n.stucour = 0;
	ImportStudentList("input.csv", arr.stud,n.stud);
	ImportCourseList("inputc.csv", arr.course, n.course);
	ImportScoreboardList("inputs.csv", arr.score, n.score);
	ImportPresenceList("inputp.csv", arr.presence, n.presence);
	ImportStuCourList("inputsc.csv", arr.stucour, n.stucour);

	createMainMenu(arr, n);

	ExportScoreList("inputs.csv", arr.score, "Course Code,Year,Semester,Student ID,Midterm Score,Lab Score,Finals Scores", n.score);
	ExportStudentList("input.csv", arr.stud, "Username,Full name,Email,Mobile phone,Type,Password,Class", n.stud);
	ExportCourseList("inputc.csv", arr.course, "Course Code,Year,Semester,Course Name,Lecturer Name,Start at,End at,From,To,DoW", n.course);
	ExportPresenceList("inputp.csv", arr.presence, "Course Code,Student ID,Year,Semester,Week", n.presence,arr.course,n.course);
	ExportStuCourList("inputsc.csv", arr.stucour, "Course Code,Student ID", n.stucour);

	ExportScoreList("outputs.csv", arr.score, "Course Code,Year,Semester,Student ID,Midterm Score,Lab Score,Finals Scores", n.score);
	ExportStudentList("output.csv", arr.stud, "Username,Full name,Email,Mobile phone,Type,Password,Class", n.stud);
	ExportCourseList("outputc.csv", arr.course, "Course Code,Year,Semester,Course Name,Lecturer Name,Start at,End at,From,To,DoW", n.course);
	ExportPresenceList("outputp.csv", arr.presence, "Course Code,Student ID,Year,Semester,Week", n.presence, arr.course, n.course);
	ExportStuCourList("outputsc.csv", arr.stucour, "Course Code,Student ID", n.stucour);
	system("pause");
}