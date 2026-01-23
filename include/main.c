#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "encryption.h"
#include "math_tools.h"
#include "user.h"
#include "audit.h"
#include "logs.h"
#include <string.h>
#include <unistd.h>

// Function Prototypes
void clearScreen();
void cyberScanAnimation();
void startupSequence();
void shutdownSequence();
void enableVirtualTerminal();

void clearScreen() {
    printf("\033[H\033[J"); // Clears screen
}

void cyberScanAnimation() {
    char *lines[] = {
        "Checking Firewall...",
        "Scanning User Database...",
        "Verifying Encryption Keys...",
        "System Integrity: SECURE"
    };

    for(int i = 0; i < 4; i++) {
        // \033[1;33m is Yellow
        printf("\033[1;33m  [!] %-30s", lines[i]); 
        fflush(stdout);
        
        for(int j = 0; j < 3; j++) {
            usleep(200000); 
            printf(".");
            fflush(stdout);
        }
        // \033[1;32m is Green, \033[0m resets color
        printf("\033[1;32m [OK]\033[0m\n"); 
    }
    usleep(500000);
}

void startupSequence() {
    // Flash white
    printf("\033[47m"); clearScreen(); fflush(stdout); usleep(50000);
    // Back to black
    printf("\033[0m"); clearScreen(); fflush(stdout);
    clearScreen();
    
    // 1. Vertical Padding (Push it down the screen)
    for(int i = 0; i < 5; i++) printf("\n");

    // 2. Centered ASCII Art (Cyan Color)
    printf("\033[1;36m");
    printf("              _   _  ____   ____ ____  \n");
    printf("             | \\ | |/ ___| / ___/ ___| \n");
    printf("             |  \\| |\\___ \\| |   \\___ \\ \n");
    printf("             | |\\  | ___) | |___ ___) |\n");
    printf("             |_| \\_|____/ \\____|____/  \n");
    
    // 3. Subtitle
    printf("\n             NATIONAL SECURITY CYBER SUITE\n");
    printf("                [SYSTEM VERSION 2.0.1]\n\n");
    
    // 4. Centered Status Message
    printf("             ESTABLISHING SECURE CONNECTION");
    for(int i = 0; i < 5; i++) {
        usleep(300000);
        printf(".");
        fflush(stdout);
    }
    
    printf("\n\n                    \033[1;32m[ACCESS GRANTED]\033[0m\n");
    usleep(1000000);
    
    // 5. Trigger your firewall scan
    cyberScanAnimation();
}

void shutdownSequence() {
    clearScreen();
    
    // Move down to the middle of the screen
    for(int i = 0; i < 8; i++) printf("\n");

    printf("\033[1;31m"); // Bright Red
    printf("                [!] SYSTEM TERMINATING SESSION...\n\n");
    
    printf("                Cleaning Cache:  [");
    for(int i = 0; i < 20; i++) {
        usleep(150000); // Slower speed (0.15s)
        printf("█"); // If this still breaks, use '#'
        fflush(stdout);
    }
    printf("] DONE\n");

    printf("                Wiping Memory:   [");
    for(int i = 0; i < 20; i++) {
        usleep(150000);
        printf("█"); 
        fflush(stdout);
    }
    printf("] DONE\n");

    printf("\n\n                \033[1;37mLOGS SAVED. ENCRYPTION KEYS DESTROYED.\n");
    printf("                     SYSTEM OFFLINE. GOODBYE.\033[0m\n");

    // STAY ON SCREEN for 3 seconds so it's brilliant
    usleep(3000000); 
}



void enableVirtualTerminal() {
#ifdef _WIN32
    // 1. Fix the colors
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    // 2. Fix the symbols (UTF-8)
    SetConsoleOutputCP(CP_UTF8); 
#endif
}

void showLoadingBar(char* task) {
    printf("\n  %s: ", task);
    for (int i = 0; i < 20; i++) {
        printf("\033[42m "); // Green background block
        fflush(stdout);
        usleep(50000); // 0.05 seconds delay
    }
    printf("\033[0m [COMPLETE]\n");
}



void setCyberTheme() {
    printf("\033[1;32m"); // Bright Green (Matrix Style)
}

void resetColor() {
    printf("\033[0m"); // Back to standard white
}

void drawHeader(char* title) {
    clearScreen();
    setCyberTheme();
    printf("==========================================================\n");
    printf("  NSCS CYBER-SECURITY TOOLKIT v2.0 - [SYSTEM: ONLINE]    \n");
    printf("==========================================================\n");
    printf("  CURRENT MODULE: %s\n", title);
    printf("----------------------------------------------------------\n");
    resetColor();
}

