#include "user.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void initUsers(struct User users[], int n) {
    for (int i = 0; i < n; i++) {
        strcpy(users[i].name, "");
        strcpy(users[i].password, "");
        users[i].role = 0;
        users[i].state = 0;
    }
}

void listUsers(struct User users[], int maxUsers) {
    printf("%-20s %-10s %-10s\n", "Name", "Role", "State");
    printf("--------------------------------------------\n");
    for (int i = 0; i < maxUsers; i++) {
        // Only print if the name is not empty
        if (strlen(users[i].name) > 0) { 
            printf("%-20s %-10d %-10d\n", 
                    users[i].name, 
                    users[i].role, 
                    users[i].state);
        }
    }
}

void addUser(struct User *u) {
    printf("Enter name: ");
    scanf("%19s", u->name);
    
    char tempPass[20];
    printf("Enter password: ");
    scanf("%19s", tempPass);

    // Use your strong password check here
    if (strongPassword(tempPass)) {
        strcpy(u->password, tempPass);
        u->role = 0;   // Default: user
        u->state = 0;  // Default: active
        printf("User added successfully.\n");
    } else {
        printf("Error: Weak password! User not added.\n");
        // Reset name so it stays "empty"
        u->name[0] = '\0'; 
    }
}

void deleteUser(struct User users[], int n, char name[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(users[i].name, name) == 0) {
            strcpy(users[i].name, "");
            strcpy(users[i].password, "");
            users[i].role = 0;
            users[i].state = 0;
            printf("User deleted successfully.\n");
            return;
        }
    }
    printf("User not found.\n");
}

int searchUser(struct User users[], int n, char name[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(users[i].name, name) == 0) {
            return i; // Return index if found
        }
    }
    return -1; // Not found
}

void changePassword(struct User users[], int n, char name[]) {
    int index = searchUser(users, n, name);
    if (index != -1) {
        printf("Enter new password: ");
        scanf("%19s", users[index].password);
        printf("Password changed successfully.\n");
    } else {
        printf("User not found.\n");
    }
}

int checkLogin(struct User users[], int n, char name[], char pass[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(users[i].name, name) == 0 &&
            strcmp(users[i].password, pass) == 0 &&
            users[i].state == 0) { // Check if active
            return 1; // Login successful
        }
    }
    return 0; // Login failed
}

int strongPassword(char pass[]) {
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSymbol = 0;
    int length = strlen(pass);

    if (length < 8) return 0; // Minimum length

    for (int i = 0; i < length; i++) {
        if (isupper(pass[i])) hasUpper = 1;
        else if (islower(pass[i])) hasLower = 1;
        else if (isdigit(pass[i])) hasDigit = 1;
        else hasSymbol = 1;
    }

    return (hasUpper && hasLower && hasDigit && hasSymbol);
}

void blockUser(struct User users[], int n, char name[]) {
    int index = searchUser(users, n, name);
    if (index != -1) {
        users[index].state = 1; // Blocked
        printf("User blocked successfully.\n");
    } else {
        printf("User not found.\n");
    }
}

void unblockUser(struct User users[], int n, char name[]) {
    int index = searchUser(users, n, name);
    if (index != -1) {
        users[index].state = 0; // Active
        printf("User unblocked successfully.\n");
    } else {
        printf("User not found.\n");
    }
}

void changeRole(struct User users[], int n, char name[], int role) {
    int index = searchUser(users, n, name);
    if (index != -1) {
        users[index].role = role;
        printf("User role changed successfully.\n");
    } else {
        printf("User not found.\n");
    }
}

void listAdmins(struct User users[], int n) {
    printf("Admin Users:\n");
    for (int i = 0; i < n; i++) {
        if (users[i].role == 1 && strcmp(users[i].name, "") != 0) {
            printf("%s\n", users[i].name);
        }
    }
}

int stringLength(char str[]) {
    return strlen(str);
}

int containsUppercase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isupper(str[i])) return 1;
    }
    return 0;
}

int containsLowercase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (islower(str[i])) return 1;
    }
    return 0;
}

int containsDigit(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i])) return 1;
    }
    return 0;
}

int containsSymbol(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalnum(str[i])) return 1;
    }
    return 0;
}

void userStatistics(struct User users[], int n) {
    int totalUsers = 0, activeUsers = 0, blockedUsers = 0, adminUsers = 0;

    for (int i = 0; i < n; i++) {
        if (strcmp(users[i].name, "") != 0) {
            totalUsers++;
            if (users[i].state == 0) activeUsers++;
            else blockedUsers++;
            if (users[i].role == 1) adminUsers++;
        }
    }

    printf("Total Users: %d\n", totalUsers);
    printf("Active Users: %d\n", activeUsers);
    printf("Blocked Users: %d\n", blockedUsers);
    printf("Admin Users: %d\n", adminUsers);
}

void saveUsers(struct User users[], int n) {
    FILE *file = fopen("users.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(users, sizeof(struct User), n, file);
    fclose(file);
}

int loadUsers(struct User users[], int max) {
    FILE *file = fopen("users.dat", "rb");
    if (file == NULL) return 0; // Return 0 if file doesn't exist

    int count = 0;
    // Read one struct at a time until end of file or max reached
    while (count < max && fread(&users[count], sizeof(struct User), 1, file)) {
        count++;
    }
    fclose(file);
    return count; // This is the important part!
}