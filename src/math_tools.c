#include <stdio.h>
#include <stdbool.h>
int isEven(int n)
{
    int TestEven;
    printf("enter your number to check if is even:");
    scanf("%d" , &n);
    if(n%2==0)
    TestEven=1;
    else
    TestEven=0;
    return(TestEven);
}
int isPrime(int n)
{
    int i , cont;
    printf("enter your number to check if its prime:");
    scanf("%d" , &n);
    cont=0;
    for(i=2 ; i<=n ; i++)
    {
        if(n%i==0)
        cont++;
    }
    if(cont==1)
    return(1);
    else 
    return(0);
}
int gcd(int a, int b)
{
    int temp;
    printf("enter the first number to calculate the GCD:");
    scanf("%d" , &a);
    printf("enter the second number to calclate the GCD:");
    scanf("%d" , &b);
    while(b!=0)
    {
        temp=b;
        b=a%b;
        a=temp;
    }
    return a;
}