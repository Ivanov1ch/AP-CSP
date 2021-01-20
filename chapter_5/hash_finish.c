#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

typedef struct _node
{
    char *word;
    struct _node *next;
} node;

node *table[MAX]; //table is global

int hash_function(char *key)
{
    int hash = toupper(key[0]) - 'A';
    return hash % MAX;
}

void print_table()
{
    // Print contents of hash table
    for (int i = 0; i < MAX; i++)
    {
        if (table[i])
        {
            printf("Index %d: ", i);
            node *current_node = table[i];
            while (current_node)
            {
                printf("%s, ", current_node->word);
                current_node = current_node->next;
            }
            printf("\n");
        }
    }
}

void insert(char *word, int i)
{
    node *new_node = malloc(sizeof(node));

    if (!new_node)
    {
        exit(-1);
    }

    new_node->word = word;
    //insert into word into hash table at index i
    // Is there anything at this index?
    if (table[i])
    {
        // Insert into linked list
        node *front = table[i];
        table[i] = new_node;
        new_node->next = front;
    }
    else
    {
        table[i] = new_node;
    }
}

int find(char *w)
{
    //return true/false or 1/0 depending on whether w was found in table

    int index = hash_function(w);

    if (table[index])
    {
        node *current_node = table[index];
        while (current_node)
        {
            if (strcmp(current_node->word, w) == 0)
            {
                return 1;
            }
            current_node = current_node->next;
        }
    }

    return 0;
}

void delete_table()
{
    for (int i = 0; i < MAX; i++)
    {
        if (table[i])
        {
            printf("Key %d: ", i);
            node *current_node = table[i];
            while (current_node)
            {
                node *next_node = current_node->next;
                free(current_node);
                current_node = next_node;
            }
            printf("\n");
        }
    }
}

int main(void)
{
    //for loop asking user to enter in words
    for (int i = 0; i < 5; i++)
    {
        // get key
        char *key = get_string("Key: ");

        int loc = hash_function(key);
        // calculate and print index
        printf("The string '%s' is mapped to index %i\n", key, loc);

        insert(key, loc);
    }
    int x = find("apple");
    int j = find("dog");
    int l = find("cat");

    print_table();

    printf("%d %d %d", x, j, l);

    delete_table();

    return 0;
}
