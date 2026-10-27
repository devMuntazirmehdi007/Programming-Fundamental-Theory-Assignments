
#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 50
#define MAX_BORROWED 5

// Membership types
#define STUDENT 1
#define FACULTY 2

// Sample membership code for fine waiver
#define MEMBERSHIP_CODE "LIB50"

// 1. Display menu
void displayMenu()
{
    printf("\n===== UNIVERSITY LIBRARY SYSTEM =====\n");
    printf("1. Register Member\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
}

// 2. Register member
void registerMember(char name[], int *studentID, int *memberType)
{
    int type;

    printf("Enter member name: ");
    scanf(" %49[^\n]", name);

    printf("Enter Student/Member ID: ");
    scanf("%d", studentID);

    do
    {
        printf("Enter membership type (1=Student, 2=Faculty): ");
        scanf("%d", &type);

        if (type != STUDENT && type != FACULTY)
            printf("Invalid membership type!\n");

    } while (type != STUDENT && type != FACULTY);

    *memberType = type;

    printf("Member registered successfully!\n");
}

// 3. Display available books
void displayBooks(int bookIDs[], char bookTitles[][50],
                  int availableCopies[], int totalBooks)
{
    int i;

    printf("\n========== AVAILABLE BOOKS ==========\n");
    printf("%-10s %-25s %-10s\n", "Book ID", "Title", "Copies");

    for (i = 0; i < totalBooks; i++)
    {
        printf("%-10d %-25s %-10d\n",
               bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}

// 4. Borrow a book
void borrowBook(int bookIDs[], char bookTitles[][50],
                int availableCopies[], int totalBooks,
                int borrowedBookIDs[], int *borrowedCount,
                int memberType)
{
    int id, days, i, found = -1;
    int maxBooks, allowedDays;

    if (memberType == STUDENT)
    {
        maxBooks = 2;
        allowedDays = 14;
    }
    else if (memberType == FACULTY)
    {
        maxBooks = 5;
        allowedDays = 30;
    }
    else
    {
        printf("Please register first.\n");
        return;
    }

    if (*borrowedCount >= maxBooks)
    {
        printf("Borrowing limit reached!\n");
        return;
    }

    printf("Enter Book ID: ");
    scanf("%d", &id);

    for (i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == id)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("Invalid Book ID!\n");
        return;
    }

    if (availableCopies[found] <= 0)
    {
        printf("No available copies of this book.\n");
        return;
    }

    printf("Enter number of days you intend to keep the book: ");
    scanf("%d", &days);

    if (days <= 0)
    {
        printf("Number of days must be positive.\n");
        return;
    }

    if (days > allowedDays)
    {
        printf("Borrowing period cannot exceed %d days.\n",
               allowedDays);
        return;
    }

    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;
    availableCopies[found]--;

    printf("Book borrowed successfully: %s\n", bookTitles[found]);
}

// 5. Return a book
float returnBook(int bookIDs[], int availableCopies[],
                 int totalBooks, int borrowedBookIDs[],
                 int *borrowedCount, int memberType,
                 float *totalFine)
{
    int id, daysKept, i, j;
    int foundBorrowed = -1, foundBook = -1;
    int allowedDays, finePerDay;
    float fine = 0;
    char code[30];

    if (memberType == STUDENT)
    {
        allowedDays = 14;
        finePerDay = 20;
    }
    else if (memberType == FACULTY)
    {
        allowedDays = 30;
        finePerDay = 10;
    }
    else
    {
        printf("Please register first.\n");
        return 0;
    }

    printf("Enter Book ID to return: ");
    scanf("%d", &id);

    for (i = 0; i < *borrowedCount; i++)
    {
        if (borrowedBookIDs[i] == id)
        {
            foundBorrowed = i;
            break;
        }
    }

    if (foundBorrowed == -1)
    {
        printf("This book is not in your borrowing record.\n");
        return 0;
    }

    for (i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == id)
        {
            foundBook = i;
            break;
        }
    }

    if (foundBook == -1)
    {
        printf("Book record not found.\n");
        return 0;
    }

    printf("Enter total number of days the book was kept: ");
    scanf("%d", &daysKept);

    if (daysKept <= 0)
    {
        printf("Number of days must be positive.\n");
        return 0;
    }

    // Calculate late fine
    if (daysKept > allowedDays)
    {
        fine = (daysKept - allowedDays) * finePerDay;

        printf("Late fine before waiver: Rs. %.2f\n", fine);

        printf("Enter membership code for 50%% fine waiver: ");
        scanf("%29s", code);

        if (strcmp(code, MEMBERSHIP_CODE) == 0)
        {
            fine = fine * 0.50;
            printf("Valid code! 50%% waiver applied.\n");
        }
        else
        {
            printf("Invalid code. No waiver applied.\n");
        }
    }
    else
    {
        printf("Book returned within the allowed period.\n");
    }

    // Update available copies
    availableCopies[foundBook]++;

    // Remove returned book from borrowing record
    for (j = foundBorrowed; j < *borrowedCount - 1; j++)
    {
        borrowedBookIDs[j] = borrowedBookIDs[j + 1];
    }

    (*borrowedCount)--;

    // Update cumulative fine
    *totalFine += fine;

    printf("Book returned successfully!\n");
    printf("Fine payable: Rs. %.2f\n", fine);
    printf("Cumulative fine: Rs. %.2f\n", *totalFine);

    return fine;
}

// 6. Display member record
void displayMemberRecord(char name[], int studentID,
                         int memberType, int borrowedBookIDs[],
                         int borrowedCount, float totalFine,
                         float fineAfterWaiver)
{
    int i;

    if (memberType == 0)
    {
        printf("No member registered yet.\n");
        return;
    }

    printf("\n========== MEMBER RECORD ==========\n");
    printf("Name: %s\n", name);
    printf("Member ID: %d\n", studentID);

    if (memberType == STUDENT)
        printf("Membership: Student\n");
    else
        printf("Membership: Faculty\n");

    printf("Currently borrowed books: %d\n", borrowedCount);

    if (borrowedCount == 0)
    {
        printf("No books currently borrowed.\n");
    }
    else
    {
        printf("Borrowed Book IDs: ");

        for (i = 0; i < borrowedCount; i++)
        {
            printf("%d ", borrowedBookIDs[i]);
        }

        printf("\n");
    }

    printf("Cumulative fine payable: Rs. %.2f\n", totalFine);
    printf("Last return fine after waiver: Rs. %.2f\n",
           fineAfterWaiver);
}

int main()
{
    int bookIDs[MAX_BOOKS] = {101, 102, 103, 104};
    char bookTitles[MAX_BOOKS][50] = {
        "Programming in C",
        "Data Structures",
        "Database Systems",
        "Computer Networks"
    };

    int availableCopies[MAX_BOOKS] = {5, 3, 0, 4};

    int totalBooks = 4;
    int borrowedBookIDs[MAX_BORROWED];
    int borrowedCount = 0;

    char name[50] = "";
    int studentID = 0;
    int memberType = 0;

    int choice;
    float totalFine = 0;
    float fineAfterWaiver = 0;

    do
    {
        displayMenu();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                if (memberType != 0)
                {
                    printf("A member is already registered.\n");
                }
                else
                {
                    registerMember(name, &studentID, &memberType);
                }
                break;

            case 2:
                displayBooks(bookIDs, bookTitles,
                             availableCopies, totalBooks);
                break;

            case 3:
                if (memberType == 0)
                {
                    printf("Please register before borrowing.\n");
                }
                else
                {
                    borrowBook(bookIDs, bookTitles,
                               availableCopies, totalBooks,
                               borrowedBookIDs, &borrowedCount,
                               memberType);
                }
                break;

            case 4:
                if (memberType == 0)
                {
                    printf("Please register before returning books.\n");
                }
                else
                {
                    fineAfterWaiver = returnBook(
                        bookIDs, availableCopies, totalBooks,
                        borrowedBookIDs, &borrowedCount,
                        memberType, &totalFine);
                }
                break;

            case 5:
                displayMemberRecord(name, studentID, memberType,
                                    borrowedBookIDs, borrowedCount,
                                    totalFine, fineAfterWaiver);
                break;

            case 6:
                printf("Exiting Library Management System.\n");
                break;

            default:
                printf("Invalid menu choice! Try again.\n");
        }

    } while (choice != 6);

    return 0;
}
