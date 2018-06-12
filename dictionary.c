// Implements a dictionary's functionality

#include "dictionary.h"

//global variables
node* hashTable[676];
int wordCount=0;
bool isLoaded = false;

//functions
int hashFunc(char* nextWord);

//checks if word from file is in dictionary
bool check(const char *word)
{
    //find length of word
    int wordLength=0;
    while(*(word + wordLength) != '\0')
    {
        wordLength++;
    }

    //copy word to new array of all lower-case characters
    char newWord[wordLength + 1];
    for (int i = 0; i <= wordLength; i++)
    {
        if (*(word+i)>='A' && *(word+i)<='Z') //convert character to lower case
        {
            newWord[i] = *(word + i) + ('a' - 'A');;
        }
        else
        {
            newWord[i] = *(word + i);
        }
    }
    newWord[wordLength] = '\0'; //create a null-terminated string
    //pass word into hash function to get a hash code (int between 0 and 25)
    int hashCode = hashFunc(newWord);

    //search hash table
    node* traversalPtr = hashTable[hashCode];
    while(traversalPtr != NULL)
    {
        //compare words
        bool isFound = false;
        for (int i = 0; i <= wordLength; i++)
        {
            if (newWord[i] == traversalPtr->word[i])
            {
                if (i == wordLength)
                {
                    isFound = true;
                }
            }
            else
            {
                break;
            }
        }

        //compare words until end of list
        if(!isFound)
        {
            traversalPtr = traversalPtr->next;
        }
        else
        {
            return true;
        }
    }
    return false;
}

//loads dictionary
bool load(const char *dictionary)
{
    //set all hash table elements (pointers) to NULL
    for (int i = 0; i < 676; i++)
    {
        hashTable[i] = NULL;
    }

    //open dictionary for reading
    FILE* filePtr = fopen(dictionary, "r");
    if (!filePtr)     //error checking
    {
        printf("Unable to open dictionary.\n");
        return false;
    }

    //load dictionary into hash table
    while(1)
    {
        //create a new node for new word
        node* newNode = malloc(sizeof(node));
        if (newNode == NULL)    //error checking
        {
            printf("Unable to create a new node.\n");
            return false;
        }

        //populate newNode
        char ch;
        int counter = 0;
        while((ch=fgetc(filePtr)) != (int) 10 && ch != EOF)  //populate newNode.word[]
        {
            newNode->word[counter]=ch;
            counter++;
        }
        newNode->word[counter] = '\0';    //create a null-terminated string
        newNode->next = NULL;       //populate newNode.pointer

        if (feof(filePtr))  //if EOF is reached, free new node to avoid memory leak and break
        {
            free(newNode);
            break;
        }
        wordCount++;

        //pass word into hash function to get a hash code (int between 0 and 25)
        int hashCode = hashFunc(newNode->word);

        //populate hash table
        if(hashTable[hashCode] == NULL)
        {
            hashTable[hashCode] = newNode;
        }
        else
        {
            newNode->next = hashTable[hashCode];
            hashTable[hashCode] = newNode;
        }
    }

    //dictionary successfully loaded
    isLoaded=true;
    fclose(filePtr);
    return true;
}

//returns number of words in dictionary after loading
unsigned int size(void)
{
    if(!isLoaded)
    {
        return 0;
    }
    else
    {
        return wordCount;
    }
}

//unloads (frees) dictionary to avoid memory leak
bool unload(void)
{
    //frees linked list from each element in hash table
    for (int i = 0; i < 676; i++)
    {
        //frees each node in linked list
        node* traversalPtr = hashTable[i];
        while (traversalPtr != NULL)
        {
            node* tmp = traversalPtr;
            traversalPtr = traversalPtr->next;
            free(tmp);
        }
    }
    isLoaded = false;
    return true;
}

//hash function that groups words into 26 groups based on first character
int old_hashFunc(char* nextWord)
{
    //words starting with the same letter should return the same hash value
    if (*nextWord >= 'a' && *nextWord <= 'z')
    {
        return (int) *(nextWord)-'a';
    }
    else
    {
        return (int) *(nextWord)-'A';
    }
}

//new hash function that groups words into 676 groups, more efficient
int hashFunc(char* nextWord)
{
    //grouping on first letter
    int hashCode = 1;
    if (*nextWord >= 'a' && *nextWord <= 'z')
    {
        hashCode += (int) *(nextWord) - 'a';
    }
    else
    {
        hashCode += (int) *(nextWord) - 'A';
    }

    //grouping on second letter
    if (*(nextWord + 1) == '\0')
    {
        hashCode *= 0;
    }
    else if (*(nextWord + 1) >= 'a' && *(nextWord + 1) <= 'z')
    {
        hashCode *= (int) *(nextWord + 1) - 'a' + 1;
    }
    else
    {
        hashCode *= (int) *(nextWord + 1) - 'A' + 1;
    }
    return hashCode;
}