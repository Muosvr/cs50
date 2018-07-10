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

//check if any non alphabets in argument
for (int i=0; i<strlen(argv[1]); i++){
    if (!isalpha(argv[1][i])){
        printf("Argument cannot contrain characters outside of the alphabet\n");
        return 1;
    }
}

//get a word from user as string
string word = get_string("plaintext: ");

//convert argnument k to an array of numbers by looping through each character
int length = strlen(argv[1]);
int alphaCounter = 0;
int index;

//Begin printing ciphertext
printf("ciphertext: ");

//loop through characters in the word
for (int i=0; i<strlen(word); i++){

///if it is in alphabet, index a number from the argument string
    if(isalpha(word[i])){

        int kj = tolower(argv[1][alphaCounter%length]) - 97; //cycle kj between 0 and length of the argument

////if capital rotate based on capitalized index, then print
        if(isupper(word[i])){
            index = (word[i]-65+kj)%26+65;

////if not capital rotate based on not capitalized index, then print character
        }else if(islower(word[i])){

            index = (word[i]-97+kj)%26+97;
        }

////print character then increment to the next alphabetical character in the argument string
    char c = index;
    printf("%c", c);
    alphaCounter ++;


///if not an alphabetical character, print it unchaged
    }else{
        printf("%c",word[i]);
    }
}

//return 0 for success
printf("\n");
return 0;

}