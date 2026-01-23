#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * Structure to hold message data and its metadata.
 */
struct Message {
    char text[200];
    int length;
};

/**
 * I/O and Basic Manipulation
 */
void inputMessage(struct Message *m);
void displayMessage(struct Message *m);
void toUppercase(struct Message *m);
void toLowercase(struct Message *m);
void reverseMessage(struct Message *m);
void removeSpaces(struct Message *m);

/**
 * Character Classification (Boolean Logic)
 */
int isUppercase(char c);
int isLowercase(char c);
int isAlphabetic(char c);

/**
 * Cryptographic Algorithms
 */
// Caesar Cipher
void encryptCeaser(struct Message *m, int key);
void decryptCeaser(struct Message *m, int key);

// XOR Cipher
void encryptXOR(struct Message *m, char key[]);
void decryptXOR(struct Message *m, char key[]);

// Substitution Cipher
void encryptSubstitution(struct Message *m, char key[26]);
void decryptSubstitution(struct Message *m, char key[26]);
int isValidKey(char key[26]); // Validates that the key contains 26 unique letters

/**
 * Cryptanalysis and Comparison
 */
int compareMessages(struct Message m1, struct Message m2);
int countCharacter(struct Message m, char c);
void frequencyAnalysis(struct Message m);
int coincidenceIndex(struct Message m);

#endif // ENCRYPTION_H