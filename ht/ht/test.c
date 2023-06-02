#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STUDENTS 50
#define MAX_COURSES 10

typedef struct {
    int studentId;
    char name[50];
    char major[50];
    char grade[15];
    char classroom[20];
} Student;

typedef struct {
    int courseId;
    char courseName[50];
    int credits;
    int grades[MAX_STUDENTS];
    int numStudents;
} Course;

void saveStudents(Student students[], int numStudents) {
    FILE* file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("无法打开文件进行写入。\n");
        return;
    }

    fprintf(file, "%d\n", numStudents);
    for (int i = 0; i < numStudents; i++) {
        fprintf(file, "%d %s %s %s %s\n", students[i].studentId, students[i].name, students[i].major, students[i].grade, students[i].classroom);
    }

    fclose(file);
}

void loadStudents(Student students[], int* numStudents) {
    FILE* file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("不存在学生数据。\n");
        *numStudents = 0;
        return;
    }

    fscanf(file, "%d", numStudents);
    for (int i = 0; i < *numStudents; i++) {
        fscanf(file, "%d %s %s %s %s", &students[i].studentId, students[i].name, students[i].major, students[i].grade, students[i].classroom);
    }

    fclose(file);
}

void saveCourses(Course courses[], int numCourses) {
    FILE* file = fopen("courses.txt", "w");
    if (file == NULL) {
        printf("无法打开文件进行写入。\n");
        return;
    }

    fprintf(file, "%d\n", numCourses);
    for (int i = 0; i < numCourses; i++) {
        fprintf(file, "%d %s %d\n", courses[i].courseId, courses[i].courseName, courses[i].credits);
    }

    fclose(file);
}

void loadCourses(Course courses[], int* numCourses) {
    FILE* file = fopen("courses.txt", "r");
    if (file == NULL) {
        printf("不存在课程数据。\n");
        *numCourses = 0;
        return;
    }

    fscanf(file, "%d", numCourses);
    for (int i = 0; i < *numCourses; i++) {
        fscanf(file, "%d %s %d", &courses[i].courseId, courses[i].courseName, &courses[i].credits);
    }

    fclose(file);
}

void initializeStudents(Student students[], int* numStudents) {
    printf("请输入班级中学生的数量：");
    scanf("%d", numStudents);

    if (*numStudents < 3) {
        printf("至少需要3名学生。\n");
        *numStudents = 0;
        return;
    }

    for (int i = 0; i < *numStudents; i++) {
        printf("请输入第%d名学生的详细信息：\n", i + 1);
        students[i].studentId = i + 1;

        printf("学生姓名：");
        scanf("%s", students[i].name);

        printf("专业：");
        scanf("%s", students[i].major);

        printf("年级：");
        scanf("%s", students[i].grade);

        printf("班级：");
        scanf("%s", students[i].classroom);
    }

    saveStudents(students, *numStudents);
}

void initializeCourses(Course courses[], int* numCourses) {
    printf("请输入课程的数量：");
    scanf("%d", numCourses);

    if (*numCourses < 3) {
        printf("至少需要3门课程。\n");
        *numCourses = 0;
        return;
    }

    for (int i = 0; i < *numCourses; i++) {
        printf("请输入第%d门课程的详细信息：\n", i + 1);
        courses[i].courseId = i + 1;

        printf("课程名称：");
        scanf("%s", courses[i].courseName);

        printf("学分：");
        scanf("%d", &courses[i].credits);
    }

    saveCourses(courses, *numCourses);
}

void enterGrades(Course courses[], int numCourses) {
    int courseId, studentId, grade;
    printf("请输入课程编号：");
    scanf("%d", &courseId);

    printf("请输入学生学号：");
    scanf("%d", &studentId);

    printf("请输入成绩：");
    scanf("%d", &grade);

    courses[courseId - 1].grades[studentId - 1] = grade;
    courses[courseId - 1].numStudents++;
}

void displayCourseDetails(Course courses[], int numCourses) {
    int courseId;
    printf("请输入课程编号：");
    scanf("%d", &courseId);

    Course course = courses[courseId - 1];
    printf("课程名称：%s\n", course.courseName);
    printf("学分：%d\n", course.credits);

    printf("学生\t成绩\n");
    for (int i = 0; i < course.numStudents; i++) {
        printf("%d\t%d\n", i + 1, course.grades[i]);
    }
}

void displayClassStatistics(Course courses[], int numCourses) {
    int totalStudents = 0;
    int totalPassed = 0;

    for (int i = 0; i < numCourses; i++) {
        Course course = courses[i];

        for (int j = 0; j < course.numStudents; j++) {
            totalStudents++;
            if (course.grades[j] >= 60) {
                totalPassed++;
            }
        }
    }

    printf("总学生数：%d\n", totalStudents);
    printf("及格人数：%d\n", totalPassed);
    printf("及格百分比：%.2f%%\n", (float)totalPassed / totalStudents * 100);
    printf("不及格人数：%d\n", totalStudents - totalPassed);
    printf("不及格百分比：%.2f%%\n", (float)(totalStudents - totalPassed) / totalStudents * 100);
}

void displayStudentGrades(Student students[], int numStudents, Course courses[], int numCourses) {
    int studentId;
    printf("请输入学生学号：");
    scanf("%d", &studentId);

    Student student = students[studentId - 1];
    printf("学生姓名：%s\n", student.name);
    printf("专业：%s\n", student.major);
    printf("年级：%s\n", student.grade);
    printf("班级：%s\n", student.classroom);

    printf("课程\t成绩\n");
    for (int i = 0; i < numCourses; i++) {
        printf("%d\t%d\n", i + 1, courses[i].grades[studentId - 1]);
    }
}

int main() {
    int numStudents, numCourses;
    Student students[MAX_STUDENTS];
    Course courses[MAX_COURSES];

    loadStudents(students, &numStudents);
    loadCourses(courses, &numCourses);

    int choice;
    do {
        printf("\n班级成绩管理系统\n");
        printf("1. 初始化学生\n");
        printf("2. 初始化课程\n");
        printf("3. 录入成绩\n");
        printf("4. 显示课程详情\n");
        printf("5. 显示班级统计信息\n");
        printf("6. 显示学生成绩\n");
        printf("7. 退出\n");

        printf("请输入您的选择：");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            initializeStudents(students, &numStudents);
            break;
        case 2:
            initializeCourses(courses, &numCourses);
            break;
        case 3:
            enterGrades(courses, numCourses);
            break;
        case 4:
            displayCourseDetails(courses, numCourses);
            break;
        case 5:
            displayClassStatistics(courses, numCourses);
            break;
        case 6:
            displayStudentGrades(students, numStudents, courses, numCourses);
            break;
        case 7:
            printf("正在退出...\n");
            break;
        default:
            printf("无效选择，请重试。\n");
            break;
        }
    } while (choice != 7);

    saveStudents(students, numStudents);
    saveCourses(courses, numCourses);

    return 0;
}
