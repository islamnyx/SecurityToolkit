#include "logs.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

void initLogs(struct Log logs[], int n) {
    for (int i = 0; i < n; i++) {
        strcpy(logs[i].user, "");
        strcpy(logs[i].action, "");
        strcpy(logs[i].date, "");
        strcpy(logs[i].time, "");
        logs[i].code = 0;
    }
}

void addLog(struct Log logs[], int n, char user[], char action[], int code) {
    for (int i = 0; i < n; i++) {
        if (strcmp(logs[i].user, "") == 0) {
            strncpy(logs[i].user, user, sizeof(logs[i].user) - 1);
            strncpy(logs[i].action, action, sizeof(logs[i].action) - 1);

            // Get current date and time
            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            strftime(logs[i].date, sizeof(logs[i].date), "%Y-%m-%d", t);
            strftime(logs[i].time, sizeof(logs[i].time), "%H:%M", t);

            logs[i].code = code;
            break;
        }
    }
}


void displayLogs(struct Log logs[], int n) {
    printf("User\tAction\tDate\tTime\tCode\n");
    for (int i = 0; i < n; i++) {
        if (strcmp(logs[i].user, "") != 0) {
            printf("%s\t%s\t%s\t%s\t%d\n",
                   logs[i].user,
                   logs[i].action,
                   logs[i].date,
                   logs[i].time,
                   logs[i].code);
        }
    }
}


void searchLogsByUser(struct Log logs[], int n, char user[]) {
    printf("Logs for user: %s\n", user);
    for (int i = 0; i < n; i++) {
        if (strcmp(logs[i].user, user) == 0) {
            printf("%s\t%s\t%s\t%s\t%d\n",
                   logs[i].user,
                   logs[i].action,
                   logs[i].date,
                   logs[i].time,
                   logs[i].code);
        }
    }
}

void searchLogsByDate(struct Log logs[], int n, char date[]) {
    printf("Logs for date: %s\n", date);
    for (int i = 0; i < n; i++) {
        if (strcmp(logs[i].date, date) == 0) {
            printf("%s\t%s\t%s\t%s\t%d\n",
                   logs[i].user,
                   logs[i].action,
                   logs[i].date,
                   logs[i].time,
                   logs[i].code);
        }
    }
}

int countErrorLogs(struct Log logs[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (logs[i].code == 2) {
            count++;
        }
    }
    return count;
}

int countLoginLogs(struct Log logs[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (strstr(logs[i].action, "login") != NULL) {
            count++;
        }
    }
    return count;
}

int countBlockedLogs(struct Log logs[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (strstr(logs[i].action, "blocked") != NULL) {
            count++;
        }
    }
    return count;
}

void displayLogStats(struct Log logs[], int n) {
    int infoCount = 0, warningCount = 0, errorCount = 0;
    for (int i = 0; i < n; i++) {
        if (logs[i].code == 0) infoCount++;
        else if (logs[i].code == 1) warningCount++;
        else if (logs[i].code == 2) errorCount++;
    }
    printf("Info Logs: %d\n", infoCount);
    printf("Warning Logs: %d\n", warningCount);
    printf("Error Logs: %d\n", errorCount);
}

void sortLogsByDate(struct Log logs[], int n) {
    struct Log temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (strcmp(logs[i].date, logs[j].date) > 0) {
                temp = logs[i];
                logs[i] = logs[j];
                logs[j] = temp;
            }
        }
    }
}

void sortLogsByUser(struct Log logs[], int n) {
    struct Log temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (strcmp(logs[i].user, logs[j].user) > 0) {
                temp = logs[i];
                logs[i] = logs[j];
                logs[j] = temp;
            }
        }
    }
}

int detectSuspiciousActivity(struct Log logs[], int n, char user[]) {
    int failedLogins = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(logs[i].user, user) == 0 &&
            strstr(logs[i].action, "failed login") != NULL) {
            failedLogins++;
        }
    }
    return (failedLogins >= 5);
}

int dailyConnections(struct Log logs[], int n, char date[]) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(logs[i].date, date) == 0 &&
            strstr(logs[i].action, "login") != NULL) {
            count++;
        }
    }
    return count;
}

float errorRate(struct Log logs[], int n) {
    int errorCount = 0;
    for (int i = 0; i < n; i++) {
        if (logs[i].code == 2) {
            errorCount++;
        }
    }
    if (n == 0) return 0.0f;
    return ((float)errorCount * 100.0f) / n;
}


void exportLogsCSV(struct Log logs[], int n) {
    FILE *file = fopen("logs.csv", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "User,Action,Date,Time,Code\n");
    for (int i = 0; i < n; i++) {
        if (strcmp(logs[i].user, "") != 0) {
            fprintf(file, "%s,%s,%s,%s,%d\n",
                    logs[i].user,
                    logs[i].action,
                    logs[i].date,
                    logs[i].time,
                    logs[i].code);
        }
    }
    fclose(file);
}


void importLogsCSV(struct Log logs[], int n) {
    FILE *file = fopen("logs.csv", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    char line[150];
    fgets(line, sizeof(line), file); // Skip header
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL && i < n) {
        sscanf(line, "%19[^,],%49[^,],%19[^,],%9[^,],%d",
               logs[i].user,
               logs[i].action,
               logs[i].date,
               logs[i].time,
               &logs[i].code);
        i++;
    }
    fclose(file);
}


void clearLogs(struct Log logs[], int n) {
    for (int i = 0; i < n; i++) {
        strcpy(logs[i].user, "");
        strcpy(logs[i].action, "");
        strcpy(logs[i].date, "");
        strcpy(logs[i].time, "");
        logs[i].code = 0;
    }
}


void recentLogs(struct Log logs[], int n, int nb) {
    printf("Most Recent %d Logs:\n", nb);
    for (int i = n - nb; i < n; i++) {
        if (i >= 0 && strcmp(logs[i].user, "") != 0) {
            printf("%s\t%s\t%s\t%s\t%d\n",
                   logs[i].user,
                   logs[i].action,
                   logs[i].date,
                   logs[i].time,
                   logs[i].code);
        }
    }
}

void archiveLogs(struct Log logs[], int n) {
    FILE *file = fopen("logs_archive.txt", "a");
    if (file == NULL) {
        printf("Error opening archive file.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        if (strcmp(logs[i].user, "") != 0) {
            fprintf(file, "%s\t%s\t%s\t%s\t%d\n",
                    logs[i].user,
                    logs[i].action,
                    logs[i].date,
                    logs[i].time,
                    logs[i].code);
        }
    }
    fclose(file);
}


void showTopErrors(struct Log logs[], int n) {
    int errorCounts[3] = {0}; // 0: info, 1: warning, 2: error

    for (int i = 0; i < n; i++) {
        if (logs[i].code >= 0 && logs[i].code <= 2) {
            errorCounts[logs[i].code]++;
        }
    }

    printf("Log Code\tCount\n");
    for (int i = 2; i >= 0; i--) {
        printf("%d\t\t%d\n", i, errorCounts[i]);
    }
}