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
    
    
        for (a=0; a<h; a++)
        {
            for (b=0; b < h-a; b++)
            {
                printf(" ");
            }
            for (c=0; c <= (2*a+5); c++)
            {
                if(c==(2*a+5)/2||c==(2*a+5)/2+1)
                   { printf(" ");}
                else
                printf("#");
            }
            /*for (c=0; c <= a; c++)
            {
                printf("#");
            }
            printf("  ");
            for (d=0; d<=a; d++)
            {
                printf("#");
            }*/
            
            printf("\n");
        }
    return 0;
    
}
