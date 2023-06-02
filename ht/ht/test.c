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
        printf("�޷����ļ�����д�롣\n");
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
        printf("������ѧ�����ݡ�\n");
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
        printf("�޷����ļ�����д�롣\n");
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
        printf("�����ڿγ����ݡ�\n");
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
    printf("������༶��ѧ����������");
    scanf("%d", numStudents);

    if (*numStudents < 3) {
        printf("������Ҫ3��ѧ����\n");
        *numStudents = 0;
        return;
    }

    for (int i = 0; i < *numStudents; i++) {
        printf("�������%d��ѧ������ϸ��Ϣ��\n", i + 1);
        students[i].studentId = i + 1;

        printf("ѧ��������");
        scanf("%s", students[i].name);

        printf("רҵ��");
        scanf("%s", students[i].major);

        printf("�꼶��");
        scanf("%s", students[i].grade);

        printf("�༶��");
        scanf("%s", students[i].classroom);
    }

    saveStudents(students, *numStudents);
}

void initializeCourses(Course courses[], int* numCourses) {
    printf("������γ̵�������");
    scanf("%d", numCourses);

    if (*numCourses < 3) {
        printf("������Ҫ3�ſγ̡�\n");
        *numCourses = 0;
        return;
    }

    for (int i = 0; i < *numCourses; i++) {
        printf("�������%d�ſγ̵���ϸ��Ϣ��\n", i + 1);
        courses[i].courseId = i + 1;

        printf("�γ����ƣ�");
        scanf("%s", courses[i].courseName);

        printf("ѧ�֣�");
        scanf("%d", &courses[i].credits);
    }

    saveCourses(courses, *numCourses);
}

void enterGrades(Course courses[], int numCourses) {
    int courseId, studentId, grade;
    printf("������γ̱�ţ�");
    scanf("%d", &courseId);

    printf("������ѧ��ѧ�ţ�");
    scanf("%d", &studentId);

    printf("������ɼ���");
    scanf("%d", &grade);

    courses[courseId - 1].grades[studentId - 1] = grade;
    courses[courseId - 1].numStudents++;
}

void displayCourseDetails(Course courses[], int numCourses) {
    int courseId;
    printf("������γ̱�ţ�");
    scanf("%d", &courseId);

    Course course = courses[courseId - 1];
    printf("�γ����ƣ�%s\n", course.courseName);
    printf("ѧ�֣�%d\n", course.credits);

    printf("ѧ��\t�ɼ�\n");
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

    printf("��ѧ������%d\n", totalStudents);
    printf("����������%d\n", totalPassed);
    printf("����ٷֱȣ�%.2f%%\n", (float)totalPassed / totalStudents * 100);
    printf("������������%d\n", totalStudents - totalPassed);
    printf("������ٷֱȣ�%.2f%%\n", (float)(totalStudents - totalPassed) / totalStudents * 100);
}

void displayStudentGrades(Student students[], int numStudents, Course courses[], int numCourses) {
    int studentId;
    printf("������ѧ��ѧ�ţ�");
    scanf("%d", &studentId);

    Student student = students[studentId - 1];
    printf("ѧ��������%s\n", student.name);
    printf("רҵ��%s\n", student.major);
    printf("�꼶��%s\n", student.grade);
    printf("�༶��%s\n", student.classroom);

    printf("�γ�\t�ɼ�\n");
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
        printf("\n�༶�ɼ�����ϵͳ\n");
        printf("1. ��ʼ��ѧ��\n");
        printf("2. ��ʼ���γ�\n");
        printf("3. ¼��ɼ�\n");
        printf("4. ��ʾ�γ�����\n");
        printf("5. ��ʾ�༶ͳ����Ϣ\n");
        printf("6. ��ʾѧ���ɼ�\n");
        printf("7. �˳�\n");

        printf("����������ѡ��");
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
            printf("�����˳�...\n");
            break;
        default:
            printf("��Чѡ�������ԡ�\n");
            break;
        }
    } while (choice != 7);

    saveStudents(students, numStudents);
    saveCourses(courses, numCourses);

    return 0;
}
