#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int digits = 0, sum = 0, z=0;
    long long number = 0, n =0;
    printf("Please enter the credit card no. : ");
    number = GetLongLong();
    n = number;
    
    while (n != 0)
    {
        n = n / 10;
        digits = digits + 1;
    }
    
    if (digits == 15)
    {
        
        
       z =(number/ pow(10,13));
       
        
        if ((z == 34) || (z == 37))
        {
       
            for(int c=100; c <pow(10,15); c=c*100)
            {
             printf("%lli",((number%c)*2));
             n = GetInt();
                if (((number%c)*2) >=10)
                {
                    
                    sum = sum + (1 + (((number%c)*2)%10));
                 
                }
                else 
                {
                 
                    sum = sum + ((number%c)*2);
               
                }
              //int x = (number%c)*2;
              //sum += x/10 + x%10;
              //345556789865345
            
            }
           for(int d=10; d <pow(10,15); d=d*100)
            {
                
               sum = sum + (number%d);
            }
            
            if((sum%10)==0)
            {
                printf("American Express\n");
            }
            else
            {
                printf("Invalid\n");
            }
        } 
        else
            {
                printf("Invalid\n");
            }  
    }
    else if (digits == 16)
    {
    z = (number/pow(10,14));
        if ((z == 51) || (z == 55))
        {
        
            for(int e=100; e <pow(10,16); e=e*100)
            {
                if (((number%e)*2) >=10)
                {
                    sum = sum + (1 + (((number%e)*2)%10));
                }
                else if (((number%e)*2) <10)
                {
                    sum = sum + ((number%e)*2);
                }
            }
            for(int f=10; f <pow(10,16); f=f*100)
            {
                sum = sum + (number%f);
            }
            
            if((sum%10)==0)
            {
                printf("MasterCard\n");
            }
            else
            {
                printf("Invalid\n");
            }
        
        }  
        else
            {
                printf("Invalid\n");
            } 
    }
    
    else
    {
    printf("Invalid");
    }   
    
    
    
    
    
    
    
    
    
}
