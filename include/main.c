#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "encryption.h"
#include "math_tools.h"
#include "user.h"
#include "audit.h"
#include "logs.h"
#include <string.h>

void encryptionMenu() {
    struct Message myMsg;
    myMsg.text[0] = '\0'; // Initialize to empty
    int subChoice, shift;
    char keyStr[50], subKey[27];

    do {
        printf("\n========================================");
        printf("\n      CRYPTOGRAPHY & TEXT ANALYSIS      ");
        printf("\n========================================");
        printf("\nCurrent Message: [%s]", myMsg.text[0] == '\0' ? "EMPTY" : myMsg.text);
        printf("\n1.  Enter/Change Message");
        printf("\n2.  Display Message Stats & IC");
        printf("\n3.  Convert to Uppercase");
        printf("\n4.  Convert to Lowercase");
        printf("\n5.  Reverse Message");
        printf("\n6.  Caesar Cipher (Encrypt/Decrypt)");
        printf("\n7.  XOR Cipher (Encrypt/Decrypt)");
        printf("\n8.  Substitution Cipher (Encrypt)");
        printf("\n9.  Frequency Analysis");
        printf("\n0.  Back to Main Menu");
        printf("\nChoice: ");
        
        if (scanf("%d", &subChoice) != 1) {
            while(getchar() != '\n');
            continue;
        }
        getchar(); // Clear newline

        switch(subChoice) {
            case 1:
                inputMessage(&myMsg);
                break;

            case 2:
                displayMessage(&myMsg);
                printf("Index of Coincidence: %d\n", coincidenceIndex(myMsg));
                break;

            case 3:
                toUppercase(&myMsg);
                printf("Updated: %s\n", myMsg.text);
                break;

            case 4:
                toLowercase(&myMsg);
                printf("Updated: %s\n", myMsg.text);
                break;

            case 5:
                reverseMessage(&myMsg);
                printf("Reversed: %s\n", myMsg.text);
                break;

            case 6:
                printf("Enter shift (positive to encrypt, negative to decrypt): ");
                scanf("%d", &shift);
                while(getchar() != '\n');
                encryptCeaser(&myMsg, shift); // Reuses the same logic for both
                printf("Result: %s\n", myMsg.text);
                break;

            case 7:
                printf("Enter XOR key string: ");
                scanf("%s", keyStr);
                while(getchar() != '\n');
                encryptXOR(&myMsg, keyStr);
                printf("Result: %s\n", myMsg.text);
                break;

            case 8:
                printf("Enter 26-char substitution alphabet: ");
                scanf("%s", subKey);
                while(getchar() != '\n');
                if(isValidKey(subKey)) {
                    encryptSubstitution(&myMsg, subKey);
                    printf("Result: %s\n", myMsg.text);
                } else {
                    printf("Invalid Key! Must be 26 unique letters.\n");
                }
                break;

            case 9:
                frequencyAnalysis(myMsg);
                break;

            case 0:
                printf("Returning to Main Menu...\n");
                break;

            default:
                printf("Invalid option.\n");
        }
    } while (subChoice != 0);
}

