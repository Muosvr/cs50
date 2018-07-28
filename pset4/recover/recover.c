#include <stdio.h>
#include <string.h>



int main(int argc, char *argv[]){

    //check number of input arguments
    if (argc != 2){
        printf("Usage: recover filename\n");
        return 0;
    }

    printf("File name: %s\n", argv[1]);

    //open card file
    char *inputFileName = argv[1];
    FILE *input_file = fopen(inputFileName, "r");

    //make sure input file is not null
    if (input_file == NULL ){
        fprintf(stderr, "Could not open %s.\n", inputFileName);
        return 1;
    }

    //create buffer for reading
    unsigned char buffer[512]; // use unsigned char to map to each byte

    //declare counting variables
    int counter = 0;
    int jpegCounter = 0;
    int foundJPEG = 0;

    //test
    char *outputFileName = "test.jpeg";
    FILE *output_file = fopen(outputFileName, "w");

    //repeat until end of card
    //read 512 bytes into buffer
    while (fread(buffer,512,1,input_file)!=0){

        //counter how many buffers are recorded
        counter ++;

        //restrict max number of iteration to prevent accidental infinite loop
        if (counter > 100000){
            break;
        }

        if (jpegCounter > 1){
            break;
        }

        // printf("%s\n", buffer[1]);
        //start of a new JPEG?
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
        && (buffer[3] & 0xf0) == 0xe0){
            jpegCounter ++;

            //Alredy found a JPEG?

                //Yes -> close existing JPEG file

            //create new output file name
            // char *outputFileName = "test.jpeg";

            //open output file
            // FILE *output_file = fopen(outputFileName, "w");

            //write into new output file
            fwrite(buffer,512,1,output_file);

            //set found JPEG to be true
            foundJPEG = 1;


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

printf("%i blocks read\n", counter);
printf("This card has %i jpg pictures\n", jpegCounter);
}