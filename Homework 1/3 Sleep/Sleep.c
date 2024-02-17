#include <stdio.h>
#include <unistd.h>

int main()
{
    int seconds;

    printf("Enter the number of seconds to sleep: ");
    scanf("%d", &seconds);

    if (seconds < 0)
    {
        printf("Invalid input. Please enter a positive number.\n");
        return 1;
    }

    printf("Sleeping for %d seconds...\n", seconds);
    sleep(seconds);
    printf("Woke up after %d seconds.\n", seconds);

    return 0;
}