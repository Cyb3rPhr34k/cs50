#include <stdio.h>
#include <cs50.h>

int main(void)
{
    float a = 0;
    long b = 0;
    int c = 0;
    printf("Enter the credit card no. : ");
    b = GetLongLong();
    a = b / 10;
    if ( a > 0)
    c = a;
    printf("%i,%f",c, a);

}
