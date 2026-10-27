
#include <stdio.h>

void inputReadings(int sensors, int hours, float temp[sensors][hours])
{
    int i, j;

    for (i = 0; i < sensors; i++)
    {
        printf("\nEnter readings for Sensor %d:\n", i + 1);

        for (j = 0; j < hours; j++)
        {
            printf("Hour %d: ", j + 1);
            scanf("%f", &temp[i][j]);
        }
    }
}

void analyzeSensor(int hours, float temp[], float *total,
                   float *average, float *highest, float *lowest,
                   int *critical, int *warning, int *longestStreak)
{
    int i;
    int streak = 0;

    *total = 0;
    *highest = temp[0];
    *lowest = temp[0];
    *critical = 0;
    *warning = 0;
    *longestStreak = 0;

    for (i = 0; i < hours; i++)
    {
        *total += temp[i];

        if (temp[i] > *highest)
            *highest = temp[i];

        if (temp[i] < *lowest)
            *lowest = temp[i];

        if (temp[i] >= 40)
            (*critical)++;

        if (temp[i] >= 35 && temp[i] <= 39)
            (*warning)++;

        if (temp[i] >= 35)
        {
            streak++;

            if (streak > *longestStreak)
                *longestStreak = streak;
        }
        else
        {
            streak = 0;
        }
    }

    *average = *total / hours;
}

int highestAverageSensor(int sensors, int hours,
                         float temp[sensors][hours])
{
    int i, j;
    int bestSensor = 0;
    float total, average;
    float highestAverage = -1;

    for (i = 0; i < sensors; i++)
    {
        total = 0;

        for (j = 0; j < hours; j++)
        {
            total += temp[i][j];
        }

        average = total / hours;

        if (average > highestAverage)
        {
            highestAverage = average;
            bestSensor = i;
        }
    }

    return bestSensor;
}

int main()
{
    int sensors, hours;
    int i;
    int critical, warning, longestStreak;
    float total, average, highest, lowest;

    printf("Enter number of sensors: ");
    scanf("%d", &sensors);

    printf("Enter number of hourly readings: ");
    scanf("%d", &hours);

    if (sensors <= 0 || hours <= 0)
    {
        printf("Invalid number of sensors or hours.\n");
        return 0;
    }

    float temp[sensors][hours];

    // 1. Input data
    inputReadings(sensors, hours, temp);

    // 2. Individual sensor reports
    printf("\n===== INDIVIDUAL SENSOR REPORTS =====\n");

    for (i = 0; i < sensors; i++)
    {
        analyzeSensor(hours, temp[i], &total, &average,
                      &highest, &lowest, &critical,
                      &warning, &longestStreak);

        printf("\nSensor %d:\n", i + 1);
        printf("Total = %.2f\n", total);
        printf("Average = %.2f\n", average);
        printf("Highest = %.2f\n", highest);
        printf("Lowest = %.2f\n", lowest);
        printf("Critical readings = %d\n", critical);
        printf("Warning readings = %d\n", warning);
        printf("Longest hot streak = %d\n", longestStreak);
    }

    // 3. Find sensor with highest average
    int bestSensor = highestAverageSensor(sensors, hours, temp);

    total = 0;

    for (i = 0; i < hours; i++)
    {
        total += temp[bestSensor][i];
    }

    average = total / hours;

    // 4. Final report
    printf("\n===== FINAL REPORT =====\n");
    printf("Highest average: Sensor %d (%.2f)\n",
           bestSensor + 1, average);

    return 0;
}
