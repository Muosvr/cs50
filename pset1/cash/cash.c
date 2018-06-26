#include <stdio.h>
#include <cs50.h>
#include <math.h>
int n;

int main(void) {

    do{
        n = round(get_float("Please enter amount of change: ")*100);

        int quarter = (n-n%25)/25;
        int dime = (n%25-n%25%10)/10;
        int nickle = (n%25%10 - n%25%10%5)/5;
        int cents = (n%25%10%5);
        int total = quarter+dime+nickle+cents;

        printf("%i\n",total);
    }
    while(n<0);
}