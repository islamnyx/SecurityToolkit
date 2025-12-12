#include <stdio.h>
#include <string.h>
#include <ctype.h>





int countUppercase(char text[]){
  int count = 0;
  int length,i;
  length = strlen(text);
    for(i = 0 ; i < length ; i++){
     if(isupper(text[i])) count++;

    }


  return count;
}

int countLowercase(char text[]){
  int count = 0;
  int length,i;
  length = strlen(text);
    for(i = 0 ; i < length ; i++){
     if(islower(text[i])) count++;
    }
  return count;
}


