#include <stdio.h>
#include <cs50.h>

int main (void)
{
    printf("%0.50f",0.01);
    float o = 0;
    int d = 0,p = 0,tot = 0,coins = 0,c25 = 0,c10 = 0,c5 = 0,c1 = 0;
    
    while (o <= 0)
    {
    printf("how much do i owe you : ");
    o = GetFloat();
    }
    d = o;
    p = (o-d)*100;
    tot = (d * 100) + p;
    
    while (tot > 0)
    {
        if (tot >= 25)
        {
            c25 = c25 + 1;
            tot = tot - 25;
        }
        else
            if(tot >=10)
            {
                c10 = c10 + 1;
                tot = tot - 10;
            }
            else
                if(tot >= 5)
                {
                    c5 = c5 + 1;
                    tot = tot - 5;
                }
                else
                {
                     c1 = c1 + 1;
                     tot = tot - 1;    
                }
     }
 
 coins = c25 + c10 + c5 + c1;
 printf ("%i\n",coins);   
   

}
