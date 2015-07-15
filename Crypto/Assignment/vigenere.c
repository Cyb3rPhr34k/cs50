#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main ( int argc, string argv[])
{
    //Condition to check if more than two arguments are input
    if (argc != 2)
    {
        printf("Wrong Input\n");
        return 1;
    }
    
    //Storing the provided key as a string in k
    string k = argv[1];
    
    //Determining the length of key
    int keylen = strlen(k);
    
    //Asking the user to enter the plaintext message
    printf("Please enter the message. \n");
    string m = GetString();
    
    if (m != NULL)
    {
        int l = strlen(m);
        char key_text[l]; 
        int key[l];
        char c[l];
        int mkshft = 0;
        
        //Coverting each character in the key to an integer value
        for( int i = 0; i < l; i++)
        {
            key_text[i] = k[i%keylen];
            
            if (isupper(key_text[i]))
            {
                key[i] = key_text[i] - 'A';
            }
            else
                if (islower(key_text[i]))
                {
                    key[i] = key_text[i] - 'a';
                }
             
                
                
        }
        
        //Loop to encrypt each character in a message
        for ( int j = 0, z = 0; j < l; j++)
        {
            if (islower(m[j]))
            {
            
                mkshft = m[j] + key[z];
                
                if (mkshft > 122)
                 {
                     mkshft = mkshft - 26;
                  }
                 
                 c[j] = mkshft;
                 z++;
            
            }
            else if (isupper(m[j]))
            {
                mkshft = m[j] + key[z];
                
                
                
                if (mkshft > 90)
                {
                    
                     mkshft = mkshft - 26;
                    
                       
                }
                c[j] = mkshft; 
                z++;
            }
            else
            {
                mkshft = m[j];
                c[j] = mkshft;
            }
             
             printf("%c",c[j]);
        
        
        }
            
     }
        
         
        
    
    printf("\n");
    return 0;
}


 
