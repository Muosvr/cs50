#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>


int main(int argc, string argv[]){

    //declare integer variable to index ascii character position
    int index;

    //print error for invalid number of argument
    if (argc != 2)
    {
        printf("Please run with 1 argument\n");

        return 1;
    }

    //Prompt and get string from user and store in word variable
    string word = get_string("plaintext: "); //get user input as string

    //Convert user input argument into integer and store in step
    int step = atoi(argv[1]);

    printf("ciphertext: ");

    //Loop through all characters in word
    for(int i=0; i<strlen(word); i++){

        //check if current character is in the alphabet
        if(isalpha(word[i])){

            //check if current character is upper case
            if(isupper(word[i])){

                //set index at new location in ascii table
                 index = (word[i]-65+step)%26+65;

            //check if current character is lower case
            }else if(islower(word[i])){

                //set index at new location in ascii table
                 index = (word[i]-97+step)%26+97;
            }

            //print character at the indexed ascii table location
            char c = index;
            printf("%c",c);

        }else{

            //If the current character is not in the alphabet, just print it as is
             printf("%c", word[i]);
        }
    }

    printf("\n");

    return 0;
}