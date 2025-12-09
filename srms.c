#include <stdio.h>
#include <string.h>

struct Student {
    int roll;
    char name[30];
    char branch[20];
} s[100];

int count = 0;

void adminMenu();
int login(char username[], char password[]);

int login(char username[], char password[]) {
    if(strcmp(username, "thanya") == 0 && strcmp(password, "thanya123") == 0)
        return 1;
    return 0;
}

void addStudent() {
    printf("\nEnter Roll: ");
    scanf("%d", &s[count].roll);
    printf("Enter Name: ");
    scanf("%s", s[count].name);
    printf("Enter Branch: ");
    scanf("%s", s[count].branch);
    count++;
    printf("Student Added Successfully!\n\n");
}

void displayStudents() {
    if(count == 0) {
        printf("\nNo Records Available!\n");
        return;
    }
    printf("\n----- STUDENT LIST -----\n");
    for(int i = 0; i < count; i++)
        printf("%d\t%s\t%s\n", s[i].roll, s[i].name, s[i].branch);
}

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
            printf("Updated Successfully!\n");
            found = 1;
        }
    }
    if(!found) printf("Not Found!\n");
}

void deleteStudent() {
    int r, found = 0;
    printf("\nEnter Roll to Delete: ");
    scanf("%d", &r);
    for(int i = 0; i < count; i++) {
        if(s[i].roll == r) {
            for(int j = i; j < count - 1; j++)
                s[j] = s[j + 1];
            count--;
            printf("Deleted Successfully!\n");
            found = 1;
            break;
        }
    }
    if(!found) printf("Not Found!\n");
}

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

int main() {
    char user[20], pass[20];
    int role;
    printf("Username: ");
    scanf("%s", user);
    printf("Password: ");
    scanf("%s", pass);
    role = login(user, pass);
    if(role == 1) adminMenu();
    else printf("\nInvalid Login! Access Denied.\n");
    return 0;
}
