#include <stdio.h>
#include <string.h>
#include <ctype.h>

  struct Message{
      char text[200];
      int length;
};

void inputMessage(struct Message m[]){

    printf("Enter your Message :");
    fgets(m[0].text, 200, stdin);
    m[0].text[strcspn(m[0].text, "\n")] = "\0";
    m[0].length = strlen(m[0].text);	
   
}

void displayMessage(struct Message m){
     
  printf("Message : %s\n", m.text);
  printf("Length : %d\n", m.length);

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




}
 void removeSpaces(struct Message *m){



 }