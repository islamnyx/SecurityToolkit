#include <stdio.h>
#include <stdbool.h>
#include "math_tools.h"
#include <math.h>
#include <stdlib.h>

// 1. Checks if a number is even
int isEven(int n) {
    return (n % 2 == 0);
}

// 2. Checks if a number is prime 
int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// 3. Computes Greatest Common Divisor 
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 4. Computes Least Common Multiple
int lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return abs(a * b) / gcd(a, b);
}

// 5. Modular Exponentiation (base^exp % mod) - Essential for RSA
int modExp(int base, int exp, int mod) {
    long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * (long long)base) % mod;
        exp = exp / 2;
    }
    return (int)res;
}

// 6-8. Arithmetic Utilities
double factorial(int n) {
    if (n < 0) return 0; // Factorial not defined for negative numbers
    if (n == 0 || n == 1) return 1.0;
    
    double result = 1.0;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int sumDigits(int n) {
    int sum = 0;
    n = abs(n);
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int reverseNumber(int n) {
    int reversed = 0;
    int sign = (n < 0) ? -1 : 1;
    n = abs(n);
    while (n > 0) {
        reversed = reversed * 10 + (n % 10);
        n /= 10;
    }
    return reversed * sign;
}

// 9-12. Number Property Checks
int isPalindromeNumber(int n) {
    if (n < 0) return 0;
    return (n == reverseNumber(n));
}

int sumDivisors(int n) {
    int sum = 0;
    int val = abs(n);
    for (int i = 1; i <= val / 2; i++) {
        if (val % i == 0) sum += i;
    }
    return sum;
}

int isPerfectNumber(int n) {
    if (n <= 0) return 0;
    return (n == sumDivisors(n));
}

int isArmstrong(int n) {
    int sum = 0, temp = abs(n), digits = 0;
    int original = temp;
    while (temp > 0) { temp /= 10; digits++; }
    temp = original;
    while (temp > 0) {
        sum += pow(temp % 10, digits);
        temp /= 10;
    }
    return (sum == original);
}

// 13. Random Number Generator
int randomNumber(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

// 14-18. Array Utilities
int sumArray(int T[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) sum += T[i];
    return sum;
}

float averageArray(int T[], int n) {
    if (n == 0) return 0;
    return (float)sumArray(T, n) / n;
}

int maxArray(int T[], int n) {
    int max = T[0];
    for (int i = 1; i < n; i++) if (T[i] > max) max = T[i];
    return max;
}

int minArray(int T[], int n) {
    int min = T[0];
    for (int i = 1; i < n; i++) if (T[i] < min) min = T[i];
    return min;
}

void sortAscending(int T[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (T[i] > T[j]) {
                int temp = T[i];
                T[i] = T[j];
                T[j] = temp;
            }
        }
    }
}

// 19-25. Matrix Operations
void displayMatrix(struct Matrix M) {
    for (int i = 0; i < M.n; i++) {
        for (int j = 0; j < M.p; j++) {
            printf("%d\t", M.data[i][j]);
        }
        printf("\n");
    }
}

void addMatrices(struct Matrix A, struct Matrix B, struct Matrix *C) {
    if (A.n != B.n || A.p != B.p) return;
    C->n = A.n; C->p = A.p;
    for (int i = 0; i < A.n; i++)
        for (int j = 0; j < A.p; j++)
            C->data[i][j] = A.data[i][j] + B.data[i][j];
}

void multiplyMatrices(struct Matrix A, struct Matrix B, struct Matrix *C) {
    if (A.p != B.n) return;
    C->n = A.n; C->p = B.p;
    for (int i = 0; i < A.n; i++) {
        for (int j = 0; j < B.p; j++) {
            C->data[i][j] = 0;
            for (int k = 0; k < A.p; k++)
                C->data[i][j] += A.data[i][k] * B.data[k][j];
        }
    }
}

void transposeMatrix(struct Matrix A, struct Matrix *T) {
    T->n = A.p; T->p = A.n;
    for (int i = 0; i < A.n; i++)
        for (int j = 0; j < A.p; j++)
            T->data[j][i] = A.data[i][j];
}

int determinant2x2(int A[2][2]) {
    return (A[0][0] * A[1][1]) - (A[0][1] * A[1][0]);
}

int isSymmetric(struct Matrix M) {
    if (M.n != M.p) return 0;
    for (int i = 0; i < M.n; i++)
        for (int j = 0; j < M.p; j++)
            if (M.data[i][j] != M.data[j][i]) return 0;
    return 1;
}

int isIdentity(struct Matrix M) {
    if (M.n != M.p) return 0;
    for (int i = 0; i < M.n; i++)
        for (int j = 0; j < M.p; j++) {
            if (i == j && M.data[i][j] != 1) return 0;
            if (i != j && M.data[i][j] != 0) return 0;
        }
    return 1;
}