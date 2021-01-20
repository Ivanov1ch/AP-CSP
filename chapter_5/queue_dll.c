// An implementation of a queue using a doubly linked list
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct queue_node
{
    int number;
    struct queue_node *next;
    struct queue_node *previous;
} queue;

queue *head = NULL, *tail = NULL;

void enqueue(int value)
{
    queue *new_node = malloc(sizeof(queue));

    if (new_node)
    {
        new_node->number = value;
        new_node->next = NULL;
        new_node->previous = NULL;

        if (head)
        {
            tail->next = new_node;
            new_node->previous = tail;

            tail = new_node;
        }
        else
        {
            // Queue is empty, set head and tail accordingly
            head = new_node;
            tail = new_node;
        }
    }
    else
    {
        printf("Heap Overflow\n");
        exit(-1);
    }
}

int dequeue()
{
    if (!head)
    {
        return NULL;
    }
    else
    {
        queue *front_node = head;

        head = head->next;

        if (!head)
        {
            tail = NULL;
        }
        else
        {
            head->previous = NULL;
        }

        int value_to_return = front_node->number;
        free(front_node);
        return value_to_return;
    }
}

int main(void)
{
    for (int i = 0; i < 10; i++)
    {
        enqueue(i);
    }

    for (int i = 0; i < 10; i++)
    {
        printf("%d", dequeue());
    }
    return 0;
}