void mainMenuGUI() {
    drawHeader("MAIN DASHBOARD");
    printf("\033[1;36m"); // Cyan color for options
    printf("  [1] > ENCRYPTION ENGINE\n");
    printf("  [2] > MATHEMATICAL ANALYSIS\n");
    printf("  [3] > USER & ACCESS CONTROL\n");
    printf("  [4] > SECURITY AUDIT\n");
    printf("  [5] > LOG MANAGEMENT\n");
    printf("  [0] > SHUTDOWN SYSTEM\n");
    printf("\033[0m");
    printf("\n  Selection > ");
}

#include <conio.h> // Required for _getch()

void getHiddenPassword(char password[], int maxLength) {
    int i = 0;
    char ch;

    while (1) {
        ch = _getch(); // Get key without printing

        if (ch == 13) { // 13 is the ASCII code for 'Enter'
            password[i] = '\0';
            break;
        } else if (ch == 8) { // 8 is 'Backspace'
            if (i > 0) {
                i--;
                printf("\b \b"); // Erase the * from the screen
            }
        } else if (i < maxLength - 1) {
            password[i++] = ch;
            printf("*"); // Print star instead of the letter
        }
    }
    printf("\n");
}

void saveSecureDatabase(struct User users[], int n, int key) {
    FILE *fp = fopen("users.dat", "w");
    FILE *fcp = fopen("config.ini", "w");
    int checksum = 0;

    for (int i = 0; i < n; i++) {
        char tempBuffer[256];
        // 1. Create the plain data string
        sprintf(tempBuffer, "%s|%s|%d|%d|%d", 
                users[i].name, users[i].password, 
                users[i].role, users[i].state, users[i].failedAttempts);

        // 2. Calculate Checksum BEFORE encryption
        for(int j = 0; tempBuffer[j] != '\0'; j++) {
            checksum += (int)tempBuffer[j];
        }

        // 3. Prepare struct Message for your library
        struct Message m;
        strncpy(m.text, tempBuffer, sizeof(m.text)); // Use .text instead of .content
        
        // 4. Call your library
        encryptCeaser(&m, key);

        // 5. Save the encrypted text to the file
        fprintf(fp, "%s\n", m.text);
    }

    fprintf(fcp, "%d", checksum);
    fclose(fp);
    fclose(fcp);
    printf("\033[1;32m[!] Database Sealed and Encrypted.\033[0m\n");
}

void loadSecureDatabase(struct User users[], int *n, int key) {
    int expectedChecksum = 0;
    FILE *fcp = fopen("config.ini", "r");
    if (fcp) {
        fscanf(fcp, "%d", &expectedChecksum);
        fclose(fcp);
    }

    FILE *fp = fopen("users.dat", "r");
    if (!fp) return;

    char line[256];
    int actualChecksum = 0;
    *n = 0;

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0; // Clean newline

        // 1. Load into your Message struct
        struct Message m;
        strncpy(m.text, line, sizeof(m.text));

        // 2. Decrypt
        decryptCeaser(&m, key);

        // 3. Checksum the decrypted text
        for(int j = 0; m.text[j] != '\0'; j++) {
            actualChecksum += (int)m.text[j];
        }

        // 4. Parse back into User struct
        sscanf(m.text, "%[^|]|%[^|]|%d|%d|%d", 
               users[*n].name, users[*n].password, 
               &users[*n].role, &users[*n].state, &users[*n].failedAttempts);
        (*n)++;
    }
    fclose(fp);

    if (actualChecksum != expectedChecksum) {
        printf("\n\033[5;41m [!] TAMPERING DETECTED: INVALID CHECKSUM [!] \033[0m\n");
        exit(1); 
    }
}

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
    // Use %.4f to show 4 decimal places of the float result
    printf("Index of Coincidence: %.4f\n", coincidenceIndex(myMsg));
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

    printf("Result (Safe View): ");
    for(int i = 0; i < myMsg.length; i++) {
        // isprint() checks if the character can be safely displayed
        if (isprint((unsigned char)myMsg.text[i])) {
            printf("%c", myMsg.text[i]);
        } else {
            printf("."); // Show a dot for "messy" control characters
        }
    }
    
    printf("\nResult (Hex):      ");
    for(int i = 0; i < myMsg.length; i++) {
        printf("%02X ", (unsigned char)myMsg.text[i]);
    }
    printf("\n");
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