void mathMenu() {
    int subChoice, a, b, n, min, max;
    struct Matrix matA, matB, matResult;

    do {
        printf("\n--- MATHEMATICAL & SECURITY TOOLS ---");
        printf("\n1. Basic Number Theory (Prime, GCD, Even)");
        printf("\n2. Arithmetic Properties (Factorial, Armstrong, etc.)");
        printf("\n3. Array Operations (Sort, Avg, Max/Min)");
        printf("\n4. Matrix Operations (Add, Multiply, Transpose)");
        printf("\n5. Modular Exponentiation (RSA Tool)");
        printf("\n0. Back to Main Menu");
        printf("\nChoice: ");
        scanf("%d", &subChoice);

        switch(subChoice) {
            case 1:
                printf("Enter a number: "); scanf("%d", &a);
                printf("Is Prime: %s\n", isPrime(a) ? "Yes" : "No");
                printf("Is Even: %s\n", isEven(a) ? "Yes" : "No");
                printf("Enter a second number for GCD: "); scanf("%d", &b);
                printf("GCD(%d, %d) = %d\n", a, b, gcd(a, b));
                break;

            case 2:
                printf("Enter a number: "); scanf("%d", &n);
                printf("Factorial: %g\n", factorial(n));
                printf("Is Armstrong: %s\n", isArmstrong(n) ? "Yes" : "No");
                printf("Is Palindrome: %s\n", isPalindromeNumber(n) ? "Yes" : "No");
                break;

            case 3: {
                int arr[50], size;
                printf("Enter array size: "); scanf("%d", &size);
                for(int i=0; i<size; i++) {
                    printf("Element [%d]: ", i); scanf("%d", &arr[i]);
                }
                printf("Max: %d, Min: %d\n", maxArray(arr, size), minArray(arr, size));
                printf("Average: %.2f\n", averageArray(arr, size));
                sortAscending(arr, size);
                printf("Sorted: ");
                for(int i=0; i<size; i++) printf("%d ", arr[i]);
                printf("\n");
                break;
            }

            case 4:
                // Example for Matrix Addition
                printf("Matrix A rows & cols: "); scanf("%d %d", &matA.n, &matA.p);
                for(int i=0; i<matA.n; i++)
                    for(int j=0; j<matA.p; j++) {
                        printf("A[%d][%d]: ", i, j); scanf("%d", &matA.data[i][j]);
                    }
                
                printf("Matrix B rows & cols: "); scanf("%d %d", &matB.n, &matB.p);
                for(int i=0; i<matB.n; i++)
                    for(int j=0; j<matB.p; j++) {
                        printf("B[%d][%d]: ", i, j); scanf("%d", &matB.data[i][j]);
                    }

                addMatrices(matA, matB, &matResult);
                printf("\nResulting Matrix:\n");
                displayMatrix(matResult);
                break;

            case 5: {
                int base, exp, mod;
                printf("Enter Base, Exponent, and Modulo: ");
                scanf("%d %d %d", &base, &exp, &mod);
                printf("Result: %d\n", modExp(base, exp, mod));
                break;
            }
        }
    } while (subChoice != 0);
}

void userMenu() {
    struct User database[100] = {0};
    int userCount = 0;
    int subChoice;
    char tempName[20], tempPass[20];
    
    memset(database, 0, sizeof(database));
    loadUsers(database, 100);

    do {
        printf("\n--- NSCS USER MANAGEMENT ---");
        printf("\n1. Add New User (with Strong Password Check)");
        printf("\n2. List All Users / List Admins Only");
        printf("\n3. Change Password");
        printf("\n4. Change User Role");
        printf("\n5. Check Login (Authentication)");
        printf("\n6. Search / Delete User");
        printf("\n7. Account Control (Block/Unblock)");
        printf("\n8. Save Changes to Disk");
        printf("\n0. Back to Main Menu");
        printf("\nChoice: ");
        scanf("%d", &subChoice);

        switch(subChoice) {
case 1:
    if (userCount < 100) {
        // We pass the address of the specific slot we want to fill
        addUser(&database[userCount]); 
        
        // Only increment the count if the user was actually added
        if (database[userCount].name[0] != '\0') {
            userCount++;
        }
        printf("Total users now: %d\n", userCount);
    } else {
        printf("Database full!\n");
    }
    break;
            case 2:
                printf("1: All Users, 2: Admins Only: ");
                int listType; scanf("%d", &listType);
                if(listType == 2) listAdmins(database, 100);
                else listUsers(database, 100);
                break;
            case 3:
                printf("Enter username: "); scanf("%s", tempName);
                changePassword(database, 100, tempName);
                break;
            case 4:
            printf("Enter username: "); 
               scanf("%s", tempName);
    
              printf("Enter new role (0:User, 1:Admin): ");
              int newRole; 
              scanf("%d", &newRole); // Get the 4th argument here
    
               // Now pass all 4 arguments: array, size, name, and the new role
                changeRole(database, 100, tempName, newRole); 
                 break;
            case 5:
                printf("--- Login ---\nUsername: "); scanf("%s", tempName);
                printf("Password: "); scanf("%s", tempPass);
                if(checkLogin(database, 100, tempName, tempPass)) 
                    printf("Login Successful!\n");
                else 
                    printf("Login Failed. Invalid credentials or blocked account.\n");
                break;
            case 6:
                printf("Enter username: "); scanf("%s", tempName);
                if(searchUser(database, 100, tempName) != -1) {
                    printf("User found. Delete? (1:Yes/0:No): ");
                    int del; scanf("%d", &del);
                    if(del) deleteUser(database, 100, tempName);
                } else printf("User not found.\n");
                break;
            case 7:
                printf("Enter username: "); scanf("%s", tempName);
                printf("Action (1:Block / 2:Unblock): ");
                int act; scanf("%d", &act);
                if(act == 1) blockUser(database, 100, tempName);
                else unblockUser(database, 100, tempName);
                break;
            case 8:
                saveUsers(database, 100);
                break;
        }
    } while (subChoice != 0);
}


