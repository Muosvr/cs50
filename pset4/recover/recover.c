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
    char *file_name = argv[1];
    FILE *input_file = fopen(file_name, "r");

    //make sure input file is not null

    //create buffer for reading
    unsigned char buffer[512];

    //declare counting variables
    int counter = 0;
    int jpgCounter = 0;

    //repeat until end of card
    //read 512 bytes into buffer
    while (fread(buffer,512,1,input_file)!=0){

    //counter how many buffers are recorded
    counter ++;

    //restrict max number of iteration to prevent accidental infinite loop
    if (counter > 100000){
        break;
    }

    // printf("%s\n", buffer[1]);
    //start of a new JPEG?
    if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
    && (buffer[3] & 0xf0) == 0xe0){
        jpgCounter ++;
    }

//yes

//no

//already found a JPEG?

//no

//yes
    }

//close any remaining files

printf("%i blocks read\n", counter);
printf("This card has %i jpg pictures\n", jpgCounter);
}