// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"

int main(void){
    // if (argc != 2){
    //     printf("Please enter ")
    //     return 1;
    // }

    string s = get_string("Input duration: ");
    printf("%i\n",duration(s));
    // duration(s);
    string n = get_string("Input note: ");
    printf("%s\n", is_rest(n) ? "true": "false");
    return 0;

}

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO

    int X = fraction[0]-48;
    int Y = fraction[2]-48;
    int eighths = X/(float)Y*8; //need to cast one of the integer as float for division operation to get result smaller than 1
    // printf("%i,%i,%i\n",X,Y,eighths);
    return eighths;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // TODO

    //declare int oct to count octave number away from 4
    int oct;

    //convert first character into a position index, relative to the positin to A in the order of: CDEFGAB e.g. position of B will be 1, position of D will be -4
    //n = position*2
    int position = note[0];
    if (position < 'B'){
        position = position-65;
    }else if(position > 'B'){
        position = position - 72;
    }
    printf("position: %i\n", position);
    printf("n: %i/n", n);

    //check if second character is in alphabet

    if (isalpha(note[1])){

        //if yes check if it is a '#'' or a 'b'
        if (strcmp(note[1],"#") == 0){
            //if # n = n+1
            n = n + 1;
        }else if(strcmp(note[1],"b") == 0){
            //if b: n = n-1
            n = n - 1;
        }

        printf("%c", note[1]);
    ///convert thrid character: oct = third character - 4
        oct = note[2] - 48;


    ///else if second character not in alphabet, oct = third charcter - 4
    }else{
        oct = note[1] - 48;
    }
    //n= n*2^oct calculate new n based on octave of the note
    n = n*2^oct;
    printf("oct: %i\n",oct);
    printf("n: %i/n", n);

    //frenquency = 2^(n/12)*440
    return frequency = 2^(n/12)*440;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // TODO
    // int ok = strcmp(s, "")==0;
    if (strcmp(s, "")==0){
        return true;
    }else{
        return false;
    }
}
