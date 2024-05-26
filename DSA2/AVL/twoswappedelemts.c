#include <stdio.h>

void findSwappedElements(int arr[], int n) {
    int first = -1, second = -1;

    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            first = i;
            break;
        }
    }
    for (int i = n - 1; i > 0; i--) {
        if (arr[i] < arr[i - 1]) {
            second = i;
            break;
        }
    }
    printf("Swapped elements: %d and %d\n", arr[first], arr[second]);
    printf("Positions: %d and %d\n", first + 1, second + 1);
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements of the array: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    findSwappedElements(arr, n);

    return 0;
}

