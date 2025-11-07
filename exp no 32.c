#include <stdio.h>
int main() {
    int pages[30], frames[10], n, f, i, j, k, next[10], faults=0, found, replace, farthest;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page numbers: ");
    for(i=0;i<n;i++) scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(i=0;i<f;i++) frames[i] = -1;

    for(i=0;i<n;i++) {
        found=0;
        for(j=0;j<f;j++) if(frames[j]==pages[i]) found=1;
        if(!found) {
            if(i<f) frames[i]=pages[i];
            else {
                for(j=0;j<f;j++) {
                    next[j]=9999;
                    for(k=i+1;k<n;k++) if(frames[j]==pages[k]) {next[j]=k; break;}
                }
                farthest=0;
                for(j=1;j<f;j++) if(next[j]>next[farthest]) farthest=j;
                frames[farthest]=pages[i];
            }
            faults++;
        }
        printf("\nFrames: ");
        for(j=0;j<f;j++) printf("%d ", frames[j]);
    }
    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
}

