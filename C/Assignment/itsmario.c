#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int a,b,c,h;
    h=0;
    do
    {
        printf("Please enter the height: ");
        h = GetInt(); 
    }while(h <= 0 || h >=23 );
    
    
        for (a=1; a<h+1; a++)
        {
            for (b=0; b < h-a; b++)
            {
                printf(" ");
            }  
            for (c=0; c <= a; c++)
            {
                printf("#");
            }
            printf("\n");
        }
    
    
}
