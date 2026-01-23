#include <stdio.h>
#include <string.h>
#include <ctype.h>

  struct Message{
      char text[200];
      int length;
};

// --- I/O and Basic Manipulation ---

void inputMessage(struct Message *m) {
    printf("Enter your text: ");
    scanf(" %[^\n]s", m->text);
    m->length = strlen(m->text);
    while(getchar() != '\n'); // Clear buffer
}

void displayMessage(struct Message *m) {
    printf("Current Message: [");
    for(int i = 0; i < m->length; i++) {
        if (isprint((unsigned char)m->text[i])) {
            printf("%c", m->text[i]);
        } else {
            printf("."); // Keep the UI clean if the message is encrypted
        }
    }
    printf("]\n");
}

int isUppercase(char c){
  if(c >= 'A' && c <= 'Z' ) return 1;
  else return 0;

}

int isLowercase(char c){
  if(c >= 'a' && c <= 'z') return 1;
  else return 0;

}

int isAlphabetic(char c){
  if((c >= 'A' && c <= 'Z' ) || (c >= 'a' && c <= 'z')) return 1;
  else return 0;

}

void toUppercase(struct Message *m){
 int i;
  for(i = 0 ; i < m->length ; i++){
  m->text[i] = toupper(m->text[i]);

  }

}

void toLowercase(struct Message *m){
 int i;
  for(i = 0 ; i < m->length ; i++){
  m->text[i] = tolower(m->text[i]);

  }

}

void reverseMessage(struct Message *m){
   int i,j;
   char temp;
   i = 0;
   j = m->length -1 ;
  while( i < j ){
     temp = m->text[i];
      m->text[i] = m->text[j];
        m->text[j] = temp;
        i++;
        j--;
  }

}


 void removeSpaces(struct Message *m){
  int i,j = 0;
  for(i = 0 ; i < m->length ; i++){
     if(m->text[i] != ' '){
       m->text[j] = m->text[i];
       j++ ;
    }
     
  }
   m->text[j] = '\0';
   m->length = j;

 }



  void encryptCeaser(struct Message *m, int key) {
    int i;
    key = key % 26;

    for (i = 0; m->text[i] != '\0'; i++) {
        if (m->text[i] >= 'A' && m->text[i] <= 'Z') {
              m->text[i] = (m->text[i] - 'A' + key) % 26 + 'A';
        }
        else if (m->text[i] >= 'a' && m->text[i] <= 'z') {
             m->text[i] = (m->text[i] - 'a' + key) % 26 + 'a';
        }
    }
    //(c - base + key) % 26 + base

}


  void decryptCeaser(struct Message *m , int key){
     int i;
     key = key % 26;

    for (i = 0; m->text[i] != '\0'; i++) {
        if (m->text[i] >= 'A' && m->text[i] <= 'Z') {
               m->text[i] = (m->text[i] - 'A' - key +  26 ) % 26 + 'A';
        }
        else if (m->text[i] >= 'a' && m->text[i] <= 'z') {
              m->text[i] = (m->text[i] - 'a' - key + 26) % 26 + 'a';
        }
        
    }
    //(c - base - key + 26) % 26 + base


  }


void encryptXOR(struct Message *m, char key[]) {
    int keyLength = (int)strlen(key);
    if (keyLength == 0) return;

    // Use actual strlen if m->length is corrupted
    int msgLen = (int)strlen(m->text); 
    
    for (int i = 0; i < msgLen; i++) {
        m->text[i] = m->text[i] ^ key[i % keyLength];
    }
    m->length = msgLen; // Re-sync the struct length
}


  void decryptXOR(struct Message *m , char key[]){
      int i;
     int keyLength = strlen(key);
    for(i = 0 ; i < m->length ; i++){
      m->text[i] = m->text[i] ^ key[i % keyLength]; //cuz the key here is periodic 
    }

  }




  void encryptSubstitution(struct Message *m , char key[26]){
     int i, numL , numU;
    for(i = 0 ; i < m->length ; i++){
      if(isAlphabetic(m->text[i])){
        if(isLowercase(m->text[i])){
          numL = m->text[i] - 'a';
          m->text[i] = tolower(key[numL]);
        }
        else if(isUppercase(m->text[i])){
          numU = m->text[i] - 'A';
          m->text[i] = toupper(key[numU]);
        }


      }


    }
 
  }

  void  decryptSubstitution(struct Message *m, char key[26]){
    int i,j;
   for(i = 0 ; i < m->length ; i++){
    if(isAlphabetic(m->text[i])){
     for(j = 0 ; j < 26 ; j++){
      if(toupper(m->text[i]) == key[j] ){
        if(isLowercase(m->text[i])) 
        m->text[i] = 'a' + j;
        else 
        m->text[i] = 'A' + j;
        break;
      } 

     }

    }
   }

  }

 int isValidKey(char key[26]){
  int i, index;
  int repeat[26] = {0};
   if(strlen(key) != 26 ) return 0;
   
   for(i =0 ; i < 26 ; i++){
    if(!isAlphabetic(key[i])) return 0;
     index = toupper(key[i]) - 'A';
    if(repeat[index]) return 0;

    repeat[index] = 1;
   }

    return 1;
 }

int compareMessages(struct Message m1, struct Message m2){
   int i;
   if(m1.length != m2.length) return 0;
   int flag = 0;
   for(i = 0 ; i < m1.length ; i++){
     if(m1.text[i] != m2.text[i]) return 0;
   }
  
  return 1;
}


int countCharacter(struct Message m, char c) {
    int count = 0;
    for (int i = 0; i < m.length; i++) {
        // Use toupper to make sure 'A' matches 'a'
        if (toupper(m.text[i]) == toupper(c)) {
            count++;
        }
    }
    return count;
}


void frequencyAnalysis(struct Message m){
 int freq[26] = {0};
 int i, index;
  for(i = 0 ; i < m.length ; i++){
    if(isAlphabetic(m.text[i])){
      index = toupper(m.text[i]) - 'A';
       freq[index]++;
    }
  }
  
  for(i = 0; i < 26; i++){
        printf("%c: %d\n", 'A' + i, freq[i]);
    }
}


float coincidenceIndex(struct Message m) { 
    int i, index;
    int sum = 0;
    int repeat[26] = {0};

    // 1. Calculate the numerator: Sum of f * (f - 1)
    for(i = 0; i < m.length; i++) {
        if(isalpha(m.text[i])) { // Use standard isalpha
            index = toupper(m.text[i]) - 'A';
            if(!repeat[index]) {
                repeat[index] = 1;
                // Count how many times this specific letter appears
                int count = countCharacter(m, m.text[i]); 
                sum += count * (count - 1);
            }
        }
    }
    
    // 2. Handle the denominator
    // If length is 10, totalPairs is 10 * 9 = 90
    int totalPairs = m.length * (m.length - 1);

    if (totalPairs <= 0) return 0.0;

    // 3. THE FIX: Cast to (float) so it doesn't return 0 or the denominator
    // If sum is 2 and totalPairs is 90, result is 0.0222
    return (float)sum / (float)totalPairs;
}