#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Constants
#define MAX_STUDENTS 100
#define NAME_LENGTH 50
#define COURSE_LENGTH 30

// Structure to represent a student
typedef struct {
    int id;
    char name[NAME_LENGTH];
    char course[COURSE_LENGTH];
    int age;
    float grades[5];  // Up to 5 grades per student
    int grade_count;   // Number of grades entered
} Student;

// Global array to store students
Student students[MAX_STUDENTS];
int student_count = 0;

// Function prototypes
void displayMenu();
void addStudent();
void viewAllStudents();
void searchStudentById();
void calculateAverageGrade();
void clearInputBuffer();
int isValidName(const char *name);
int isValidCourse(const char *course);
float calculateStudentAverage(int index);

int main() {
    int choice;

    printf("=== STUDENT MANAGEMENT SYSTEM ===\n");

    do {
        displayMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewAllStudents();
                break;
            case 3:
                searchStudentById();
                break;
            case 4:
                calculateAverageGrade();
                break;
            case 5:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        printf("\n");
    } while (choice != 5);

    return 0;
}

void displayMenu() {
    printf("\n--- Main Menu ---\n");
    printf("1. Add a new student\n");
    printf("2. View all students\n");
    printf("3. Search student by ID\n");
    printf("4. Calculate average grade for a student\n");
    printf("5. Exit\n");
}

void addStudent() {
    if (student_count >= MAX_STUDENTS) {
        printf("Cannot add more students. Maximum limit reached.\n");
        return;
    }

    Student newStudent;
    newStudent.id = student_count + 1;

    // Input name
    printf("Enter student name: ");
    clearInputBuffer();
    fgets(newStudent.name, NAME_LENGTH, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0'; // Remove newline

    if (!isValidName(newStudent.name)) {
        printf("Invalid name format. Name should contain only letters and spaces.\n");
        return;
    }

    // Input course
    printf("Enter course: ");
    fgets(newStudent.course, COURSE_LENGTH, stdin);
    newStudent.course[strcspn(newStudent.course, "\n")] = '\0';

    if (!isValidCourse(newStudent.course)) {
        printf("Invalid course name. Course should contain letters, spaces, and hyphens.\n");
        return;
    }

    // Input age
    printf("Enter age: ");
    if (scanf("%d", &newStudent.age) != 1 || newStudent.age < 10 || newStudent.age > 100) {
        printf("Invalid age. Age must be between 10 and 100.\n");
        clearInputBuffer();
        return;
    }

    // Input grades
    printf("How many grades to enter (max 5): ");
    if (scanf("%d", &newStudent.grade_count) != 1 ||
        newStudent.grade_count < 0 || newStudent.grade_count > 5) {
        printf("Invalid number of grades. Must be between 0 and 5.\n");
        clearInputBuffer();
        return;
    }

    for (int i = 0; i < newStudent.grade_count; i++) {
        printf("Enter grade %d (0-100): ", i + 1);
        if (scanf("%f", &newStudent.grades[i]) != 1 ||
            newStudent.grades[i] < 0.0f || newStudent.grades[i] > 100.0f) {
            printf("Invalid grade. Grade must be between 0 and 100.\n");
            clearInputBuffer();
            return;
        }
    }

    students[student_count] = newStudent;
    student_count++;
    printf("Student added successfully with ID: %d\n", newStudent.id);
}

void viewAllStudents() {
    if (student_count == 0) {
        printf("No students in the system.\n");
        return;
    }

    printf("\n=== ALL STUDENTS ===\n");
    for (int i = 0; i < student_count; i++) {
        printf("ID: %d | Name: %s | Course: %s | Age: %d",
               students[i].id, students[i].name,
               students[i].course, students[i].age);

        if (students[i].grade_count > 0) {
            printf(" | Grades: ");
            for (int j = 0; j < students[i].grade_count; j++) {
                printf("%.1f", students[i].grades[j]);
                if (j < students[i].grade_count - 1) printf(", ");
            }
            float avg = calculateStudentAverage(i);
            printf(" | Avg: %.2f", avg);
        } else {
            printf(" | No grades recorded");
        }
        printf("\n");
    }
}

void searchStudentById() {
    int searchId;
    printf("Enter student ID to search: ");

    if (scanf("%d", &searchId) != 1) {
        printf("Invalid ID. Please enter a number.\n");
        clearInputBuffer();
        return;
    }

    int found = 0;
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == searchId) {
            found = 1;
            printf("\nStudent found:\n");
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Course: %s\n", students[i].course);
            printf("Age: %d\n", students[i].age);

            if (students[i].grade_count > 0) {
                printf("Grades: ");
                for (int j = 0; j < students[i].grade_count; j++) {
                    printf("%.1f", students[i].grades[j]);
                    if (j < students[i].grade_count - 1) printf(", ");
                }
                printf("\nAverage Grade: %.2f\n", calculateStudentAverage(i));
            } else {
                printf("No grades recorded.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Student with ID %d not found.\n", searchId);
    }
}

void calculateAverageGrade() {
    int studentId;
    printf("Enter student ID to calculate average grade: ");

    if (scanf("%d", &studentId) != 1) {
        printf("Invalid ID. Please enter a number.\n");
        clearInputBuffer();
        return;
    }

    int index = -1;
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == studentId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Student with ID %d not found.\n", studentId);
        return;
    }

    if (students[index].grade_count == 0) {
        printf("No grades recorded for this student.\n");
        return;
    }

    float average = calculateStudentAverage(index);
    printf("Average grade for student %s (ID: %d) is: %.2f\n",
           students[index].name, studentId, average);
}

