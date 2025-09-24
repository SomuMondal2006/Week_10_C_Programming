//Minimum platforms required
//https://www.geeksforgeeks.org/problems/minimum-platforms-1587115620/1



#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int minPlatforms(int arr[], int dep[], int n) {
    qsort(arr, n, sizeof(int), cmp);
    qsort(dep, n, sizeof(int), cmp);

    int plat_needed = 1, max_plat = 1;
    int i = 1, j = 0;

    while (i < n && j < n) {
        if (arr[i] <= dep[j]) {
            plat_needed++;
            if (plat_needed > max_plat) max_plat = plat_needed;
            i++;
        } else {
            plat_needed--;
            j++;
        }
    }

    return max_plat;
}

int main() {
    int arr1[] = {900, 940, 950, 1100, 1500, 1800};
    int dep1[] = {910, 1200, 1120, 1130, 1900, 2000};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);
    printf("%d\n", minPlatforms(arr1, dep1, n1)); 

    int arr2[] = {900, 1235, 1100};
    int dep2[] = {1000, 1240, 1200};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    printf("%d\n", minPlatforms(arr2, dep2, n2)); 

    int arr3[] = {1000, 935, 1100};
    int dep3[] = {1200, 1240, 1130};
    int n3 = sizeof(arr3)/sizeof(arr3[0]);
    printf("%d\n", minPlatforms(arr3, dep3, n3)); 

    return 0;
}

