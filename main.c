#include "stdio.h"
#include "encryption.h"
#include "math_tools.h"
#include "user.h"
#include "audit.h"
#include "logs.h"

int main(){
     int choice;
    do {

 printf("1. Encryption\n2. Math Tools\n3. User Management\n4. Security Audit\n5. Log Management\n6. Help\n7. About\n0. Exit\nChoice: ");
 scanf("%d", &choice);
   switch(choice){
    case 1: encryptionMenu();break;
    case 2: mathMenu();      break;
    case 3: userMenu();      break;
    case 4: auditMenu();     break;
    case 5: logsMenu();      break;
    case 6: helpMenu();      break;   
    case 7: aboutMenu();     break;
    default: printf("Invalid choice! Please try again. \n");
   }
} while(choice != 0);
    return 0;
}
