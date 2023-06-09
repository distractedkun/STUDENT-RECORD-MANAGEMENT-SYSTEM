#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct student {
    char name[50];
    char mobile[20];
    int rollno;
    char course[20];
    char branch[20];
};

void menu();
void add();
void view();
void search();
void modify();
void deleterec();
void sort();
void filter();
void exportRecords();
void importRecords();
void authenticateUser();

void gotoxy(int x, int y);

int main() {
    system("cls");
    authenticateUser();
    return 0;
}

void menu() {
    system("cls");
    int choice;
    gotoxy(10, 3);
    printf("<-----:STUDENT RECORD MANAGEMENT SYSTEM:----->");
    gotoxy(10, 5);
    printf("1. Add Student Record");
    gotoxy(10, 6);
    printf("2. View Student Records");
    gotoxy(10, 7);
    printf("3. Search Student Record");
    gotoxy(10, 8);
    printf("4. Modify Student Record");
    gotoxy(10, 9);
    printf("5. Delete Student Record");
    gotoxy(10, 10);
    printf("6. Sort Student Records");
    gotoxy(10, 11);
    printf("7. Filter Student Records");
    gotoxy(10, 12);
    printf("8. Export Student Records");
    gotoxy(10, 13);
    printf("9. Import Student Records");
    gotoxy(10, 14);
    printf("10. Exit");
    gotoxy(10, 17);
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            add();
            break;
        case 2:
            view();
            break;
        case 3:
            search();
            break;
        case 4:
            modify();
            break;
        case 5:
            deleterec();
            break;
        case 6:
            sort();
            break;
        case 7:
            filter();
            break;
        case 8:
            exportRecords();
            break;
        case 9:
            importRecords();
            break;
        case 10:
            exit(0);
            break;
        default:
            gotoxy(10, 19);
            printf("Invalid choice. Please enter a valid option.");
            getch();
            menu();
    }
}

void add() {
    system("cls");
    struct student std;
    FILE *fp;
    fp = fopen("record.txt", "ab+");
    if (fp == NULL) {
        gotoxy(10, 5);
        printf("Error opening file.");
        exit(1);
    }
    gotoxy(10, 3);
    printf("<--:ADD STUDENT RECORD:-->");
    gotoxy(10, 5);
    printf("Enter name: ");
    fflush(stdin);
    gets(std.name);
    gotoxy(10, 6);
    printf("Enter mobile number: ");
    gets(std.mobile);
    gotoxy(10, 7);
    printf("Enter roll number: ");
    scanf("%d", &std.rollno);
    fflush(stdin);
    gotoxy(10, 8);
    printf("Enter course: ");
    gets(std.course);
    gotoxy(10, 9);
    printf("Enter branch: ");
    gets(std.branch);
    fseek(fp, 0, SEEK_END);
    fwrite(&std, sizeof(std), 1, fp);
    fclose(fp);
    gotoxy(10, 11);
    printf("Record added successfully.");
    gotoxy(10, 14);
    printf("Press any key to continue.");
    getch();
    menu();
}

void view() {
    system("cls");
    struct student std;
    FILE *fp;
    fp = fopen("record.txt", "rb");
    if (fp == NULL) {
        gotoxy(10, 5);
        printf("Error opening file.");
        exit(1);
    }
    gotoxy(10, 3);
    printf("<--:VIEW STUDENT RECORDS:-->");
    gotoxy(10, 5);
    printf("---------------------------------------------------------------------------------");
    gotoxy(10, 6);
    printf("Name\t\t\tMobile\t\t  Roll No\tCourse\t\tBranch");
    gotoxy(10, 7);
    printf("---------------------------------------------------------------------------------");
    int row = 9;
    while (fread(&std, sizeof(std), 1, fp) == 1) {
        gotoxy(10, row);
        printf("%s", std.name);
        gotoxy(30, row);
        printf("%s", std.mobile);
        gotoxy(50, row);
        printf("%d", std.rollno);
        gotoxy(65, row);
        printf("%s", std.course);
        gotoxy(80, row);
        printf("%s", std.branch);
        row++;
    }
    fclose(fp);
    gotoxy(10, row + 2);
    printf("Press any key to continue.");
    getch();
    menu();
}

