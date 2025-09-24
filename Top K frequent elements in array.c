//Top K frequent elements in array
//https://www.geeksforgeeks.org/problems/top-k-frequent-elements-in-array/1



#include <stdio.h>
#include <stdlib.h>

#define MAX 100001

typedef struct {
    int num;
    int freq;
} Element;

int cmp(const void *a, const void *b) {
    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;

    if (e1->freq != e2->freq)
        return e2->freq - e1->freq; 
    return e2->num - e1->num;       
}

void topKFrequent(int arr[], int n, int k) {
    int freq[MAX] = {0};
    int i, distinctCount = 0;

    for (i = 0; i < n; i++) {
        freq[arr[i]]++;
    }

    Element *elements = (Element *)malloc(n * sizeof(Element));
    for (i = 0; i < MAX; i++) {
        if (freq[i] > 0) {
            elements[distinctCount].num = i;
            elements[distinctCount].freq = freq[i];
            distinctCount++;
        }
    }

    qsort(elements, distinctCount, sizeof(Element), cmp);

    for (i = 0; i < k; i++) {
        printf("%d ", elements[i].num);
    }
    printf("\n");

    free(elements);
}

int main() {
    int arr1[] = {3, 1, 4, 4, 5, 2, 6, 1};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int k1 = 2;

    int arr2[] = {7, 10, 11, 5, 2, 5, 5, 7, 11, 8, 9};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 4;

    printf("Example 1:\n");
    topKFrequent(arr1, n1, k1); 

    printf("Example 2:\n");
    topKFrequent(arr2, n2, k2);  

    return 0;
}

