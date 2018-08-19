// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H


#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Size of hashtabe
#define HASHTABLESIZE 1000000

// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H

//declare struct
typedef struct node
{
    char word[LENGTH +1]; //?? char word[LENGTH +1]
    struct node *next;
}
node;

//declare functions
unsigned long hash_func(const char *word);
