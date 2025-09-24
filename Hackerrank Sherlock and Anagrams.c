//Hackerrank: Sherlock and Anagrams
//https://www.hackerrank.com/challenges/sherlock-and-anagrams/problem



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compareChars(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}

int compareStrings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int sherlockAndAnagrams(char* s) {
    int n = strlen(s);
    int num_substrings = n * (n + 1) / 2;
    char** signatures;
    int current_index = 0;
    long long total_pairs = 0;
    int len, i, j; 
    long long consecutive_count; 

    signatures = malloc(num_substrings * sizeof(char*));

    for (len = 1; len <= n; len++) {
        for (i = 0; i <= n - len; i++) {
            signatures[current_index] = malloc((len + 1) * sizeof(char));
            strncpy(signatures[current_index], s + i, len);
            signatures[current_index][len] = '\0';
            qsort(signatures[current_index], len, sizeof(char), compareChars);
            current_index++;
        }
    }

    qsort(signatures, num_substrings, sizeof(char*), compareStrings);

    for (i = 0; i < num_substrings; ) {
        consecutive_count = 1;
        j = i + 1;
        while (j < num_substrings && strcmp(signatures[i], signatures[j]) == 0) {
            consecutive_count++;
            j++;
        }
        total_pairs += consecutive_count * (consecutive_count - 1) / 2;
        i = j;
    }

    for (i = 0; i < num_substrings; i++) {
        free(signatures[i]);
    }
    free(signatures);
    
    return total_pairs;
}

int main() {
    int q;
    int q_itr;
    scanf("%d", &q);
    getchar(); 

    for (q_itr = 0; q_itr < q; q_itr++) {
        char s[102];
        fgets(s, sizeof(s), stdin);
        s[strcspn(s, "\r\n")] = 0; 
        
        int result = sherlockAndAnagrams(s);
        printf("%d\n", result);
    }

    return 0;
}
