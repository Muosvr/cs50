#include <stdio.h>
#include <cs50.h>
#include <math.h>
int n;

int main(void) {

    do{
        n = round(get_float("Please enter amount of change: ")*100);//get a float from user input, multiply by 100,  then round to integer

        int quarter = (n-n%25)/25; //calculate the amount of quarter needed
        int dime = (n%25-n%25%10)/10; //calculate the amount of dime needed
        int nickle = (n%25%10 - n%25%10%5)/5; //...nickle needed
        int cents = (n%25%10%5); //...cents
        int total = quarter+dime+nickle+cents;//calculate total

        printf("%i\n",total);
    }
    while(n<0);
}