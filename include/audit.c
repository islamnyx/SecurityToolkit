#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

struct User {
    char name[20];
    char password[20];
    int role;   // 0: user, 1: admin
    int state;  // 0: active, 1: blocked
};

/* ================= TEXT STATS ================= */

int countUppercase(char text[]) {
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) count++;
    }
    return count;
}

int countLowercase(char text[]) {
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (islower(text[i])) count++;
    }
    return count;
}

int countDigits(char text[]) {
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isdigit(text[i])) count++;
    }
    return count;
}

float percentUppercase(char text[]) {
    int length = strlen(text);
    if (length == 0) return 0.0;

    int count = countUppercase(text);
    return ((float)count * 100.0f) / length;
}

int textlength(char text[]) {
    int len = 0;
    while (text[len] != '\0') {
        len++;
    }
    return len;
}

void displayTextStats(char text[]) {
    printf("%d\n", countUppercase(text));
    printf("%d\n", countLowercase(text));
    printf("%d\n", countDigits(text));
    printf("%.2f\n", percentUppercase(text));
}

/* ================= PASSWORD ================= */

int veryStrongPassword(char pass[]) {
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSymbol = 0;

    for (int i = 0; pass[i] != '\0'; i++) {
        if (isupper(pass[i])) hasUpper = 1;
        else if (islower(pass[i])) hasLower = 1;
        else if (isdigit(pass[i])) hasDigit = 1;
        else hasSymbol = 1;
    }

    return (hasUpper && hasLower && hasDigit && hasSymbol);
}

void generateKey(int length, char key[]) {
    char char_set[] =
        "abcdefghijklmnopqrstuvwxyz!@#$^&*()-_=+[]{}<>?"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    int char_set_length = strlen(char_set);

    for (int i = 0; i < length; i++) {
        key[i] = char_set[rand() % char_set_length];
    }
    key[length] = '\0';

    printf("The Generated Key is: %s\n", key);
}

int isHexKey(char key[]) {
    for (int i = 0; key[i] != '\0'; i++) {
        if (!(
            (key[i] >= '0' && key[i] <= '9') ||
            (key[i] >= 'a' && key[i] <= 'f') ||
            (key[i] >= 'A' && key[i] <= 'F')
        )) {
            return 0; // Not hex
        }
    }
    return 1; // Valid hex key
}

void generateRandomPassword(int length, char pass[]) {
    char char_set[] =
        "abcdefghijklmnopqrstuvwxyz!@#$^&*()-_=+[]{}<>?"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    int char_set_length = strlen(char_set);

    for (int i = 0; i < length; i++) {
        pass[i] = char_set[rand() % char_set_length];
    }
    pass[length] = '\0';

    printf("The Generated Password is: %s\n", pass);
}

int passwordScore(char key[]) {
    int score = 0;
    int length = strlen(key);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSymbol = 0;

    if (length >= 8) score += 1;
    if (length >= 12) score += 1;
    if (length >= 16) score += 2;

    for (int i = 0; i < length; i++) {
        if (isupper(key[i])) hasUpper = 1;
        else if (islower(key[i])) hasLower = 1;
        else if (isdigit(key[i])) hasDigit = 1;
        else hasSymbol = 1;
    }

    score += hasUpper + hasLower + hasDigit + hasSymbol;
    return score;
}

/* ================= USERS ================= */

float averageScore(struct User users[], int n) {
    if (n <= 0) return 0.0f;

    int totalScore = 0;
    for (int i = 0; i < n; i++) {
        totalScore += passwordScore(users[i].password);
    }
    return (float)totalScore / n;
}

void displaySecurityReport(struct User users[], int n) {
    printf("Average Password Security Score: %.2f\n",
           averageScore(users, n));

    int weakCount = 0;
    for (int i = 0; i < n; i++) {
        if (passwordScore(users[i].password) < 3) {
            weakCount++;
            printf("Weak Password User: %s\n", users[i].name);
        }
    }
    printf("Total Users with Weak Passwords: %d\n", weakCount);
}

int countStrongUsers(struct User users[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (passwordScore(users[i].password) >= 5)
            count++;
    }
    return count;
}

/**
 * Computes the global security level of the system.
 * Returns: 
 * 0: Dangerous (Avg < 2)
 * 1: Weak (Avg < 4)
 * 2: Moderate (Avg < 6)
 * 3: Strong (Avg >= 6)
 */
int globalSecurityLevel(struct User users[], int n) {
    if (n <= 0) return 0; // Cannot assess an empty system

    float avg = averageScore(users, n);

    if (avg < 2.0) {
        return 0; // Dangerous
    } else if (avg < 4.0) {
        return 1; // Weak
    } else if (avg < 6.0) {
        return 2; // Moderate
    } else {
        return 3; // Strong
    }
}

/* ================= VALIDATION ================= */

int checkEmailFormat(char email[]) {
    int atCount = 0, dotCount = 0;

    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') atCount++;
        else if (email[i] == '.') dotCount++;
    }
    return (atCount == 1 && dotCount >= 1);
}

int checkLoginFormat(char login[]) {
    for (int i = 0; login[i] != '\0'; i++) {
        if (!(isalnum(login[i]) || login[i] == '_' || login[i] == '.'))
            return 0;
    }
    return 1;
}

/* ================= HEX ================= */

void generateHexKey(int length, char key[]) {
    const char hex_chars[] = "0123456789ABCDEF";

    for (int i = 0; i < length; i++) {
        key[i] = hex_chars[rand() % 16];
    }
    key[length] = '\0';

    printf("The Generated Hex Key is: %s\n", key);
}
