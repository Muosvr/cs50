#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

int main(int numOfArguments, string argValues[])
{
    if(numOfArguments == 2)
    {
        char* file = argValues[1]; //create a pointer for the file name string named file
        FILE* card = fopen(file,"r"); //read the file

        if(!card) //check if file exist
        {
            printf("No file or nothing in file.\n");
            return 1;
        }
        //define buffer
        unsigned char buffer[512];

        //keep count
        int imgcount = 0;

        while(fread(buffer, 512, 1, card) == 1)
        {
            if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            //if this a jpg
            {
                imgcount++;
            }
        }

        printf("Total number of jpeg files: %i\n", imgcount);
        fclose(card);
        return 0;
    }
    else
    {
        printf("Usage: ./getjepg filename\n");
    }

}
