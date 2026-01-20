#ifndef LOGS_H
#define LOGS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * 7.1. Structure
 */
struct Log {
    char user[20];
    char action[50];
    char date[20];   // Format: YYYY-MM-DD
    char time[10];   // Format: HH:MM
    int code;        // 0: info, 1: warning, 2: error
};

/**
 * 7.2. Functions and Procedures
 */

// Basic Management
void initLogs(struct Log logs[], int n);
void addLog(struct Log logs[], int n, char user[], char action[], int code);
void displayLogs(struct Log logs[], int n);
void clearLogs(struct Log logs[], int n);

// Search Functions
void searchLogsByUser(struct Log logs[], int n, char user[]);
void searchLogsByDate(struct Log logs[], int n, char date[]);

// Counters
int countErrorLogs(struct Log logs[], int n);
int countLoginLogs(struct Log logs[], int n);
int countBlockedLogs(struct Log logs[], int n);

// Statistics and Analysis
void displayLogStats(struct Log logs[], int n);
int detectSuspiciousActivity(struct Log logs[], int n, char user[]);
int dailyConnections(struct Log logs[], int n, char date[]);
float errorRate(struct Log logs[], int n);
void showTopErrors(struct Log logs[], int n);

// Sorting
void sortLogsByDate(struct Log logs[], int n);
void sortLogsByUser(struct Log logs[], int n);

// Persistence (File I/O)
void exportLogsCSV(struct Log logs[], int n);
void importLogsCSV(struct Log logs[], int n);
void archiveLogs(struct Log logs[], int n);

// Recent Events
void recentLogs(struct Log logs[], int n, int nb);

#endif // LOGS_H