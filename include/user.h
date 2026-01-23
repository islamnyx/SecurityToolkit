#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <string.h>

/**
 * 5.1. Structure
 */
struct User {
    char name[20];
    char password[20];
    int role;  // 0: user, 1: admin
    int state; // 0: active, 1: blocked
};

/**
 * 5.2. Functions and Procedures
 */


// --- Initialization and Display ---
void initUsers(struct User users[], int n);
void listUsers(struct User users[], int n);
void userStatistics(struct User users[], int n);
void listAdmins(struct User users[], int n);

// --- CRUD Operations (Create, Read, Update, Delete) ---
void addUser(struct User *u);
void deleteUser(struct User users[], int n, char name[]);
int  searchUser(struct User users[], int n, char name[]);

// --- Account Management ---
void changePassword(struct User users[], int n, char name[]);
void blockUser(struct User users[], int n, char name[]);
void unblockUser(struct User users[], int n, char name[]);
void changeRole(struct User users[], int n, char name[], int role);

// --- Authentication and Validation ---
int checkLogin(struct User users[], int n, char name[], char pass[]);
int strongPassword(char pass[]);

// --- String Utility Functions ---
int stringLength(char str[]);
int containsUppercase(char str[]);
int containsLowercase(char str[]);
int containsDigit(char str[]);
int containsSymbol(char str[]);

// --- File Persistence ---
void saveUsers(struct User users[], int n);
int loadUsers(struct User users[], int n);

#endif // USER_H