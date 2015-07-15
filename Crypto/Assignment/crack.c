#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define _XOPEN_SOURCE

//prototype
char *crypt(const char *key, const char *salt);

int main (int argc, string argv[])
{
    //Error if the user input more than 2 command line arguments
    if (argc != 2 )
    {
        printf("Mayday, Mayday, Mayday, Wrong input, I repeat Wrong input. \n");
        return 1;       
    }
    else
    {
        //Storing the encrypted password in a variable
        string encrypted_pass = argv[1];
        
        // Initializing File and key
        FILE *pass_file;
        char key[8];
        
        //Opening the dictionary file
        pass_file = fopen("/home/jharvard/CS50/pset2/pass.txt","r");
        
        //Checking if the program is able to read the file or not
        if (pass_file == NULL)
        {
            printf("Couldn't read the dictionary file, please try again later. \n");
            return 1;
        }
        
        //Reading the words in the file untill EOF
        while (fgets(key, 128, pass_file) != NULL)
        {
            //Storing the password in key
            fscanf(pass_file, "%s", key);
        
            //Initializing the salt value
            char salt[2];
        
            //Storing the Salt value in a variable
            for (int i = 0; i < 2; i++)
            {
                salt[i] = encrypted_pass[i];
            }
        
            //Storing the encrypted key in a variable
             string pwd_enc = crypt(key, salt);
             
             //Comparing the encrypted key with the given hash  
             int diff = strncmp(pwd_enc, encrypted_pass, 13);
             
             //Printing the password if a match is found
             if(diff == 0)
             {
                printf("%s\n", key );
                return 0;
             }
        
            
        
        } 
        
        //Closing the dictionary file 
        fclose(pass_file);
     }


}