void userMenu(struct User database[], int *userCount, struct Log logDatabase[]) {
    int subChoice;
    char tempName[20], tempPass[20];
    
    memset(database, 0, 100 * sizeof(struct User));
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
    if (*userCount < 100) {  // 1. Dereference to check the value
        // 2. Dereference to use as an index
        addUser(&database[*userCount], logDatabase); 
        
        // 3. Dereference to check if user was added
        if (database[*userCount].name[0] != '\0') {
            (*userCount)++;  // 4. Dereference to increment the real count in main
        }
    } else {
        printf("Database is full!\n");
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
              changePassword(database, 100, tempName, logDatabase);
                break;
case 4:
    printf("Enter username: "); 
    scanf("%s", tempName);
    printf("Enter new role (0:User, 1:Admin): ");
    int newRole; 
    scanf("%d", &newRole);

    
    changeRole(database, 100, tempName, newRole, logDatabase); 
    break;
            case 5: // Login
    printf("--- Login ---\nUsername: "); 
    scanf("%s", tempName);
    printf("Password: "); 
    getHiddenPassword(tempPass, 20);

    if (checkLogin(database, 100, tempName, tempPass, logDatabase)) {
        // SUCCESS PATH
        printf("\n\033[1;32m[ACCESS GRANTED]\033[0m\n");
        cyberScanAnimation(); // The cool animation you added
        printf("Welcome, %s. Security session initialized.\n", tempName);
    } 
    else {
        // ERROR PATH - The compiler needs this statement!
        printf("\n\033[1;31m[ACCESS DENIED]\033[0m\n");
        printf("Invalid credentials or account is blocked. Incident logged.\n");
    }
    break;
            case 6:
                 printf("Enter username: "); scanf("%s", tempName);
                if(searchUser(database, 100, tempName) != -1) {
                    printf("User found. Delete? (1:Yes/0:No): ");
                    int del; scanf("%d", &del);
                    // Pass the logDatabase here!
                    if(del) deleteUser(database, 100, tempName, logDatabase); 
                } else printf("User not found.\n");
                break;
            case 7:
                printf("Enter username: "); scanf("%s", tempName);
                printf("Action (1:Block / 2:Unblock): ");
                int act; scanf("%d", &act);
                // Pass the logDatabase here!
                if(act == 1) blockUser(database, 100, tempName, logDatabase);
                else unblockUser(database, 100, tempName, logDatabase);
                break;
            case 8:
                saveUsers(database, 100);
                exportLogsCSV(logDatabase, 100); // Saves logs to an Excel-friendly file
                printf("All data and logs saved to disk.\n");
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


void logMenu(struct Log logs[], int n) {
    int choice, count;
    char temp[30];

    do {
        printf("\n--- SYSTEM LOG & AUDIT MANAGEMENT ---");
        printf("\n1. View All Logs");
        printf("\n2. Search Logs (by User or Date)");
        printf("\n3. Security Statistics & Error Rate");
        printf("\n4. Detect Suspicious Activity");
        printf("\n5. Export Logs to CSV (Excel Compatible)");
        printf("\n6. Archive & Clear Current Logs");
        printf("\n0. Back to Main Menu");
        printf("\nChoice: ");
        scanf("%d", &choice);
        getchar(); // Clean buffer

        switch(choice) {
            case 1:
                displayLogs(logs, n);
                break;
            case 2:
                printf("1. Search by User\n2. Search by Date\nChoice: ");
                int sType; scanf("%d", &sType);
                printf("Enter search term: "); scanf("%s", temp);
                if(sType == 1) searchLogsByUser(logs, n, temp);
                else searchLogsByDate(logs, n, temp);
                break;
            case 3:
                displayLogStats(logs, n);
                printf("System Error Rate: %.2f%%\n", errorRate(logs, n));
                showTopErrors(logs, n);
                break;
            case 4:
                printf("Enter username to check: "); scanf("%s", temp);
                if(detectSuspiciousActivity(logs, n, temp))
                    printf("ALERT: Suspicious activity (5+ failed logins) detected for %s!\n", temp);
                else
                    printf("Activity for %s appears normal.\n", temp);
                break;
            case 5:
                exportLogsCSV(logs, n);
                printf("Logs successfully exported to 'logs.csv'.\n");
                break;
            case 6:
                archiveLogs(logs, n);
                clearLogs(logs, n);
                printf("Logs archived to 'logs_archive.txt' and current memory cleared.\n");
                break;
        }
    } while (choice != 0);
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
    enableVirtualTerminal();
    startupSequence();
    
    struct User database[100] = {0};
    struct Log logDatabase[100] = {0}; 
    initLogs(logDatabase, 100);
    int userCount = 0;
     int choice;

    do {
        mainMenuGUI(); // This handles clearScreen, Header, and Menu
        if (scanf("%d", &choice) != 1) break;

      
   switch(choice){
    case 1: encryptionMenu();break;
    case 2: mathMenu();      break;
    case 3: showLoadingBar("INITIALIZING USER DATABASE"); userMenu(database, &userCount, logDatabase); break;
    case 4: auditMenu();     break;
    case 5: showLoadingBar("FETCHING SYSTEM LOGS");  logMenu(logDatabase, 100);     break;
    case 6: helpMenu();      break;   
    case 7: aboutMenu();     break;
    case 0: shutdownSequence(); break;
    default: printf("\033[1;31mInvalid choice! Please try again.\033[0m\n");
            usleep(1000000);
   }
} while(choice != 0);
    return 0;
}
