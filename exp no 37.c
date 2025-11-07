#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, total = 0;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    int req[n];
    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    int disk_size = 199;

    // Sort requests
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (req[i] > req[j]) {
                int t = req[i];
                req[i] = req[j];
                req[j] = t;
            }

    int pos;
    for (int i = 0; i < n; i++)
        if (head < req[i]) { pos = i; break; }

    for (int i = pos; i < n; i++) total += abs(req[i] - head), head = req[i];
    total += abs(disk_size - head) + disk_size;
    head = 0;
    for (int i = 0; i < pos; i++) total += abs(req[i] - head), head = req[i];

    printf("Total head movement: %d\n", total);
    return 0;
}

