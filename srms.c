#include <stdio.h>
#include <string.h>

struct Student {
    int roll;
    char name[30];
    char branch[20];
} s[100];

int count = 0;

// Function declarations
void adminMenu();
void staffMenu();
void guestMenu();
int login(char username[], char password[]);
void loadData();
void saveData();

// Login function
int login(char username[], char password[]) {
    if(strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0)
        return 1; // Admin
    if(strcmp(username, "staff") == 0 && strcmp(password, "staff123") == 0)
        return 2; // Staff
    return 0; // Invalid
}

// Load data from txt file
void loadData() {
    FILE *fp = fopen("students.txt", "r");
    if(fp == NULL) return;

    count = 0;
    while(fscanf(fp, "%d %s %s", &s[count].roll, s[count].name, s[count].branch) != EOF) {
        count++;
    }
    fclose(fp);
}

// Save data to file
void saveData() {
    FILE *fp = fopen("students.txt", "w");
    for(int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %s\n", s[i].roll, s[i].name, s[i].branch);
    }
    fclose(fp);
}

// Add student
void addStudent() {
    printf("\nEnter Roll: ");
    scanf("%d", &s[count].roll);
    printf("Enter Name: ");
    scanf("%s", s[count].name);
    printf("Enter Branch: ");
    scanf("%s", s[count].branch);

    count++;
    saveData();
    printf("Student Added Successfully!\n\n");
}

// Display all students
void displayStudents() {
    if(count == 0) {
        printf("\nNo Records Available!\n");
        return;
    }
    printf("\n----- STUDENT LIST -----\n");
    for(int i = 0; i < count; i++)
        printf("%d\t%s\t%s\n", s[i].roll, s[i].name, s[i].branch);
}

// Search student
void searchStudent() {
    int r, found = 0;
    printf("\nEnter Roll to Search: ");
    scanf("%d", &r);

    for(int i = 0; i < count; i++) {
        if(s[i].roll == r) {
            printf("Found: %d %s %s\n", s[i].roll, s[i].name, s[i].branch);
            found = 1;
        }
    }
    if(!found) printf("Not Found!\n");
}

// Update student
void updateStudent() {
    int r, found = 0;
    printf("\nEnter Roll to Update: ");
    scanf("%d", &r);

    for(int i = 0; i < count; i++) {
        if(s[i].roll == r) {
            printf("New Name: ");
            scanf("%s", s[i].name);
            printf("New Branch: ");
            scanf("%s", s[i].branch);

            saveData();
            printf("Updated Successfully!\n");
            found = 1;
        }
    }
    if(!found) printf("Not Found!\n");
}

// Delete student
void deleteStudent() {
    int r, found = 0;
    printf("\nEnter Roll to Delete: ");
    scanf("%d", &r);

    for(int i = 0; i < count; i++) {
        if(s[i].roll == r) {
            for(int j = i; j < count - 1; j++)
                s[j] = s[j + 1];

            count--;
            saveData();
            printf("Deleted Successfully!\n");
            found = 1;
            break;
        }
    }
    if(!found) printf("Not Found!\n");
}

// -------------------- MENUS --------------------

// Admin menu (full control)
void adminMenu() {
    int ch;
    do {
        printf("\n---- ADMIN MENU ----\n");
        printf("1. Add Student\n2. Display Students\n3. Search Student\n4. Update Student\n5. Delete Student\n6. Logout\n");
        printf("Enter Choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: return;
            default: printf("Invalid Choice!\n");
        }
    } while(1);
}

// Staff menu (same as admin except login)
void staffMenu() {
    int ch;
    do {
        printf("\n---- STAFF MENU ----\n");
        printf("1. Display Students\n2. Search Student\n3. Update Student\n4. Logout\n");
        printf("Enter Choice: ");
        scanf("%d", &ch);

        switch(ch) {
            
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: updateStudent(); break;
            case 4: return;
            default: printf("Invalid Choice!\n");
        }
    } while(1);
}

// Guest menu (view only)
void guestMenu() {
    int ch;
    do {
        printf("\n---- GUEST MENU ----\n");
        printf("1. Display Students\n2. Search Student\n3. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: return;
            default: printf("Invalid Choice!\n");
        }
    } while(1);
}

// -------------------- MAIN FUNCTION --------------------

int main() {
    char user[20], pass[20];
    int role;

    loadData(); // Load records from file

    printf("Username: ");
    scanf("%s", user);

    if(strcmp(user, "guest") == 0) {
        guestMenu();
        return 0;
    }

    printf("Password: ");
    scanf("%s", pass);

    role = login(user, pass);

    if(role == 1) adminMenu();
    else if(role == 2) staffMenu();
    else printf("\nInvalid Login! Access Denied.\n");

    return 0;
}
