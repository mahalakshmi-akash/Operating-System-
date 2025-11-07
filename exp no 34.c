#include <stdio.h>
int main() {
    int index[50], n, i, j, block[50];
    for(i=0;i<50;i++) block[i]=0;

    printf("Enter index block: ");
    scanf("%d", &i);
    block[i]=1;

    printf("Enter number of data blocks: ");
    scanf("%d", &n);
    printf("Enter block numbers: ");
    for(j=0;j<n;j++) {
        scanf("%d", &index[j]);
        block[index[j]]=1;
    }

    printf("\nFile allocated using Indexed Allocation.\n");
    printf("Index Block %d ? ", i);
    for(j=0;j<n;j++) printf("%d ", index[j]);
    printf("\n");

    printf("\nBlock Status:\n");
    for(i=0;i<50;i++) printf("%d ", block[i]);
    return 0;
}

