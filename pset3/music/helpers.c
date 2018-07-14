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

    string s = get_string("Input: ");
    printf("%i\n",duration(s));
    // duration(s);
    string n = get_string("Input2: ");
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
// int frequency(string note)
// {
//     // TODO
// }

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
