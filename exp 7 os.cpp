#include <stdio.h>

int main() {
    int n, tq, time = 0, remain;
    printf("Enter number of processes and Time Quantum: ");
    scanf("%d%d", &n, &tq);

    int at[n], bt[n], rt[n], ct[n], wt[n], tat[n];
    for (int i = 0; i < n; i++) {
        printf("P%d AT BT: ", i+1);
        scanf("%d%d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    remain = n;
    while (remain) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0 && at[i] <= time) {
                done = 0;
                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    rt[i] = 0;
                    remain--;
                }
            }
        }
        if (done) time++;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    float twt = 0, ttat = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
        twt += wt[i]; ttat += tat[i];
    }
    printf("\nAvg WT = %.2f\nAvg TAT = %.2f\n", twt/n, ttat/n);
    return 0;
}