void auditMenu() {
    struct User users[100];
    int subChoice, len;
    char tempPass[30], tempText[200];
    
    // Load current users to analyze their security
    loadUsers(users, 100);

    do {
        printf("\n--- SECURITY AUDIT & REPORTING ---");
        printf("\n1. Global Security Report (Database Analysis)");
        printf("\n2. Password Strength Tester & Scoring");
        printf("\n3. Password Generator (Random / Hex)");
        printf("\n4. Format Validator (Email / Login)");
        printf("\n5. Security Tips & Best Practices");
        printf("\n0. Back to Main Menu");
        printf("\nChoice: ");
        scanf("%d", &subChoice);
        getchar(); // Clear newline buffer

        switch(subChoice) {
            case 1:
                printf("\nGenerating Audit Report...\n");
                displaySecurityReport(users, 100);
                printf("Average Security Score: %.2f/10\n", averageScore(users, 100));
                printf("Global Security Level: %d/5\n", globalSecurityLevel(users, 100));
                printf("Top 3 Weakest Passwords detected.\n");
                top3Passwords(users, 100);
                break;

            case 2:
                printf("Enter password to audit: ");
                scanf("%s", tempPass);
                int score = passwordScore(tempPass);
                printf("Strength Score: %d/10\n", score);
                if(veryStrongPassword(tempPass)) printf("Verdict: EXCELLENT\n");
                else printf("Verdict: NEEDS IMPROVEMENT\n");
                break;

            case 3:
                printf("Enter desired length: ");
                scanf("%d", &len);
                generateRandomPassword(len, tempPass);
                printf("Generated Random: %s\n", tempPass);
                generateHexKey(len, tempPass);
                printf("Generated Hex Key: %s\n", tempPass);
                break;

            case 4:
printf("\n1. Check Email\n2. Check Login Format\n3. Text Statistics\nChoice: ");
    int fmtChoice; scanf("%d", &fmtChoice);
    printf("Enter text: ");
    scanf("%s", tempText);
    
    if(fmtChoice == 1) {
        printf("Email Format: %s\n", checkEmailFormat(tempText) ? "VALID" : "INVALID");
    } else if(fmtChoice == 2) {
        printf("Login Format: %s\n", checkLoginFormat(tempText) ? "VALID" : "INVALID");
    } else {
        displayTextStats(tempText); // Shows Uppercase, Lowercase, Digits counts
    }
    break;
    

            case 5:
                showSecurityTips();
                break;
        }
    } while (subChoice != 0);
}


