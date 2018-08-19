// Implements a dictionary's functionality
#include "dictionary.h"


//declare variable
 node *hashtable[HASHTABLESIZE] = {NULL};
 unsigned int wordCount = 0;


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //TODO
    //word to lowercase
    char copy[LENGTH+1]="";

    // printf("Test\n");
    for (int i = 0; i < strlen(word); i++)
    {
        copy[i]=tolower(word[i]);

    }

     // use hash function to calculate index for word
    int index = hash_func(copy);

    // look up word index from hash table array
    node *cursor = hashtable[index];

    //traverse hash table
    while(cursor != NULL){
        // printf("Cursor: %s\n", cursor->word);

        // look up word following linked list in hash table
        //use strcmp to check each word in linked list, return true if strcmp result in 0
        if (strcmp(cursor->word,copy)!= 0)
        {
            cursor = cursor->next;
        }
        else
        {
            // printf("Word found\n");
            return true;
        }
    }
    // printf("Word not found\n");
    return false;
}

unsigned long hash_func (const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c);

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
            return false;
        }

        char word[LENGTH+1];

        while (fscanf(dictionaryFile,"%s",word)!=EOF){

            int index = hash_func(word);

            node *newNode = malloc(sizeof(node));
            strcpy(newNode -> word, word);
            newNode->next = hashtable[index];
            hashtable[index] = newNode;
            wordCount++;
        }
        fclose(dictionaryFile);


    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    //loop through hash table array
    for(int i=0; i<HASHTABLESIZE; i++)
    {
        //loop through linked list
        node *cursor = hashtable[i];

        //free each node from memory
        while(cursor != NULL){
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}

