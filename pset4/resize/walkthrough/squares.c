#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./squares rows columns\n");
        return 1;
    }

    int rows = atoi(argv[1]);
    int columns = atoi(argv[2]);
    int scale = atoi(argv[3]);

    for (int i=0; i < rows*scale+rows*scale%2; i++)
    {
        for (int j=0; j < columns*scale+columns*scale%2; j++){
            printf(" o ");
        }
        printf("\n");
    }
}