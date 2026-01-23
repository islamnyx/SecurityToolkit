#include "user.h"
#include "logs.h"  
#include "audit.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
  #include <windows.h>
  #define usleep(x) Sleep((x)/1000) // Converts microseconds to milliseconds for Windows
#else
  #include <unistd.h> // For Linux/macOS
#endif

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

void addUser(struct User *u, struct Log logs[]) {
    printf("--- ADD NEW USER ---\n");
    printf("Enter name: ");
    scanf("%19s", u->name);
    
    char tempPass[20];
    printf("Enter password: ");
    // FIX 1: Read the password into tempPass first, not u->password
    getHiddenPassword(tempPass, 20); 

    // FIX 2: Check the score of tempPass (The 8 threshold we discussed)
    if (passwordScore(tempPass) >= 8) { 
        strcpy(u->password, tempPass); // Only copy if it's strong enough
        u->role = 0;   
        u->state = 0;  
        u->failedAttempts = 0; 
        
        addLog(logs, 100, u->name, "ACCOUNT_CREATED", 0);
        printf("\nUser added successfully.\n"); // Added \n because getHiddenPassword might skip it
    } else {
        printf("\nError: Password too weak (Score: %d)! User not added.\n", passwordScore(tempPass));
        u->name[0] = '\0'; 
    }
}

void deleteUser(struct User users[], int n, char name[], struct Log logs[]) {
    int idx = searchUser(users, n, name);
    if (idx != -1) {
        addLog(logs, 100, name, "ACCOUNT_DELETED", 1); // Record before deleting
        users[idx].name[0] = '\0'; // Simple delete by clearing name
        printf("User %s has been deleted.\n", name);
    } else {
        printf("User not found.\n");
    }
}


int searchUser(struct User users[], int n, char name[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(users[i].name, name) == 0) {
            return i; // Return index if found
        }
    }
    return -1; // Not found
}

void changePassword(struct User users[], int n, char name[], struct Log logs[]) {
    int idx = -1;
    // Find the user in the database
    for (int i = 0; i < n; i++) {
        if (strcmp(users[i].name, name) == 0) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("\033[1;31m[!] Error: User '%s' not found in system.\033[0m\n", name);
        return;
    }

    char oldPass[20], newPass[20];
    
    // --- STEP 1: VERIFY CURRENT IDENTITY ---
    printf("\033[1;33m[?] Verification required for %s.\033[0m\n", name);
    printf("Enter current password: ");
    getHiddenPassword(oldPass, 20); // HIDDEN INPUT

    if (strcmp(users[idx].password, oldPass) == 0) {
        // --- STEP 2: ENTER NEW SECURE PASSWORD ---
        printf("\n\033[1;36m[+] Identity Verified.\033[0m\n");
        printf("Enter new password: ");
        getHiddenPassword(newPass, 20); // HIDDEN INPUT

        // Security check for the new password
        if (passwordScore(newPass) >= 6) { 
            strcpy(users[idx].password, newPass);
            printf("\n\033[1;32m[SUCCESS] Password updated in encrypted database.\033[0m\n");
            
            // SUCCESS LOG (Code 0 for Info)
            addLog(logs, 100, name, "PASS_CHANGE_SUCCESS", 0);
        } else {
            printf("\n\033[1;31m[REJECTED] Password strength insufficient (Score < 6).\033[0m\n");
            
            // FAILURE LOG (Code 1 for Warning)
            addLog(logs, 100, name, "PASS_CHANGE_WEAK", 1);
        }
    } else {
        printf("\n\033[41m\033[1;37m [!] SECURITY ALERT: INCORRECT PASSWORD ENTERED \033[0m\n");
        
        // SECURITY ALERT LOG (Code 2 for Error/Risk)
        addLog(logs, 100, name, "PASS_CHANGE_UNAUTH", 2);
    }
    
    // Pause for a moment so the user can see the result before menu clears
    usleep(1500000); 
}

int checkLogin(struct User users[], int n, char name[], char pass[], struct Log logs[]) {
    int idx = searchUser(users, n, name);

    if (idx != -1) {
        // 1. Check if account is blocked (state == 1)
        if (users[idx].state == 1) {
            printf("\n\033[1;31m[!] ACCESS DENIED: This account is currently LOCKED.\033[0m\n");
            addLog(logs, 100, name, "LOCKED_LOGIN_ATTEMPT", 2);
            return 0;
        }

        // 2. Verify Password
        if (strcmp(users[idx].password, pass) == 0) {
            users[idx].failedAttempts = 0; // Reset counter on success
            addLog(logs, 100, name, "LOGIN_SUCCESS", 0);
            return 1;
        } else {
            // 3. Increment failures
            users[idx].failedAttempts++;
            printf("\n\033[1;33m[!] Warning: Incorrect password. Attempt %d/3.\033[0m\n", users[idx].failedAttempts);
            
            // 4. Trigger Auto-Lock
            if (users[idx].failedAttempts >= 3) {
                users[idx].state = 1; // Block the user
                printf("\n\033[41m\033[1;37m [!!!] SECURITY ALERT: ACCOUNT AUTO-LOCKED [!!!] \033[0m\n");
                addLog(logs, 100, name, "ACCOUNT_LOCKED_BRUTEFORCE", 2);
            } else {
                addLog(logs, 100, name, "LOGIN_FAILED", 1);
            }
        }
    } else {
        printf("\n\033[1;31m[!] User not found in database.\033[0m\n");
    }
    return 0;
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

void blockUser(struct User users[], int n, char name[], struct Log logs[]) {
    int idx = searchUser(users, n, name);
    if (idx != -1) {
        users[idx].state = 1; // Blocked
        addLog(logs, 100, name, "user blocked", 1); // 1 = Warning
    }
}

void unblockUser(struct User users[], int n, char name[], struct Log logs[]) {
    int idx = searchUser(users, n, name);
    if (idx != -1) {
        users[idx].state = 0; 
        addLog(logs, 100, name, "USER_UNBLOCKED", 0); // Now this will work
        printf("User %s unblocked.\n", name);
    }
}

void changeRole(struct User users[], int n, char name[], int newRole, struct Log logs[]) {
    int idx = searchUser(users, n, name);
    
    if (idx != -1) {
        users[idx].role = newRole;
        
        // Create a description string to show the change
        char description[30];
        sprintf(description, "ROLE_TO_%s", (newRole == 1) ? "ADMIN" : "USER");
        
        // RECORD THE LOG
        addLog(logs, 100, name, description, 0);
        
        printf("Success: %s is now an %s.\n", name, (newRole == 1) ? "Admin" : "User");
    } else {
        printf("Error: User not found.\n");
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