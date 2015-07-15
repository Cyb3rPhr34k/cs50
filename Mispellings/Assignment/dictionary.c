/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// initialization
int hash_index = 0;
int word_count = 0;
node* hashtable[HT_SIZE];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int len = strlen(word);
    char tmp_word[len];
   
    // to lower all the letters 
    for (int i = 0; i < len; i++)
    {
        tmp_word[i] = tolower(word[i]);
    }
    
    // Adding a terminating character
    tmp_word[len] = '\0';
    
    // calculating the hash
    hash_index = tmp_word[0] - 'a';
    node* cursor = hashtable[hash_index];
     
    // checking
    if (cursor == NULL)
    {
        return false;
    }
    else
    {
        while (cursor != NULL)
        {
            if(!strcmp(tmp_word, cursor-> word))
            {
                return true;
            }
            cursor = cursor -> next;
        }   
    } 
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    
    // initializing the file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Error : Unable to read the dictionary file\n");
        return false;
    }
     
    // initializing the array to store the word 
    char tmp_word[LENGTH+1];
    
    // reading the file for words
    while (fscanf(dict, "%s", tmp_word) != EOF)
    {
        // allocating memory for the new node and the word
        node* new_node = malloc(sizeof(node));
        new_node -> word = malloc(sizeof(char) * strlen(tmp_word));
        
        // assigning the tmp_word to the node
        strcpy(new_node -> word, tmp_word);
        new_node -> next = NULL;
        
        word_count = word_count + 1;
        
        // calculating the hash index
        hash_index = tolower(tmp_word[0]) - 'a';
        
       // storing the word in the hash table
        if (hashtable[hash_index] == NULL)
        {  
            hashtable[hash_index] = new_node;                    
        }
        else
        {         
            node* cursor = hashtable[hash_index];
            
            while (cursor->next != NULL)
            {
                cursor = cursor->next;
            }
            
            cursor->next = new_node;                     
        } 
                  
    }
    
    fclose(dict);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    
    return word_count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < HT_SIZE; i++)
    {
        node * cursor = hashtable[i];
        
        while (cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
