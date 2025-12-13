#include <stdio.h>
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

int main()
{
    int a , b;
    printf("%d" , gcd(a , b));



}