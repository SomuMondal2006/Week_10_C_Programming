//Longest valid parentheses
//https://www.geeksforgeeks.org/problems/longest-valid-parentheses5657/1



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int longestValidParentheses(char *s) {
    int n = strlen(s);
    int *stack = (int *)malloc((n + 1) * sizeof(int));
    int top = 0;
    int max_len = 0;
    int i;

    stack[top] = -1;

    for (i = 0; i < n; i++) {
        if (s[i] == '(') {
            top++;
            stack[top] = i;
        } else {
            top--;
            if (top < 0) {
                top = 0;
                stack[top] = i;
            } else {
                int len = i - stack[top];
                if (len > max_len) max_len = len;
            }
        }
    }

    free(stack);
    return max_len;
}

int main() {
    char s1[] = "((()";
    char s2[] = ")()())";
    char s3[] = "())()";

    printf("%d\n", longestValidParentheses(s1));
    printf("%d\n", longestValidParentheses(s2)); 
    printf("%d\n", longestValidParentheses(s3)); 

    return 0;
}

