#include <stdio.h>

int main()
{
    int rows, seats, k;
    int i, j, r, c;
    int middle, distance;
    int available, totalAvailable = 0;
    int found, start, selectedRow;
    int bestDistance, currentDistance;
    int temp;

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter seats per row: ");
    scanf("%d", &seats);

    int seatingPlan[rows][seats];

    // 1. Input Seating Plan
    printf("\nEnter seating status (0 = Available, 1 = Booked):\n");

    for (i = 0; i < rows; i++)
    {
        printf("Row %d:\n", i);

        for (j = 0; j < seats; j++)
        {
            do
            {
                printf("Seat %d: ", j);
                scanf("%d", &seatingPlan[i][j]);

                if (seatingPlan[i][j] != 0 &&
                    seatingPlan[i][j] != 1)
                {
                    printf("Invalid input! Enter 0 or 1.\n");
                }

            } while (seatingPlan[i][j] != 0 &&
                     seatingPlan[i][j] != 1);
        }
    }

    // 2. Display Seating Arrangement
    printf("\n--- Seating Arrangement ---\n");
    printf("     ");

    for (j = 0; j < seats; j++)
    {
        printf("%d ", j);
    }

    printf("\n");

    for (i = 0; i < rows; i++)
    {
        printf("Row %d ", i);

        for (j = 0; j < seats; j++)
        {
            if (seatingPlan[i][j] == 0)
                printf("_ ");
            else
                printf("X ");
        }

        printf("\n");
    }

    // 3. Seat Availability Report
    printf("\n--- Seat Availability Report ---\n");

    for (i = 0; i < rows; i++)
    {
        available = 0;

        for (j = 0; j < seats; j++)
        {
            if (seatingPlan[i][j] == 0)
            {
                available++;
            }
        }

        printf("Row %d: %d available seats\n", i, available);
        totalAvailable += available;
    }

    printf("Total available seats: %d\n", totalAvailable);

    // 4. Group Booking
    printf("\nEnter number of customers (k): ");
    scanf("%d", &k);

    if (k <= 0 || k > seats)
    {
        printf("Invalid group size! It must be between 1 and %d.\n",
               seats);
        return 0;
    }

    // 5. Seat Allocation Rules
    middle = rows / 2;
    found = 0;
    selectedRow = -1;
    start = -1;

    /*
       Search rows in increasing distance from the middle.
       If two rows have the same distance, search the smaller
       row number first.
    */

    for (distance = 0; distance < rows && !found; distance++)
    {
        for (r = 0; r < rows && !found; r++)
        {
            currentDistance = r - middle;

            if (currentDistance < 0)
                currentDistance = -currentDistance;

            if (currentDistance == distance)
            {
                // Search from the lowest seat number
                for (c = 0; c <= seats - k; c++)
                {
                    available = 1;

                    // Check k consecutive seats
                    for (j = c; j < c + k; j++)
                    {
                        if (seatingPlan[r][j] != 0)
                        {
                            available = 0;
                            break;
                        }
                    }

                    if (available == 1)
                    {
                        selectedRow = r;
                        start = c;
                        found = 1;
                        break;
                    }
                }
            }
        }
    }

    // 6. Confirm Booking
    if (found == 1)
    {
        printf("\nBooking successful!\n");
        printf("Allocated Row: %d\n", selectedRow);
        printf("Allocated Seat Numbers: ");

        for (j = start; j < start + k; j++)
        {
            printf("%d ", j);
            seatingPlan[selectedRow][j] = 1;
        }

        printf("\n");

        // Display Updated Seating Arrangement
        printf("\n--- Updated Seating Arrangement ---\n");
        printf("     ");

        for (j = 0; j < seats; j++)
        {
            printf("%d ", j);
        }

        printf("\n");

        for (i = 0; i < rows; i++)
        {
            printf("Row %d ", i);

            for (j = 0; j < seats; j++)
            {
                if (seatingPlan[i][j] == 0)
                    printf("_ ");
                else
                    printf("X ");
            }

            printf("\n");
        }

        // Display Remaining Available Seats
        totalAvailable = 0;

        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < seats; j++)
            {
                if (seatingPlan[i][j] == 0)
                {
                    totalAvailable++;
                }
            }
        }

        printf("Remaining available seats: %d\n", totalAvailable);
    }
    else
    {
        // 7. Handle Unsuccessful Booking
        printf("\nBooking unsuccessful!\n");
        printf("No row contains %d consecutive available seats.\n", k);
        printf("Seating plan remains unchanged.\n");
    }

    return 0;
}