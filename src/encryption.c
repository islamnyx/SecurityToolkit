#include <stdio.h>
#include <string.h>
#include <ctype.h>

  struct Message{
      char text[200];
      int length;
};

void inputMessage(struct Message *m){

    printf("Enter your Message :");
    fgets(m->text, 200, stdin);
    m->text[strcspn(m->text, "\n")] = '\0';
    m->length = strlen(m->text);  
   
}

void displayMessage(struct Message *m){
     
  printf("Message : %s\n", m->text);
  printf("Length : %d\n", m->length);

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


  void encryptXOR(struct Message *m , char key[]){
      int i;
      int keyLength = strlen(key);
    for(i = 0 ; i < m->length ; i++){
      m->text[i] = m->text[i] ^ key[i % keyLength];
    }

  }


  void decryptXOR(struct Message *m , char key[]){
      int i;
     int keyLength = strlen(key);
    for(i = 0 ; i < m->length ; i++){
      m->text[i] = m->text[i] ^ key[i % keyLength]; //cuz the key here is periodic 
    }

  }