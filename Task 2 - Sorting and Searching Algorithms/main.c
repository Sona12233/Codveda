
#include <stdio.h>
#include <time.h>

#define MAX_SIZE 10000

// Best O(n), Average O(n^2), Worst O(n^2)
void bubble_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;

        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }
}

// Best O(nlogn), Average O(nlogn), Worst O(n^2)
void quick_sort(int a[], int left, int right) {
    int i = left, j = right;
    int pivot = a[left + (right - left) / 2];

    while (i <= j) {
        while (a[i] < pivot)
            i++;

        while (a[j] > pivot)
            j--;

        if (i <= j) {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j)
        quick_sort(a, left, j);

    if (i < right)
        quick_sort(a, i, right);
}

// Best O(1), Average O(n), Worst O(n)
int linear_search(const int a[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (a[i] == target)
            return i;
    }

    return -1;
}

// Best O(1), Average O(logn), Worst O(logn)
int binary_search(const int a[], int n, int target) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (a[mid] == target)
            return mid;

        if (a[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

void print_array(const int a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

int main(void) {
    int a[MAX_SIZE], n, choice, target;

    printf("Enter array size (1-%d): ", MAX_SIZE);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_SIZE) {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
    }

    do {
        printf("\n--- Sorting and Searching ---\n");
        printf("1. Bubble sort\n");
        printf("2. Quick sort\n");
        printf("3. Linear search\n");
        printf("4. Binary search (sorts array first)\n");
        printf("5. Print array\n");
        printf("0. Exit\n");
        printf("Choose: ");

        if (scanf("%d", &choice) != 1)
            break;

        clock_t start;
        double elapsed;
        int index;

        switch (choice) {
            case 1:
                start = clock();
                //calling function in loop to actually compare timing
                for (int i = 0; i < 100000; i++)
                    bubble_sort(a, n);
                elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
                printf("Sorted with bubble sort:\n");
                print_array(a, n);
                printf("Time: %.6f seconds\n", elapsed);
                break;

            case 2:
                start = clock();
                //calling function in loop to actually compare timing
                for (int i = 0; i < 100000; i++)
                    quick_sort(a, 0, n - 1);
                elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
                printf("Sorted with quicksort:\n");
                print_array(a, n);
                printf("Time: %.6f seconds\n", elapsed);
                break;

            case 3:
                printf("Enter target: ");
                if (scanf("%d", &target) != 1)
                    return 1;

                start = clock();
                //calling function in loop to actually compare timing
                for (int i = 0; i < 100000; i++)
                    index = linear_search(a, n, target);
                elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;

                if (index != -1)
                    printf("Found at index %d.\n", index);
                else
                    printf("Not found.\n");

                printf("Time: %.6f seconds\n", elapsed);
                break;

            case 4:
                quick_sort(a, 0, n - 1);

                printf("Enter target: ");
                if (scanf("%d", &target) != 1)
                    return 1;

                start = clock();
                //calling function in loop to actually compare timing
                for (int i = 0; i < 100000; i++)
                    index = binary_search(a, n, target);

                elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;

                if (index != -1)
                    printf("Found at index %d.\n", index);
                else
                    printf("Not found.\n");

                printf("Search time: %.6f seconds\n", elapsed);
                break;

            case 5:
                print_array(a, n);
                break;

            case 0:
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
