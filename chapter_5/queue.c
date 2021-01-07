#include <stdio.h>
#define CAPACITY 10

typedef struct
{
    int front;
    int numbers[CAPACITY];
    int size;
} queue;

void enqueue(queue *to_add, int value)
{
    if (to_add->size < CAPACITY)
    {
        to_add->numbers[(to_add->front + to_add->size) % CAPACITY] = value;
        to_add->size++;
    }
}

int dequeue(queue *to_remove_from)
{
    if (to_remove_from->size > 0)
    {
        int dequeued_value = to_remove_from->numbers[to_remove_from->front];
        to_remove_from->front = (to_remove_from->front + 1) % CAPACITY;
        to_remove_from->size--;
        return dequeued_value;
    }

    return 0;
}

int main(void)
{
    queue queue1;
    queue1.front = 0;
    queue1.size = 0;

    for(int i = 1; i <= 10; i++)
    {
        enqueue(&queue1, i);
    }

    for(int i = 1; i <= 5; i++)
    {
        printf("%d\n", dequeue(&queue1));
    }
}