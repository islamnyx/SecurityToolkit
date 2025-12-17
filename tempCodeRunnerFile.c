#include <stdio.h>
#include <math.h>
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
int main()
{
    int n;
    printf("%d" ,isArmstrong(n) );
}