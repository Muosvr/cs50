#include <stdio.h>
#include <cs50.h>
int n;

int main(void)
{

   do{
    //something
        n = get_int("Please enter a number: ");

    }
    while (n<0 || n>23);

    for(int i = 0; i<n; i++){

        for (int j = n-i-1; j>0; j--){

           printf(" ");
        }
        for (int k = 0; k<2+i; k++){

            printf("#");
        }
        printf("\n");
    }
}