void logsMenu() {
    struct Log systemLogs[500]; // Static array for 500 log entries
    int subChoice;
    char tempBuffer[50];

    // Initialize and load existing logs
    initLogs(systemLogs, 500);
    importLogsCSV(systemLogs, 500);

    do {
        printf("\n--- LOG MANAGEMENT SYSTEM ---");
        printf("\n1. View All Logs");
        printf("\n2. Search Logs (by User or Date)");
        printf("\n3. System Statistics & Error Rate");
        printf("\n4. Detect Suspicious Activity");
        printf("\n5. Export Logs to CSV");
        printf("\n6. Clear Log History");
        printf("\n0. Back to Main Menu");
        printf("\nChoice: ");
        scanf("%d", &subChoice);
        getchar(); // Buffer clear

        switch(subChoice) {
            case 1:
                displayLogs(systemLogs, 500);
                break;
            case 2:
                printf("Search by (1: User / 2: Date): ");
                int searchType; scanf("%d", &searchType);
                printf("Enter search term: "); scanf("%s", tempBuffer);
                if(searchType == 1) searchLogsByUser(systemLogs, 500, tempBuffer);
                else searchLogsByDate(systemLogs, 500, tempBuffer);
                break;
            case 3:
                displayLogStats(systemLogs, 500);
                printf("Current Error Rate: %.2f%%\n", errorRate(systemLogs, 500));
                break;
            case 4:
                printf("Enter username to analyze: ");
                scanf("%s", tempBuffer);
                if(detectSuspiciousActivity(systemLogs, 500, tempBuffer))
                    printf("ALERT: Suspicious activity patterns detected for %s!\n", tempBuffer);
                else
                    printf("Activity for %s appears normal.\n", tempBuffer);
                break;
            case 5:
                exportLogsCSV(systemLogs, 500);
                printf("Logs successfully exported to 'logs.csv'.\n");
                break;
            case 6:
                clearLogs(systemLogs, 500);
                break;
        }
    } while (subChoice != 0);
}

void helpMenu() {
    printf("\n=========================================\n");
    printf("           SYSTEM HELP & GUIDE           \n");
    printf("=========================================\n");
    printf("1. Encryption: Encrypt/Decrypt messages using\n");
    printf("   Caesar, XOR, or Substitution ciphers.\n");
    printf("2. Math Tools: Perform number theory tests,\n");
    printf("   array stats, and matrix operations.\n");
    printf("3. User Mgmt: CRUD operations for system users\n");
    printf("   and password strength validation.\n");
    printf("4. Audit: Analyze global security levels and\n");
    printf("   generate secure random keys.\n");
    printf("5. Logs: Track all system events and export\n");
    printf("   them to a CSV file for analysis.\n");
    printf("=========================================\n");
}

void aboutMenu() {
    printf("\n=========================================\n");
    printf("   Security Utility Library Suite v1.0   \n");
    printf("   -----------------------------------   \n");
    printf("   Course: Algorithms & Data Structures  \n");
    printf("   Institution: NSCS                     \n");
    printf("   Developer: Bendif islam & Fellag Abderhman\n");
    printf("   Academic Year: 2025-2026              \n");
    printf("=========================================\n");
}

int main(){
     int choice;
    do {
      printf("\n==============================\n");
      printf("   NSCS SECURITY UTILITY SUITE  \n");
      printf("==============================\n");
      printf("1. Encryption\n2. Math Tools\n3. User Management\n4. Security Audit\n5. Log Management\n6. Help\n7. About\n0. Exit\nChoice: ");
      printf("Choice: ");
      scanf("%d", &choice);

      
   switch(choice){
    case 1: encryptionMenu();break;
    case 2: mathMenu();      break;
    case 3: userMenu();      break;
    case 4: auditMenu();     break;
    case 5: logsMenu();      break;
    case 6: helpMenu();      break;   
    case 7: aboutMenu();     break;
    default: printf("Invalid choice! Please try again. \n");
   }
} while(choice != 0);
    return 0;
}
