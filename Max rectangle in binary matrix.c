//Max rectangle in binary matrix
//https://www.geeksforgeeks.org/problems/max-rectangle/1



#include <stdio.h>
#include <stdlib.h>

int maxHistogramArea(int* heights, int m) {
    int stack[1000]; 
    int top = -1;
    int max_area = 0;
    int i;

    for (i = 0; i <= m; i++) {
        int h = (i == m) ? 0 : heights[i];
        while (top >= 0 && heights[stack[top]] > h) {
            int height = heights[stack[top--]];
            int width = (top == -1) ? i : i - stack[top] - 1;
            int area = height * width;
            if (area > max_area) max_area = area;
        }
        stack[++top] = i;
    }
    return max_area;
}

int maximalRectangle(int mat[][1000], int n, int m) {
    int heights[1000];
    int i, c, r;
    for (i = 0; i < m; i++) heights[i] = 0;

    int max_area = 0;

    for (r = 0; r < n; r++) {
        for (c = 0; c < m; c++) {
            if (mat[r][c] == 1) heights[c] += 1;
            else heights[c] = 0;
        }
        {
            int area = maxHistogramArea(heights, m);
            if (area > max_area) max_area = area;
        }
    }
    return max_area;
}

int main() {
    int mat1[4][1000] = {
        {0, 1, 1, 0},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 0, 0}
    };
    printf("Max Area: %d\n", maximalRectangle(mat1, 4, 4));

    int mat2[3][1000] = {
        {0, 1, 1},
        {1, 1, 1},
        {0, 1, 1}
    };
    printf("Max Area: %d\n", maximalRectangle(mat2, 3, 3)); 

    return 0;
}

