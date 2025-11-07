#include <stdio.h>
int main() {
    int pages[30], frames[10], recent[10], n, f, i, j, k, pos, faults=0, found, min;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page numbers: ");
    for(i=0;i<n;i++) scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(i=0;i<f;i++) frames[i] = -1;

    for(i=0;i<n;i++) {
        found=0;
        for(j=0;j<f;j++) if(frames[j]==pages[i]) {found=1; recent[j]=i;}
        if(!found) {
            if(i<f) frames[i]=pages[i];
            else {
                min=0;
                for(k=1;k<f;k++) if(recent[k]<recent[min]) min=k;
                frames[min]=pages[i];
                recent[min]=i;
            }
            faults++;
        }
        for(k=0;k<f;k++) if(frames[k]!=-1) recent[k]=i;
        printf("\nFrames: ");
        for(k=0;k<f;k++) printf("%d ", frames[k]);
    }
    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
}

