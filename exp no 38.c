#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, i, j, total = 0;
    printf("Enter total number of requests: ");
    scanf("%d", &n);

    int req[n];
    printf("Enter request sequence: ");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    int disk_size;
    printf("Enter total disk size: ");
    scanf("%d", &disk_size);

    // Sort the request array
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (req[j] > req[j + 1]) {
                int temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }

    int pos = 0;
    for (i = 0; i < n; i++) {
        if (head < req[i]) {
            pos = i;
            break;
        }
    }

    printf("\nC-SCAN Disk Scheduling Order:\n");

    // Move right from current head position
    for (i = pos; i < n; i++) {
        printf("%d ", req[i]);
        total += abs(req[i] - head);
        head = req[i];
    }

    // Move from last to end of disk
    total += abs((disk_size - 1) - head);
    head = 0;
    total += (disk_size - 1);

    // Continue from start of disk
    for (i = 0; i < pos; i++) {
        printf("%d ", req[i]);
        total += abs(req[i] - head);
        head = req[i];
    }

    printf("\nTotal head movement: %d\n", total);
    return 0;
}

