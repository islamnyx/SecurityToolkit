#ifndef MATH_TOOLS_H
#define MATH_TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * 4.1. Structure
 */
struct Matrix {
    int data[10][10];
    int n; // Rows
    int p; // Columns
};

/**
 * 4.2. Functions and Procedures
 */

// --- Basic Number Theory (Security Tools) ---
int isEven(int n);
int isPrime(int n);
int gcd(int a, int b);
int lcm(int a, int b);

// Modular Exponentiation (Essential for RSA)
// Computes (base^exp) % mod
int modExp(int base, int exp, int mod);

// --- Arithmetic & Number Properties ---
int factorial(int n);
int sumDigits(int n);
int reverseNumber(int n);
int isPalindromeNumber(int n);
int sumDivisors(int n);
int isPerfectNumber(int n);
int isArmstrong(int n);

// --- Randomization ---
int randomNumber(int min, int max);

// --- Array Utilities ---
int sumArray(int T[], int n);
float averageArray(int T[], int n);
int maxArray(int T[], int n);
int minArray(int T[], int n);
void sortAscending(int T[], int n);

// --- Matrix Operations ---
void displayMatrix(struct Matrix M);
void addMatrices(struct Matrix A, struct Matrix B, struct Matrix *C);
void multiplyMatrices(struct Matrix A, struct Matrix B, struct Matrix *C);
void transposeMatrix(struct Matrix A, struct Matrix *T);

// --- Matrix Properties & Determinants ---
int determinant2x2(int A[2][2]);
int isSymmetric(struct Matrix M);
int isIdentity(struct Matrix M);

#endif // MATH_TOOLS_H