//Question: what is the right way to develop in an enviroment where I cannot make the individual c file?
//char word[LENGTH +1] ?? what is LENGTH?
//Why I cannot access the properties in struct with . like in whodunit, but instead have to use the arrow notation here?

// Implements a dictionary's functionality
#include <stdbool.h>
// #include "dictionary.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define HASHTABLESIZE 10000

//for testing
#include <stdio.h>

typedef struct node
{
    char word[46]; //?? char word[LENGTH +1]
    struct node *next;
}
node;

//declare variable
 node *hashtable[HASHTABLESIZE] = {NULL};



// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //TODO
    //word to lowercase
    char copy[46];

    // printf("Test\n");
    for (int i = 0; i < 10; i++)
    {
        copy[i]=tolower(word[i]);

    }
    printf("Tolower: %s\n", copy);

    //traverse hash table
    // int index = hash_func(copy);
    // node* curosr =

    // use hash function to calculate index for word
    // look up word index from hash table array
    //if index found
        // look up word following linked list in hash table
        //use strcmp to check each word in linked list, return true if strcmp result in 0
//return 0;

    return false;
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

    return hash % HASHTABLESIZE;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    // create a mock hash table for testing

        FILE *dictionaryFile = fopen(dictionary,"r");

        //check if file exist
        if(dictionaryFile == NULL)
        {
            printf("Dictionary does not exist\n");
            return false;
        }
        // hashtable[0] = NULL; //head
        // free(head);

        char word[46];
        // printf("Input 5 wrods: ");
        while (fscanf(dictionaryFile,"%s",word)!=EOF){

            // scanf("%s45", word);
            int index = hash_func(word);
            printf("Word: %s, Hash #: %d\n", word, index);

            node *newNode = malloc(sizeof(node));
            strcpy(newNode -> word, word);
            newNode->next = hashtable[index];
            hashtable[index] = newNode;
        }

        // char *target = node1 -> word;

        // node *cursor = hashtable[2488];

        // while(cursor != NULL){
            // printf("Cursor: %s\n", cursor->word);
        //     cursor = cursor->next;

        // }
        // char *target = hashtable[0]->next->word;
        // printf("Target: %s\n", target);
        // printf("Cursor: %s\n", cursor->word);
        // return hashtable;

    //open dictionary file
    //malloc memory for hash table array (size of table)
    //loop through each word in the file till end of file
    //read each word into memory
        //use hash function to calculate index for word
        //malloc memory for new node
        //check if malloc succeeded
        //check hash table array if index exist
            //if yes, add node to the linked list
            //if no, add to the hash table start a new linked list ??
    //return true if the above succeeds
    printf("Dictionary: %s\n", dictionary);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    //open dictionary file, file name ??
    //loop through and count each word until end of file
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    //loop through hash table array
        //loop through from end of linked list to the head
            //free each node from memory
    //free memory from hash table array


    return false;
}

int main(void){
    char word[46];
    char dictionary[46];

    printf("Word: ");
    scanf("%s45", word);
    printf("Dictionary: ");
    scanf("%s45", dictionary);
    printf("You typed: %s\n", word);

    check(word);
    load(dictionary);
}
