#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

// argc = no. of command line inputs, argv[] = string array which stores the command line 
int main (int argc, string argv[])
{
    //Check if the command line arguments are not 2
    if (argc != 2)
    {
        printf("Wrong Input\n");
        return 1;
    }
    
    //Converting key from string to int
    int key = atoi(argv[1]);
    
    //Takes the plain text message from the user
    printf("Please enter the message.\n");
    string m = GetString();
 
    key = key % 26;
    int mkshft = 0;
    
    if (m != NULL)
    {
        //Calculate the length of the plain text message
        int l = strlen(m);
        char c[l];
        for (int i = 0 ; i < l; i++)
        {
           //Check if the ith alphabet is a lowercase
           if ( islower(m[i])) 
           {
                //shift the ith character 
                mkshft = m[i] + key;
                
                //Starting from a if c crosses z
                if (mkshft > 122)
                 {
                     mkshft = mkshft - 26;
                  }
                 c[i] = mkshft;
           }
           else
            if( isupper(m[i]))
            {
                mkshft = m[i] + key;
                if (mkshft > 90)
                 {
                     mkshft = mkshft - 26;
                 }
                 c[i] = mkshft;   
            
            }
            else
            {
                mkshft = m[i];
                c[i] = mkshft;
            }
             
             printf("%c",c[i]);
        }
    }
    printf("\n");
    return 0;
    }

    
    
    
