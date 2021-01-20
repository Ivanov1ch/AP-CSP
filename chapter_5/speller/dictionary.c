// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 500000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int key = hash(word);

    if (table[key])
    {
        node *current_node = table[key];
        while (current_node)
        {
            if (strcasecmp(current_node->word, word) == 0)
            {
                return true;
            }
            current_node = current_node->next;
        }
    }

    return false;
}

// Hashes word to a number
// Source: slightly-modified djb2 by Dan Bernstein: http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % N;
}

// Keeps track of how many words have been loaded into the hash table
int num_loaded = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Will store the read word
    char word[LENGTH + 1];

    // Read all words into word, incrementing the counter
    while (fscanf(file, "%s", word) != EOF)
    {
        // Set aside memory for the new node
        node *new_node = malloc(sizeof(node));

        // Ensure there was enough memory for this node
        if (!new_node)
        {
            return false;
        }

        // Set new_node's word
        strcpy(new_node->word, word);

        // Hash new_node and insert new_node into the linked list accordingly
        int key = hash(word);

        node *original = table[key];
        table[key] = new_node;
        new_node->next = original;

        // Increment counter
        num_loaded++;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return num_loaded;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *current_node = table[i];

        // Free current_node and all of the nodes after it
        while (current_node)
        {
            node *next_node = current_node->next;
            free(current_node);
            current_node = next_node;
        }

        // This is true when we have finished
        if (!current_node && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
