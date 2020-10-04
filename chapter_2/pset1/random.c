#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    for(int i = 0; i < 5; i++)
    {
        int x = rand() % 6 + 1;
        printf("%d\n", x);
    }
}