#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>


int main(int argc, string argv[]){
    argc = 2; //allow users to input one argument when program is run

    string word = get_string("plaintext: "); //get user input as string
    string newword = word;

    // convert input argument into integer
    // int index = atoi(argv[1]);

    for(int i=0; i<strlen(word); i++){
        if(isalpha(word[i])){
            // if(isupper(word[i])){

            // }
            newword[i]="A";
        }
    }

    // if(isalpha(word[index])){

    //       printf("First letter is in alphabet\n");

    //     }else{
    //         printf("First letter not in alphabet\n");
    //     }

    // for(int i = 0; i<strlen(word); i++){
    //     if(isalpha(word[i])){

    //     }
    // }
    // printf("The word is %s\n",word);
    printf("The argument value is %s\n", argv[2]);
    // printf("Letter A code: %i\n", 'A');
}