void search() {
    system("cls");
    struct student std;
    FILE *fp;
    char stname[50];
    fp = fopen("record.txt", "rb");
    if (fp == NULL) {
        gotoxy(10, 5);
        printf("Error opening file.");
        exit(1);
    }
    gotoxy(10, 3);
    printf("<--:SEARCH STUDENT RECORD:-->");
    gotoxy(10, 5);
    printf("Enter the name of the student to search: ");
    fflush(stdin);
    gets(stname);
    int found = 0;
    while (fread(&std, sizeof(std), 1, fp) == 1) {
        if (strcmp(stname, std.name) == 0) {
            found = 1;
            break;
        }
    }
    if (found) {
        gotoxy(10, 7);
        printf("Record found!");
        gotoxy(10, 9);
        printf("Name: %s", std.name);
        gotoxy(10, 10);
        printf("Mobile: %s", std.mobile);
        gotoxy(10, 11);
        printf("Roll No: %d", std.rollno);
        gotoxy(10, 12);
        printf("Course: %s", std.course);
        gotoxy(10, 13);
        printf("Branch: %s", std.branch);
    } else {
        gotoxy(10, 7);
        printf("Record not found.");
    }
    fclose(fp);
    gotoxy(10, 16);
    printf("Press any key to continue.");
    getch();
    menu();
}

void modify() {
    system("cls");
    struct student std;
    FILE *fp;
    char stname[50];
    fp = fopen("record.txt", "rb+");
    if (fp == NULL) {
        gotoxy(10, 5);
        printf("Error opening file.");
        exit(1);
    }
    gotoxy(10, 3);
    printf("<--:MODIFY STUDENT RECORD:-->");
    gotoxy(10, 5);
    printf("Enter the name of the student to modify: ");
    fflush(stdin);
    gets(stname);
    int found = 0;
    while (fread(&std, sizeof(std), 1, fp) == 1) {
        if (strcmp(stname, std.name) == 0) {
            found = 1;
            break;
        }
    }
    if (found) {
        fseek(fp, ftell(fp) - sizeof(std), 0);
        gotoxy(10, 7);
        printf("Enter new name: ");
        fflush(stdin);
        gets(std.name);
        gotoxy(10, 8);
        printf("Enter new mobile number: ");
        gets(std.mobile);
        gotoxy(10, 9);
        printf("Enter new roll number: ");
        scanf("%d", &std.rollno);
        fflush(stdin);
        gotoxy(10, 10);
        printf("Enter new course: ");
        gets(std.course);
        gotoxy(10, 11);
        printf("Enter new branch: ");
        gets(std.branch);
        fwrite(&std, sizeof(std), 1, fp);
        gotoxy(10, 13);
        printf("Record modified successfully.");
    } else {
        gotoxy(10, 7);
        printf("Record not found.");
    }
    fclose(fp);
    gotoxy(10, 16);
    printf("Press any key to continue.");
    getch();
    menu();
}

void deleterec() {
    system("cls");
    struct student std;
    FILE *fp, *temp;
    char stname[50];
    fp = fopen("record.txt", "rb");
    if (fp == NULL) {
        gotoxy(10, 5);
        printf("Error opening file.");
        exit(1);
    }
    temp = fopen("temp.txt", "wb");
    if (temp == NULL) {
        gotoxy(10, 5);
        printf("Error opening file.");
        exit(1);
    }
    gotoxy(10, 3);
    printf("<--:DELETE STUDENT RECORD:-->");
    gotoxy(10, 5);
    printf("Enter the name of the student to delete: ");
    fflush(stdin);
    gets(stname);
    int found = 0;
    while (fread(&std, sizeof(std), 1, fp) == 1) {
        if (strcmp(stname, std.name) != 0)
            fwrite(&std, sizeof(std), 1, temp);
        else
            found = 1;
    }
    fclose(fp);
    fclose(temp);
    remove("record.txt");
    rename("temp.txt", "record.txt");
    if (found) {
        gotoxy(10, 7);
        printf("Record deleted successfully.");
    } else {
        gotoxy(10, 7);
        printf("Record not found.");
    }
    gotoxy(10, 10);
    printf("Press any key to continue.");
    getch();
    menu();
}

void sort() {
    system("cls");
    struct student std[100], temp;
    FILE *fp;
    int i, j, count = 0;
    fp = fopen("record.txt", "rb");
    if (fp == NULL) {
        gotoxy(10, 5);
        printf("Error opening file.");
        exit(1);
    }
    while (fread(&std[count], sizeof(std[count]), 1, fp) == 1)
        count++;
    fclose(fp);
    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count; j++) {
            if (strcmp(std[i].name, std[j].name) > 0) {
                temp = std[i];
                std[i] = std[j];
                std[j] = temp;
            }
        }
    }
    system("cls");
    gotoxy(10, 3);
    printf("<--:SORT STUDENT RECORDS:-->");
    gotoxy(10, 5);
    printf("---------------------------------------------------------------------------------");
    gotoxy(10, 6);
    printf("Name\t\t\tMobile\t\t  Roll No\tCourse\t\tBranch");
    gotoxy(10, 7);
    printf("---------------------------------------------------------------------------------");
    int row = 9;
    for (i = 0; i < count; i++) {
        gotoxy(10, row);
        printf("%s", std[i].name);
        gotoxy(30, row);
        printf("%s", std[i].mobile);
        gotoxy(50, row);
        printf("%d", std[i].rollno);
        gotoxy(65, row);
        printf("%s", std[i].course);
        gotoxy(80, row);
        printf("%s", std[i].branch);
        row++;
    }
    gotoxy(10, row + 2);
    printf("Press any key to continue.");
    getch();
    menu();
}

