#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    
    string name;
    name = GetString();
    
    //Checking if the GetString() func. returned an error
    if (name != NULL)
    {
        //Printing the first initial
        printf("%c", toupper(name[0]));
    
    
    for (int i = 0, l = strlen(name); i < l; i++)
    {
        //Checking if the ith character is a space
        if (name[i] == 32)
        {
            //Printing the next initial i.e character after the space
            printf("%c", toupper(name[i+1]));
        }
        
        
    
    } 
    
    }
    

    printf("\n");
}
