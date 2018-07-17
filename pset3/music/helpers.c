// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

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
    printf("Empty note: %s\n", is_rest(n) ? "true": "false");
    printf("%i\n",frequency(n));
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
    int n = 0;

    //convert first character into a position index,
    //relative to the positin to A in the order of: CDEFGAB e.g. position of B will be 1, position of D will be -4

    int position = note[0];

    if (position <= 66){
        position = position-65;
    }else if(position > 66){
        position = position - 72;
    }

    //n = position*2
    n = position*2;

    //Position correction: if first character is greater than B and less than F, subtract position index by 1
    if(note[0] > 'B' && note[0] < 'F'){
        n ++;
        printf("Note is between C, D, or E, adjust n by 1\n");
    }



    eprintf("position: %i\n", position);
    eprintf("n: %i\n", n);


    //check if second character is in alphabet

    if (strlen(note)==3){

        //if yes check if it is a '#'' or a 'b'
        if (note[1] == '#'){
            //if # n = n+1
            n = n + 1;
        }else if(note[1]=='b'){
            //if b: n = n-1
            n = n - 1;
        }

        eprintf("# or b: %c\n", note[1]);

        //convert thrid character: oct = third character - 4
            oct = note[2] - 48;


    ///else if second character not in alphabet, oct = third charcter - 4
    }else{
        oct = note[1] - 48;
    }

    //recalculate oct relative to octave of A4
    oct = oct-4;

    // calculate new n based on octave of the note
    n = n+oct*12;
    eprintf("oct: %i\n",oct);
    eprintf("n: %i\n", n);

    //frenquency is 2^(n/12)*440
    return pow(2,(n/(float)12))*440;
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
