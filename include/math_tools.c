#include <stdio.h>
#include <stdbool.h>
#include <math.h>
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
int factorial(int n)
{
    int fact , i;
    printf("enter your number to compute factorial:");
    scanf("%d" , &n);
    fact=n;
    for(i=n-1 ; i>=1 ; i--)
    {
        fact=fact*i;
    }
    return fact;

}
int sumDigits(int n)
{
    int sum , digit; 
    printf("enter your number:");
    scanf("%d" , &n);
    sum=0;
    while(n>0)
    {
        digit=n%10;
        sum=sum+digit;
        n=n/10;
    }
    return sum;
}
int reverseNumber(int n)
{
    int digit , sum;
    printf("enter your number to reverse it:");
    scanf("%d" , &n);
    sum=0;
    while(n>0)
    {
        digit=n%10;
        sum=sum*10+digit;
        n=n/10;
    }
    return sum;
}
int isPalindromeNumber(int n)
{
    int digit,rev,pali,save;
    printf("enter your number to check if its palindrome:");
    scanf("%d" , &n);
    if(n<0)
    {
        n=-n;
    }
    rev=0;
    save=n;
    while(save>0)
    {
        digit=save%10;
        rev=rev*10+digit;
        save=save/10;
    }
    if(n==rev)
    pali=1;
    else 
    pali=0;
    return pali;
}
int sumDivisors(int n)
{
    int i,sum;
    printf("enter your number to caclulate the sum of its divisors:");
    scanf("%d" , &n);
    if(n<0)
    n=-n;
    sum=0;
    for(i=1 ; i<=n/2 ; i++)
    {
        if(n%i==0)
        sum=sum+i;
    }
    return sum;
}
int isPerfectNumber(int n)
{
    int i,sumdiv,perfectnum;
    printf("enter your positive number to check if its perfect:");
    scanf("%d" , &n);
    sumdiv=0;
    for(i=1 ; i<=n/2 ; i++)
    {
        if(n%i==0)
        sumdiv=sumdiv+i;
    }
    if(n==sumdiv)
    perfectnum=1;
    else 
    perfectnum=0;
    if(n==0)
    perfectnum=0;
    return perfectnum;
}
int isArmstrong(int n)
{
    int save,numdigits,sum,arms,digit;
    printf("enter ur number to check if its armstrong number:");
    scanf("%d" , &n);
    if(n<0)
    n=-n;
    save=n;
    numdigits=0;
    while(save>0)
    {
        save=save/10;
        numdigits++;    
    }
    save=n;
    sum=0;
    while(save>0)
    {
        digit=save%10;
        sum=sum+pow(digit , numdigits);
        save=save/10;
    }
    if(sum==n)
    arms=1;
    else 
    arms=0;
    if(n==0)
    arms=0;
    return arms;
}
