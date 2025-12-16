#include <stdio.h>
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
int main()
{
    int n;
    printf("%d" ,reverseNumber(n) );
}