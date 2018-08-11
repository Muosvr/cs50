#include <stdio.h>
#include <string.h>



int main(int argc, char *argv[]){

    //check number of input arguments
    if (argc != 2){
        printf("Usage: recover filename\n");
        return 1;
    }

    printf("File name: %s\n", argv[1]);

    //open card file
    char *inputFileName = argv[1];
    FILE *input_file = fopen(inputFileName, "r");

    //make sure input file is not null
    if (input_file == NULL){
        fprintf(stderr, "Could not open %s.\n", inputFileName);
        return 1;
    }

    //create buffer for reading
    unsigned char buffer[512]; // use unsigned char to map to each byte

    //declare variables
    int counter = 0;
    int jpegCounter = 0;//so the image file namges starts with 0
    int foundJPEG = 0;
    // int a=0, b=0, c=0;
    char outputNameBuffer[8]; //check

    //create an output file
    // sprintf(outputNameBuffer,"%03d.jpg",jpegCounter);
    // FILE *output_file = fopen(outputNameBuffer, "w");
    FILE *output_file = NULL;

    //repeat until end of card
    //read 512 bytes into buffer
    while (fread(buffer,512,1,input_file)!=0){

        //counter how many buffers are recorded
        counter ++;

        //restrict max number of iteration to prevent accidental infinite loop


        //start of a new JPEG?
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
        && (buffer[3] & 0xf0) == 0xe0){

            //Alredy found a JPEG?
            if(foundJPEG == 1){
                fclose(output_file);

                //specify outputfile naming convention
                // a = jpegCounter%10;
                // b = jpegCounter%100/10;
                // c = jpegCounter%1000/100;
                sprintf(outputNameBuffer,"%03d.jpg",jpegCounter++);

                //create file under new name after ever new jpeg found
                output_file = fopen(outputNameBuffer, "w");
            }else{
                sprintf(outputNameBuffer,"%03d.jpg",jpegCounter++);
                output_file = fopen(outputNameBuffer, "w");
            }

            //write into new output file
            fwrite(buffer,512,1,output_file);

            //set found JPEG to be true
            foundJPEG = 1;

        //if not the start of a JPEG
        }else{

            //already found a JPEG?
            if (foundJPEG == 1){

                //Yes -> write buffer into existing output file
                fwrite(buffer,512,1,output_file);
            }
        }
    }

//close any remaining files
fclose(output_file);

//output to confirm reading of blocks and counted images
printf("%i blocks read\n", counter);
printf("This card has %i jpg pictures\n", jpegCounter);
return 0;
}