// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

//Struct for nodes in linked list
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

// Prototypes
bool check(const char *word);       /* Checks if word is in dictionary
*input: pointer to a word
*output: true/false (if in or not in dictionary)
*/
bool load(const char *dictionary);  /* Loads dictionary into memory
*input: .txt file
*output: true/false (if loaded or not loaded)
*/
unsigned int size(void);            /* Finds the size of the dictionary
*input: N/A
*returns: # of words in dictionary (0 if dictionary is not loaded)
*/
bool unload(void);                  /* Unloads dictionary from memory
*input: N/A
*output: true/false (success/failed)
*/
int hashFunc(char* nextWord);       //hash function

#endif // DICTIONARY_H
