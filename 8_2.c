#include <stdio.h>
#include <stdlib.h>

#define DISK_SIZE 500 // cylinders 0 - 499

// Function to sort requests in ascending order
void sort(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void SCAN(int requests[], int n, int head)
{
    int total = 0;
    int i;
    int left[n], right[n];
    int lcount = 0, rcount = 0;

    // Split into left and right of head
    for (i = 0; i < n; i++)
    {
        if (requests[i] >= head)
            right[rcount++] = requests[i];
        else
            left[lcount++] = requests[i];
    }

    sort(right, rcount);
    sort(left, lcount);

    printf("\nSCAN order: ");

    // Move towards 499 first
    for (i = 0; i < rcount; i++)
    {
        printf("%d ", right[i]);
        total += abs(head - right[i]);
        head = right[i];
    }

    // After reaching the last request, go to end (499)
    total += abs((DISK_SIZE - 1) - head);
    head = DISK_SIZE - 1;

    // Then move in the opposite direction (towards 0)
    for (i = lcount - 1; i >= 0; i--)
    {
        printf("%d ", left[i]);
        total += abs(head - left[i]);
        head = left[i];
    }

    printf("\nTotal Head Movement (SCAN): %d", total);
    printf("\nAverage Seek Distance (SCAN): %.2f\n", (float)total / n);
}

void LOOK(int requests[], int n, int head)
{
    int total = 0;
    int i;
    int left[n], right[n];
    int lcount = 0, rcount = 0;

    // Split into left and right of head
    for (i = 0; i < n; i++)
    {
        if (requests[i] >= head)
            right[rcount++] = requests[i];
        else
            left[lcount++] = requests[i];
    }

    sort(right, rcount);
    sort(left, lcount);

    printf("\nLOOK order: ");

    // Move toward higher requests first
    for (i = 0; i < rcount; i++)
    {
        printf("%d ", right[i]);
        total += abs(head - right[i]);
        head = right[i];
    }

    // Then move toward lower requests (reverse)
    for (i = lcount - 1; i >= 0; i--)
    {
        printf("%d ", left[i]);
        total += abs(head - left[i]);
        head = left[i];
    }

    printf("\nTotal Head Movement (LOOK): %d", total);
    printf("\nAverage Seek Distance (LOOK): %.2f\n", (float)total / n);
}

int main()
{
    int head = 185;
    int requests[] = {20, 229, 39, 450, 18, 145, 120, 380, 20, 250};
    int n = sizeof(requests) / sizeof(requests[0]);

    printf("Initial Head Position: %d\n", head);

    SCAN(requests, n, head);
    LOOK(requests, n, head);

    printf("\nConclusion: LOOK generally performs better (less head movement).\n");

    return 0;
}