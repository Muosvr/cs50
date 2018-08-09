// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    //word to lowercase
    // use hash function to calculate index for word
    // look up word index from hash table array
    //if index found
        // look up word following linked list in hash table
        //use strcmp to check each word in linked list, return true if strcmp result in 0

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    //open dictionary file
    //melloc memory for hash table array
    //loop through each word in the file till end of file ??
    //read each word into memory
        //word to lowercase ?
        //use hash function to calculate index for word
        //check hash table array if index exist
            //if yes, find head of linked list


    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
