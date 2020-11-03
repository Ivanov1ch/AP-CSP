#include <stdio.h>
#include "time_struct.h"

struct Time_Struct elapsed_time(struct Time_Struct time1, struct Time_Struct time2);

int main(void)
{
    struct Time_Struct time1, time2;

    time1.hours = 9;
    time1.minutes = 44;
    time1.seconds = 03;

    time2.hours = 3;
    time2.minutes = 45;
    time2.seconds = 12;

    struct Time_Struct difference = elapsed_time(time2, time1);

    printf("Elapsed time: %02d:%02d:%02d\n", difference.hours, difference.minutes, difference.seconds);
}

struct Time_Struct elapsed_time(struct Time_Struct time1, struct Time_Struct time2)
{
    struct Time_Struct difference = {time1.hours - time2.hours, time1.minutes - time2.minutes,
                                     time1.seconds - time2.seconds};

    if (difference.hours < 0)
    {
        difference.hours *= -1;
        difference.minutes *= -1;
        difference.seconds *= -1;
    }

    if (difference.seconds < 0)
    {
        difference.seconds += 60;
        difference.minutes--;
    }

    if (difference.minutes < 0)
    {
        difference.minutes += 60;
        difference.hours--;
    }

    return difference;
}