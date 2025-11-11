#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to perform Bubble Sort
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to perform Insertion Sort
void insertionSort(int arr[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Function to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of integers: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    pid_t pid = fork();  // Create child process

    if (pid < 0) {
        printf("Fork failed!\n");
        exit(1);
    }

    else if (pid == 0) {
        // CHILD PROCESS: Insertion Sort
        printf("\nChild Process (PID = %d) performing Insertion Sort...\n", getpid());
        insertionSort(arr, n);
        printf("Child Sorted Array (Insertion Sort): ");
        printArray(arr, n);

        // Demonstrate ORPHAN: Uncomment below lines to see orphan process
        //sleep(5); // make child sleep so parent ends first
        //printf("\nChild (PID=%d) now orphan (parent died), new parent = %d\n", getpid(), getppid());
       
         printf("\nChild process finished.\n");

        exit(0); // Child ends
    }

    else {
        // PARENT PROCESS: Bubble Sort
        printf("\nParent Process (PID = %d) performing Bubble Sort...\n", getpid());
        bubbleSort(arr, n);
        printf("Parent Sorted Array (Bubble Sort): ");
        printArray(arr, n);

        // Demonstrate ZOMBIE: Uncomment below line
        //sleep(10); // child will finish first, becomes zombie until parent waits in parallel command line prompt use "ps -ef" to show zombie state as defunct

        wait(NULL); // parent waits for child to avoid zombie
        printf("\nParent process finished.\n");
    }

    return 0;
}