#include <cs50.h>
#include <stdio.h>


int main(void)
{
    // Get input + calculate conversion
    float celsius = get_float("C: ");
    float fahrenheit = ((celsius * 9) / 5) + 32;

    // Output with 1 digit after the decimal point
    printf("F: %.1f", fahrenheit);
}