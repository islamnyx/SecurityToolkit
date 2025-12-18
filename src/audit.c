#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>



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


 int countDigits(char text[]){
  int i,length; 
  int count = 0;
  length = strlen(text);
  for (i =0 ; i < length ; i++){
     if(isdigit(text[i])){
   count++;

     }
  }


  return count;
 }


 float percentUppercase(char text[]){
    float percent;
    int count, length;
   
    if(length == 0) return 0;
    count = countUppercase(text);
    length = strlen(text);
    percent = count * 100 / length ;

  return percent;
 }


 int textlength(char text[]){
   int textlength = 0;

     while(text[textlength] != "\0"){
       textlength++;

     }
      
  return textlength;
 }

  void displayTextStats(char text[]){
     printf("%d\n",  countUppercase(text));
     printf("%d\n",  countLowercase(text));
     printf("%d\n",  countDigits(text));
     printf("%.2f\n",  percentUppercase(text));

  }


  int veryStrongPassword(char pass[]){
      int  hasUpper = 0 , hasLower = 0 , hasDigit = 0 , hasSymbol = 0 ;
      int strong , i;
      int length = strlen(pass);
      for(i = 0 ; i < length ; i++){
          if(isupper(pass[i])) hasUpper = 1;
          else if(islower(pass[i])) hasLower = 1;
          else if(isdigit(pass[i])) hasDigit = 1;
          else hasSymbol = 1;

      }
      if( hasUpper && hasLower && hasDigit  && hasSymbol  ){
        return 1;
      } else return 0;

  }

  void generateKey(int length, char key[]){
char char_set[] = "abcdefghijklmnopqrstuvwxyz!@#$^&*()-_=+[]{}<>?ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

int random,i ;
  int char_set_length = strlen(char_set);
   for(i =0 ; i < length ; i++){
      random = rand() % char_set_length;
      key[i] = char_set[random];
   }
key[length] = "\0";

printf("the Generated key is : %s", key);

//don't forget in main here u should add srand(time(NULL)); and char key[length + 1];

  }



  int isHexKey(char key[]){
    int i;
      int length = strlen(key);
      for(i = 0 ; i < length ; i++){
          if(!((key[i] >= '0' && key[i] <= '9')   (key[i] >= 'a' && key[i] <= 'f') (key[i] >= 'A' && key[i] <= 'F'))) return 1;
          return 0;

      }

        return 1;

  }


  void generateRandomPassword(int length, char pass[]){
char char_set[] = "abcdefghijklmnopqrstuvwxyz!@#$^&*()-_=+[]{}<>?ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
   int random,i ;
  int char_set_length = strlen(char_set);
   for(i =0 ; i < length ; i++){
      random = rand() % char_set_length;
      pass[i] = char_set[random];
   }
pass[length] = "\0";

printf("the Generated Password is : %s", pass);

//don't forget in main here u should add srand(time(NULL)); and char key[length + 1];




  }

void 