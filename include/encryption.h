#ifdef ENCRYPTION_H
#define ENCRYPTION_H

  struct Message{
      char text[200];
      int length;
};

void inputMessage(struct Message m[]);
void displayMessage(struct Message m); 


#endif