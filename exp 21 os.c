#include <stdio.h>
int main() {
    int block[10], process[10], nb, np, alloc[10], i, j;
    printf("Enter number of blocks and processes: ");
    scanf("%d%d", &nb, &np);
    printf("Enter block sizes: ");
    for(i=0;i<nb;i++) scanf("%d",&block[i]);
    printf("Enter process sizes: ");
    for(i=0;i<np;i++) scanf("%d",&process[i]);

    for(i=0;i<np;i++) {
        int worst=-1;
        for(j=0;j<nb;j++)
            if(block[j]>=process[i])
                if(worst==-1 || block[j]>block[worst])
                    worst=j;
        if(worst!=-1) {
            alloc[i]=worst;
            block[worst]-=process[i];
        } else alloc[i]=-1;
    }

    printf("\nProcess\tBlock\n");
    for(i=0;i<np;i++)
        printf("%d\t%s\n", process[i], alloc[i]==-1?"Not Allocated":"Allocated");
}