float calculateStudentAverage(int index) {
    if (students[index].grade_count == 0) {
        return 0.0f;
    }

    float sum = 0.0f;
    for (int i = 0; i < students[index].grade_count; i++) {
        sum += students[index].grades[i];
    }
    return sum / students[index].grade_count;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int isValidName(const char *name) {
    if (strlen(name) == 0) return 0;

    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != ' ' && name[i] != '-') {
            return 0;
        }
    }
    return 1;
}

int isValidCourse(const char *course) {
    if (strlen(course) == 0) return 0;

    for (int i = 0; course[i] != '\0'; i++) {
        if (!isalnum(course[i]) && course[i] != ' ' && course[i] != '-' && course[i] != '&') {
            return 0;
        }
    }
    return 1;
}
void sortStudentsByAverage() {
    if (student_count == 0) {
        printf("No students to sort.\n");
        return;
    }

    
    int indices[MAX_STUDENTS];
    for (int i = 0; i < student_count; i++) {
        indices[i] = i;
    }

    
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = 0; j < student_count - i - 1; j++) {
            float avg1 = calculateStudentAverage(indices[j]);
            float avg2 = calculateStudentAverage(indices[j + 1]);

            if (avg1 < avg2) {
                // Меняем индексы местами
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }

    printf("\n=== STUDENTS SORTED BY AVERAGE GRADE (DESCENDING) ===\n");
    for (int i = 0; i < student_count; i++) {
        int idx = indices[i];
        float avg = calculateStudentAverage(idx);
        printf("%d. %s (ID: %d) - Avg: %.2f\n",
               i + 1, students[idx].name, students[idx].id, avg);
    }
}

void displayStatistics() {
    if (student_count == 0) {
        printf("No students in the system.\n");
        return;
    }

    int totalAge = 0;
    float totalAverage = 0.0f;
    int studentsWithGrades = 0;

    for (int i = 0; i < student_count; i++) {
        totalAge += students[i].age;

        if (students[i].grade_count > 0) {
            studentsWithGrades++;
            totalAverage += calculateStudentAverage(i);
        }
    }

    float avgAge = (float)totalAge / student_count;
    float overallAvg = (studentsWithGrades > 0) ?
                     totalAverage / studentsWithGrades : 0.0f;

    printf("\n=== SYSTEM STATISTICS ===\n");
    printf("Total students: %d\n", student_count);
    printf("Average age: %.1f\n", avgAge);
    printf("Students with grades: %d\n", studentsWithGrades);
    printf("Overall average grade: %.2f\n", overallAvg);
}
