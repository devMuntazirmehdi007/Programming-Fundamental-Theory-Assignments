
#include <stdio.h>
#include <math.h>

int sumDivisors(int n)
{
    int sum = 1;

    if (n <= 1)
        return 0;

    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            sum += i;

            if (i != n / i)
            {
                sum += n / i;
            }
        }
    }

    return sum;
}

int main()
{
    int n;
    int i, j;
    int sum1, sum2;
    int count = 0;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Amicable pairs up to %d:\n", n);

    for (i = 2; i <= n; i++)
    {
        sum1 = sumDivisors(i);

        // Exclude perfect numbers
        if (sum1 == i)
            continue;

        // The second number must be greater than the first
        j = sum1;

        if (j > i && j <= n)
        {
            sum2 = sumDivisors(j);

            if (sum2 == i)
            {
                printf("(%d, %d)\n", i, j);
                count++;
            }
        }
    }

    if (count == 0)
    {
        printf("No amicable pairs found.\n");
    }

    printf("Total pairs: %d\n", count);

    return 0;
}
