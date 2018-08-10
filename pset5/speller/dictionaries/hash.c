#include <stdio.h>
#include <ctype.h>

#define HASHTABLE 10000
#define MAXSTR 46

// djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html
//experimenting codes from https://www.reddit.com/r/C_Programming/comments/2syijd/understanding_this_hash_function/
unsigned long hash_func (char* word);

int main(void)
{

    // char word[20];
    // word[0] = argv[1];
    char word[MAXSTR];

    printf("Word to hash- ");
    scanf("%s45", word);

    int index = hash_func(word);
    printf("index = %i\n", index);
}

unsigned long hash_func (char* word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        // printf("int c = %i\n", c); // only to visualize function

        hash = ((hash << 5) + hash) + tolower(c);
        // printf("hash = %lu\n\n", hash); // only to visualize function
    }
    return hash % HASHTABLE;
}