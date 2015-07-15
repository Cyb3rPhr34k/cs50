/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdint.h>
 
// BYTE typedef equal to unsigned integer 8-bits in length.
typedef uint8_t BYTE;

 
 // constant for block size
 #define BLOCK 512

int main(int argc, char* argv[])
{
   // ensure proper usage 
   if (argc != 2)
   {
        printf("Usage : ./recover [filename]");
        return 1;
   }
   
   // remember filename
   char* infile = argv[1];
   
   // open input file
   FILE* inptr = fopen(infile, "r");
   if (inptr == NULL)
   {
        printf("Error : Could not open %s.\n", infile);
        return 1;
   }
   
   // temp outptr
   FILE* outptr = NULL;
   
   // buffer to store 512 bytes
   BYTE buffer[BLOCK];
   
   // image counter
   int img_counter = 0;
   
   
     
   // read from input file
   while (fread(buffer, BLOCK * sizeof(BYTE) , 1, inptr))
   {
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] == 0xe0) || (buffer[3] == 0xe1)))         
        {
        
            if (outptr != NULL)
            {
               
                fclose(outptr);
            }
            
            // create a new jpg file
            char* filename = malloc(sizeof(int) * 2);
            sprintf(filename, "%03d.jpg", img_counter);
            img_counter++;
            printf("%s\n", filename);
            
            // opening the ouput file
            
            outptr = fopen(filename, "w");
            if (outptr == NULL)
            {
                printf("Error : unable to open output file");
                return 1;
            }
            
            fwrite(buffer, BLOCK * sizeof(BYTE), 1, outptr);
            
        
        }   
        else if (outptr != NULL)
        {
            fwrite(buffer, BLOCK * sizeof(BYTE), 1, outptr);
        }
        
       
   }
   fclose(inptr);
   
   
}     
