#include <stdio.h>

int main() {
    int n, i;
    printf("Enter number of blocks in file: ");
    scanf("%d", &n);
    int block[n];
    printf("Enter block numbers:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &block[i]);

    printf("\nLinked Allocation:\nStart -> ");
    for (i = 0; i < n; i++)
        printf("%d -> ", block[i]);
    printf("NULL\n");
    return 0;
}

