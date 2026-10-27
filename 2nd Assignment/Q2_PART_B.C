
#include <stdio.h>

int main()
{
    int n = 220;
    int i, sum1 = 1, sum2 = 1;

    printf("Finding proper divisors of 220:\n");

    for (i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
        {
            sum1 += i;
            printf("%d added, running sum = %d\n", i, sum1);
        }
    }

    printf("\nSum of proper divisors of 220 = %d\n", sum1);

    n = sum1;

    printf("\nFinding proper divisors of %d:\n", n);

    for (i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
        {
            sum2 += i;
            printf("%d added, running sum = %d\n", i, sum2);
        }
    }

    printf("\nSum of proper divisors of 284 = %d\n", sum2);

    if (sum2 == 220 && n != 220)
    {
        printf("\n(220, 284) is an amicable pair.\n");
    }
    else
    {
        printf("\nNot an amicable pair.\n");
    }

    return 0;
}
