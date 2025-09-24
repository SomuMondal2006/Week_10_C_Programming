//Job sequencing problem
//https://www.geeksforgeeks.org/problems/job-sequencing-problem/1



#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int profit;
    int deadline;
} Job;

int cmp(const void* a, const void* b) {
    Job *j1 = (Job*)a;
    Job *j2 = (Job*)b;
    return j2->profit - j1->profit;
}

int max(int a, int b) { return (a > b) ? a : b; }

void jobScheduling(int deadline[], int profit[], int n, int* job_count, int* total_profit) {
    Job *jobs = (Job*)malloc(n * sizeof(Job));
    int i, j;

    for (i = 0; i < n; i++) {
        jobs[i].profit = profit[i];
        jobs[i].deadline = deadline[i];
    }

    qsort(jobs, n, sizeof(Job), cmp);

    int max_deadline = 0;
    for (i = 0; i < n; i++) {
        if (jobs[i].deadline > max_deadline) max_deadline = jobs[i].deadline;
    }

    int *slot = (int*)calloc(max_deadline + 1, sizeof(int));
    
    *job_count = 0;
    *total_profit = 0;

    for (i = 0; i < n; i++) {
        for (j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == 0) {
                slot[j] = 1; 
                *job_count += 1;
                *total_profit += jobs[i].profit;
                break;
            }
        }
    }

    free(jobs);
    free(slot);
}

int main() {
    int deadline1[] = {4, 1, 1, 1};
    int profit1[] = {20, 10, 40, 30};
    int n1 = sizeof(deadline1)/sizeof(deadline1[0]);
    int count1, total1;
    jobScheduling(deadline1, profit1, n1, &count1, &total1);
    printf("[%d, %d]\n", count1, total1);

    int deadline2[] = {2, 1, 2, 1, 1};
    int profit2[] = {100, 19, 27, 25, 15};
    int n2 = sizeof(deadline2)/sizeof(deadline2[0]);
    int count2, total2;
    jobScheduling(deadline2, profit2, n2, &count2, &total2);
    printf("[%d, %d]\n", count2, total2); 

    int deadline3[] = {3, 1, 2, 2};
    int profit3[] = {50, 10, 20, 30};
    int n3 = sizeof(deadline3)/sizeof(deadline3[0]);
    int count3, total3;
    jobScheduling(deadline3, profit3, n3, &count3, &total3);
    printf("[%d, %d]\n", count3, total3); 

    return 0;
}

