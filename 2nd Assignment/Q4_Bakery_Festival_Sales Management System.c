
#include <stdio.h>

// 1. Input and validate festival duration
int getValidDays()
{
    int days;

    do
    {
        printf("Enter number of festival days (1-7): ");
        scanf("%d", &days);

        if (days < 1 || days > 7)
        {
            printf("Invalid days! Enter between 1 and 7.\n");
        }

    } while (days < 1 || days > 7);

    return days;
}

// 2. Calculate daily sales
float calculateDailySales(int dayNumber)
{
    int orders, i;
    float amount;
    float total = 0, highest = 0;

    printf("\nDay %d\n", dayNumber);

    do
    {
        printf("Enter number of customer orders: ");
        scanf("%d", &orders);

        if (orders < 1)
        {
            printf("Number of orders must be at least 1.\n");
        }

    } while (orders < 1);

    for (i = 1; i <= orders; i++)
    {
        do
        {
            printf("Enter amount for order %d: ", i);
            scanf("%f", &amount);

            if (amount <= 0)
            {
                printf("Amount must be greater than zero.\n");
            }

        } while (amount <= 0);

        total += amount;

        if (amount > highest)
        {
            highest = amount;
        }
    }

    printf("Total sales: %.2f\n", total);
    printf("Average order amount: %.2f\n", total / orders);
    printf("Highest order amount: %.2f\n", highest);

    return total;
}

// 3. Find day with highest sales
int findHighestSalesDay(float dailySales[], int numberOfDays)
{
    int i;
    int highestDay = 0;

    for (i = 1; i < numberOfDays; i++)
    {
        if (dailySales[i] > dailySales[highestDay])
        {
            highestDay = i;
        }
    }

    return highestDay;
}

// 4. Display daily sales bar chart
void displayBarChart(float dailySales[], int numberOfDays)
{
    int i, j;
    int stars;

    printf("\n===== DAILY SALES BAR CHART =====\n");

    for (i = 0; i < numberOfDays; i++)
    {
        stars = (int)(dailySales[i] / 100.0);

        printf("Day %d: ", i + 1);

        for (j = 0; j < stars; j++)
        {
            printf("*");
        }

        printf(" (%.2f)\n", dailySales[i]);
    }

    printf("Each * represents Rs. 100 of sales.\n");
}

int main()
{
    int days, i;
    int highestDay;
    float festivalTotal = 0;

    // Input festival duration
    days = getValidDays();

    // Store each day's total sales
    float dailySales[days];

    // Calculate daily sales
    for (i = 0; i < days; i++)
    {
        dailySales[i] = calculateDailySales(i + 1);
        festivalTotal += dailySales[i];
    }

    // Find highest-sales day
    highestDay = findHighestSalesDay(dailySales, days);

    // Festival summary
    printf("\n===== FESTIVAL SALES SUMMARY =====\n");
    printf("Total festival sales: %.2f\n", festivalTotal);
    printf("Day with highest sales: Day %d\n", highestDay + 1);
    printf("Highest daily sales: %.2f\n", dailySales[highestDay]);

    // Display bar chart
    displayBarChart(dailySales, days);

    return 0;
}
