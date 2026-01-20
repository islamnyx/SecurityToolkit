#ifndef AUDIT_H
#define AUDIT_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// --- Structure Definition ---
struct User {
    char name[20];
    char password[20];
    int role;   // 0: user, 1: admin
    int state;  // 0: active, 1: blocked
};

// --- Function Prototypes ---

// Character Counting & Stats
int countUppercase(char text[]);
int countLowercase(char text[]);
int countDigits(char text[]);
float percentUppercase(char text[]);
int textlength(char text[]);
void displayTextStats(char text[]);

// Password Strength & Validation
int veryStrongPassword(char pass[]);
int passwordScore(char key[]);
void generateRandomPassword(int length, char pass[]);
int isHexKey(char key[]);
void generateHexKey(int length, char key[]);

// Formatting & Format Checks
int checkEmailFormat(char email[]);
int checkLoginFormat(char login[]);

// Global Security & Reporting
float averageScore(struct User users[], int n);
void displaySecurityReport(struct User users[], int n);
int countStrongUsers(struct User users[], int n);
void showSecurityTips();
void top3Passwords(struct User users[], int n);
int globalSecurityLevel(struct User users[], int n);

// Utility
void generateKey(int length, char key[]);

#endif // AUDIT_H