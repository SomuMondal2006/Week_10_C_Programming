//Largest rectangle in histogram
//https://www.geeksforgeeks.org/problems/maximum-rectangular-area-in-a-histogram-1587115620/1



#include <stdio.h>
#include <stdlib.h>

int largestRectangleArea(int arr[], int n) {
    int stack[100000]; 
    int top = -1;
    int max_area = 0;
    int i;

    for (i = 0; i <= n; i++) {
        int h = (i == n) ? 0 : arr[i];
        while (top >= 0 && arr[stack[top]] > h) {
            int height = arr[stack[top--]];
            int width;
            if (top == -1) width = i;
            else width = i - stack[top] - 1;
            int area = height * width;
            if (area > max_area) max_area = area;
        }
        stack[++top] = i;
    }

    return max_area;
}

int main() {
    int arr1[] = {60, 20, 50, 40, 10, 50, 60};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);
    printf("%d\n", largestRectangleArea(arr1, n1)); 

    int arr2[] = {3, 5, 1, 7, 5, 9};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    printf("%d\n", largestRectangleArea(arr2, n2)); 

    int arr3[] = {3};
    int n3 = sizeof(arr3)/sizeof(arr3[0]);
    printf("%d\n", largestRectangleArea(arr3, n3)); 

    return 0;
}

