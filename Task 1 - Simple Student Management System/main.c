
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 5
#define NAME_SIZE 50
#define FILE_NAME "students.dat"

typedef struct {
    int id;
    char name[NAME_SIZE];
    int grade;
} Student;

int load_students(Student students[]) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL)
        return 0;

    int count = 0;
    while (count < MAX_STUDENTS &&
           fread(&students[count], sizeof(Student), 1, file) == 1) {
        count++;
    }

    fclose(file);
    return count;
}

int save_students(const Student students[], int count) {
    FILE *file = fopen(FILE_NAME, "wb");
    if (file == NULL)
        return 0;

    int success = fwrite(students, sizeof(Student), count, file) == (size_t)count;
    fclose(file);
    return success;
}

int find_student(const Student students[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id)
            return i;
    }
    return -1;
}

void create_student(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Student limit reached.\n");
        return;
    }

    Student student;

    printf("Enter ID: ");
    if (scanf("%d", &student.id) != 1)
        return;

    if (find_student(students, *count, student.id) != -1) {
        printf("That ID already exists.\n");
        return;
    }

    printf("Enter name: ");
    if (scanf(" %49[^\n]", student.name) != 1)
        return;

    printf("Enter grade (0-100): ");
    if (scanf("%d", &student.grade) != 1 ||
        student.grade < 0 || student.grade > 100) {
        printf("Invalid grade.\n");
        return;
    }

    students[*count] = student;
    (*count)++;

    if (!save_students(students, *count)) {
        (*count)--;
        printf("Could not save records.\n");
        return;
    }

    printf("Student added.\n");
}

void read_students(const Student students[], int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Grade: %d\n",
               students[i].id,
               students[i].name,
               students[i].grade);
    }
}

void update_student(Student students[], int count) {
    int id;

    printf("Enter student ID to update: ");
    if (scanf("%d", &id) != 1)
        return;

    int index = find_student(students, count, id);
    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    printf("Enter new name: ");
    if (scanf(" %49[^\n]", students[index].name) != 1)
        return;

    printf("Enter new grade (0-100): ");
    if (scanf("%d", &students[index].grade) != 1 ||
        students[index].grade < 0 || students[index].grade > 100) {
        printf("Invalid grade.\n");
        return;
    }

    if (!save_students(students, count)) {
        printf("Could not save records.\n");
        return;
    }

    printf("Student updated.\n");
}

void delete_student(Student students[], int *count) {
    int id;

    printf("Enter student ID to delete: ");
    if (scanf("%d", &id) != 1)
        return;

    int index = find_student(students, *count, id);
    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    for (int i = index; i < *count - 1; i++)
        students[i] = students[i + 1];

    (*count)--;

    if (!save_students(students, *count)) {
        printf("Could not save records. Reload the program's data before continuing.\n");
        return;
    }

    printf("Student deleted.\n");
}

int main(void) {
    Student students[MAX_STUDENTS];
    int count = load_students(students);
    int choice;

    do {
        printf("\n--- Student Management System ---\n");
        printf("1. Create student\n");
        printf("2. Read students\n");
        printf("3. Update student\n");
        printf("4. Delete student\n");
        printf("0. Exit\n");
        printf("Choose: ");

        if (scanf("%d", &choice) != 1)
            break;

        switch (choice) {
            case 1:
                create_student(students, &count);
                break;
            case 2:
                read_students(students, count);
                break;
            case 3:
                update_student(students, count);
                break;
            case 4:
                delete_student(students, &count);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
