/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize factor infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    float f = atof(argv[1]);
    
    if (f <= 0.0 || f >= 100.0)
    {
        printf("Usage : ./resize factor infile outfile\n");
        printf("Usage : factor should be between 0.0 and 100.0\n");
        return 1;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
   
    
    // initializing a new variable to keep track of both headers
    BITMAPINFOHEADER newbi = bi;
    BITMAPFILEHEADER newbf = bf;
    
    
    // changing values in the new header
    newbi.biWidth = newbi.biWidth * f;
    newbi.biHeight = newbi.biHeight * f;
   
   // new width and height
   int newWidth = newbi.biWidth;
   int newHeight = newbi.biHeight; 
    
    // determine padding for scanlines
    int newpadding =  (4 - (newWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    newbi.biSizeImage = (newWidth * sizeof(RGBTRIPLE) + newpadding) * abs(newHeight);
    newbf.bfSize = newbi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&newbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&newbi, sizeof(BITMAPINFOHEADER), 1, outptr);

   // buffer to store scanline
   RGBTRIPLE *buffer = malloc(sizeof(RGBTRIPLE) * newbi.biWidth);
    
   
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(newHeight); i < biHeight; i++)
    {
      
      int counter = 0;
      
      //iterate pixels over scanline and store it n times in the buffer
      for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // write pixel to buffer n times
            for(int k = 0; k < (int)f; k++)
            {
                *(buffer + (counter)) = triple;
                counter++;
            }
        } 
       
       
       // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // write RGB triple to outfile
        for(int l = 0; l < (int)f; l++)
           {
               fwrite(buffer, sizeof(RGBTRIPLE), newbi.biWidth, outptr);

               // write padding to outfile
               for (int m = 0; m < newpadding; m++)
               {
                   fputc(0x00, outptr);
               }
           }      
    }
     
    // free buffer
    free(buffer);    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
