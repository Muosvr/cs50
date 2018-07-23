// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


int main(int argc, char *argv[])
{
    // ensure proper usage
    //change this line to 4 to include an addtitional argument n for scale
    //also cheack if n is between 0 and 100
    if (argc != 4 || atoi(argv[1])<0 || atoi(argv[1])> 100)
    {
        fprintf(stderr, "Usage: ./resize scale(0<scale<100) infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    //set scale variable
    int n = atoi(argv[1]);

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    //create outfile's BITMAPFILEHEADER
    BITMAPFILEHEADER bfo;
    bfo = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    //create outfile's BITMAPINFOHEADER
    BITMAPINFOHEADER bio;
    bio = bi;



    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


    //set new width of output image
    bio.biWidth = bi.biWidth*n;

    //Vertical: set new height of output image
    bio.biHeight = bi.biHeight*n;

    //calculate out file padding
    int outPadding = (4 - (bio.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //calculate outfile's BITMAPFILEHEADER biSizeImage
    bio.biSizeImage = ((sizeof(RGBTRIPLE)*bio.biWidth)+outPadding)*abs(bio.biHeight); //multiply this by n for vertical

    //Update outfile's BITMAPINFOHEADER
    bfo.bfSize = bio.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    //Write outfile's BITMAPFILEHEADER
    //modify to replace with new BITMAPFILEHEADER size x
    fwrite(&bfo, sizeof(BITMAPFILEHEADER), 1, outptr);

    //Write outfile's BITMAPINFOHEADER
    //modify to replace with new BITMAPINFOHEADER size x
    fwrite(&bio, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //Vertical: declare array type RGBTRIPLE
        RGBTRIPLE tripleRow[bio.biWidth];

        //Vertical: declare index variable for the next unassigned value in the tripleRow array
        int index = 0;

        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            //declare temp array

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            //loop this n times to scale horizontally
            //Verical: modify this to save to the type RGBTRIPLE array
            for (int k = 0; k<n; k++){
                // fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                tripleRow[index] = triple;
                index++;
            }

        }

        //Vertical: loop over n times to write type RGBTRIPLE array to file, and add padding each time
        for (int l = 0; l < n; l++)
        {
            //write each row to file from array
            fwrite(tripleRow, sizeof(RGBTRIPLE), bio.biWidth, outptr);

            // add new padding to outfile
            for (int k = 0; k < outPadding; k++)
            {
                fputc(0x00, outptr);
            }
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
