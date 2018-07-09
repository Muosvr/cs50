#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//main function with arguement parameter k as string

int main (int argc, string argv[]){

//if number of argument is not one, print error and return 1

if (argc != 2){
    printf("Please run program with one argument\n");
    return 1;
}

//get a word from user as string
string word = get_string("plaintext: ");

//convert argnument k to an array of numbers by looping through each character(to be refactored)
int length = strlen(argv[1]);
int k = tolower(argv[1][0]);
k = k - 97;
printf("First character is: %i\n", k);
printf("length of arguement: %i\n", length);

int alphaCounter = 0;
int index = 0;
//loop through characters in the word
for (int i=0; i<strlen(word); i++){

    printf("%c\n",word[i]);
///if it is in alphabet, index a number from the argument array of numbers
    if(isalpha(word[i])){

        int kj = argv[1][alphaCounter%length];
        printf ("%i\n", kj);
////if capital rotate based on capitalized index, then print

////if not capital rotate based on not capitalized index, then print character

////index to the next number in the argument array using modulo
    alphaCounter ++;


///else print unchaged character
    }else{
        printf("%c",word[i]);
    }
}

//return 0
printf("\n");
return 0;

}