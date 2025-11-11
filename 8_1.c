#include <stdio.h>
#include <stdlib.h>

#define DISK_SIZE 500

// Function to sort the requests in ascending order
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

void CSCAN(int requests[], int n, int head)
{
    int total = 0;
    int i;
    int left[n], right[n];
    int lcount = 0, rcount = 0;

    // Split requests into two parts: right and left of head
    for (i = 0; i < n; i++)
    {
        if (requests[i] >= head)
            right[rcount++] = requests[i];
        else
            left[lcount++] = requests[i];
    }

    sort(right, rcount);
    sort(left, lcount);

    printf("\nC-SCAN order: ");

    // Move toward end (499)
    for (i = 0; i < rcount; i++)
    {
        printf("%d ", right[i]);
        total += abs(head - right[i]);
        head = right[i];
    }

    // Move to end (499)
    total += abs((DISK_SIZE - 1) - head);
    head = 0; // Jump (not counted)

    // Then move on left side
    for (i = 0; i < lcount; i++)
    {
        printf("%d ", left[i]);
        total += abs(head - left[i]);
        head = left[i];
    }

    printf("\nTotal Head Movement (C-SCAN): %d", total);
    printf("\nAverage Seek Distance (C-SCAN): %.2f\n", (float)total / n);
}

void CLOOK(int requests[], int n, int head)
{
    int total = 0;
    int i;
    int left[n], right[n];
    int lcount = 0, rcount = 0;

    // Split requests into two parts
    for (i = 0; i < n; i++)
    {
        if (requests[i] >= head)
            right[rcount++] = requests[i];
        else
            left[lcount++] = requests[i];
    }

    sort(right, rcount);
    sort(left, lcount);

    printf("\nC-LOOK order: ");

    // Move toward higher requests
    for (i = 0; i < rcount; i++)
    {
        printf("%d ", right[i]);
        total += abs(head - right[i]);
        head = right[i];
    }

    // Jump directly to smallest (not counted)
    if (lcount > 0)
    {
        head = left[0];
        printf("%d ", head);
        for (i = 1; i < lcount; i++)
        {
            total += abs(head - left[i]);
            head = left[i];
            printf("%d ", head);
        }
    }

    printf("\nTotal Head Movement (C-LOOK): %d", total);
    printf("\nAverage Seek Distance (C-LOOK): %.2f\n", (float)total / n);
}

int main()
{
    int head = 85;
    int requests[] = {10, 229, 39, 400, 18, 145, 120, 480, 20, 250};
    int n = sizeof(requests) / sizeof(requests[0]);

    printf("Initial Head Position: %d\n", head);

    CSCAN(requests, n, head);
    CLOOK(requests, n, head);

    printf("\nConclusion: C-LOOK performs better (less head movement).\n");

    return 0;
}