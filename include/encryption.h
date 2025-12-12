#ifdef ENCRYPTION_H
#define ENCRYPTION_H

  struct Message{
      char text[200];
      int length;
};

void inputMessage(struct Message m[]);
void displayMessage(struct Message m); 
int isUppercase(char c);
int isLowercase(char c);
int isAlphabetic(char c);
void toUppercase(struct Message *m);
void toLowercase(struct Message *m); 



#endif