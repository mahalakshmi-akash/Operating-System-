#include <stdio.h>

int main() {
    int n, i, time = 0, smallest, remain = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], pr[n], rt[n];
    for (i = 0; i < n; i++) {
        printf("P%d AT BT PR: ", i+1);
        scanf("%d%d%d", &at[i], &bt[i], &pr[i]);
        rt[i] = bt[i];
    }

    int completed = 0, wt = 0, tat = 0;
    while (completed < n) {
        int min_pr = 999, idx = -1;
        for (i = 0; i < n; i++)
            if (at[i] <= time && rt[i] > 0 && pr[i] < min_pr) {
                min_pr = pr[i];
                idx = i;
            }

        if (idx == -1) { time++; continue; }

        rt[idx]--; time++;
        if (rt[idx] == 0) {
            completed++;
            int finish = time;
            tat += finish - at[idx];
            wt += finish - at[idx] - bt[idx];
        }
    }

    printf("Avg WT: %.2f\nAvg TAT: %.2f\n", (float)wt/n, (float)tat/n);
    return 0;
}
