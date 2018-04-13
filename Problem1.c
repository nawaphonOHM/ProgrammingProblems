#include <stdio.h>

int main ()
{
    unsigned long long int inputA = 0, 
                           inputB = 0;

        scanf ("%llu", &inputA);
        scanf ("%llu", &inputB);

        printf ("%llu", inputA * inputB);

        return 0;
}