void filter() {
    system("cls");
    struct student std;
    FILE *fp;
    char stcourse[20];
    fp = fopen("record.txt", "rb");
    if (fp == NULL) {
        gotoxy(10, 5);
        printf("Error opening file.");
        exit(1);
    }
    gotoxy(10, 3);
    printf("<--:FILTER STUDENT RECORDS:-->");
    gotoxy(10, 5);
    printf("Enter the course to filter records: ");
    fflush(stdin);
    gets(stcourse);
    gotoxy(10, 7);
    printf("---------------------------------------------------------------------------------");
    gotoxy(10, 8);
    printf("Name\t\t\tMobile\t\t  Roll No\tCourse\t\tBranch");
    gotoxy(10, 9);
    printf("---------------------------------------------------------------------------------");
    int row = 11;
    while (fread(&std, sizeof(std), 1, fp) == 1) {
        if (strcmp(stcourse, std.course) == 0) {
            gotoxy(10, row);
            printf("%s", std.name);
            gotoxy(30, row);
            printf("%s", std.mobile);
            gotoxy(50, row);
            printf("%d", std.rollno);
            gotoxy(65, row);
            printf("%s", std.course);
            gotoxy(80, row);
            printf("%s", std.branch);
            row++;
        }
    }
    fclose(fp);
    gotoxy(10, row + 2);
    printf("Press any key to continue.");
    getch();
    menu();
}

void exportRecords() {
    system("cls");
    struct student std;
    FILE *fp, *exportFile;
    fp = fopen("record.txt", "rb");
    if (fp == NULL) {
        gotoxy(10, 5);
        printf("Error opening file.");
        exit(1);
    }
    exportFile = fopen("export.txt", "w");
    if (exportFile == NULL) {
        gotoxy(10, 5);
        printf("Error creating file.");
        exit(1);
    }
    while (fread(&std, sizeof(std), 1, fp) == 1) {
        fprintf(exportFile, "%s,%s,%d,%s,%s\n", std.name, std.mobile, std.rollno, std.course, std.branch);
    }
    fclose(fp);
    fclose(exportFile);
    gotoxy(10, 3);
    printf("<--:EXPORT STUDENT RECORDS:-->");
    gotoxy(10, 5);
    printf("Student records exported successfully.");
    gotoxy(10, 7);
    printf("Export file: export.txt");
    gotoxy(10, 9);
    printf("Press any key to continue.");
    getch();
    menu();
}

void importRecords() {
    system("cls");
    struct student std;
    FILE *fp, *importFile;
    fp = fopen("record.txt", "ab");
    if (fp == NULL) {
        gotoxy(10, 5);
        printf("Error opening file.");
        exit(1);
    }
    importFile = fopen("import.txt", "r");
    if (importFile == NULL) {
        gotoxy(10, 5);
        printf("Error opening file.");
        exit(1);
    }
    while (fscanf(importFile, "%[^,],%[^,],%d,%[^,],%[^\n]\n", std.name, std.mobile, &std.rollno, std.course, std.branch) == 5) {
        fwrite(&std, sizeof(std), 1, fp);
    }
    fclose(fp);
    fclose(importFile);
    gotoxy(10, 3);
    printf("<--:IMPORT STUDENT RECORDS:-->");
    gotoxy(10, 5);
    printf("Student records imported successfully.");
    gotoxy(10, 7);
    printf("Import file: import.txt");
    gotoxy(10, 9);
    printf("Press any key to continue.");
    getch();
    menu();
}

void authenticateUser() {
    system("cls");
    char username[20] = "admin";
    char password[20] = "admin123";
    char enteredUsername[20], enteredPassword[20];
    gotoxy(10, 3);
    printf("<--:USER AUTHENTICATION:-->");
    gotoxy(10, 5);
    printf("Username: ");
    fflush(stdin);
    gets(enteredUsername);
    gotoxy(10, 6);
    printf("Password: ");
    fflush(stdin);
    gets(enteredPassword);
    if (strcmp(username, enteredUsername) == 0 && strcmp(password, enteredPassword) == 0) {
        menu();
    } else {
        gotoxy(10, 8);
        printf("Invalid username or password.");
        gotoxy(10, 10);
        printf("Press any key to exit.");
        getch();
        exit(0);
    }
}
