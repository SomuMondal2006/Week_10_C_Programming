//Hackerrank: Simple text editor
//https://www.hackerrank.com/challenges/simple-text-editor/problem



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TOTAL_LEN 1000001
#define MAX_OPS 1000001

typedef enum {
    APPEND_OP = 1,
    DELETE_OP = 2
} OpType;

typedef struct {
    OpType type;
    union {
        int length; 
        char* text; 
    } data;
} Operation;

char S[MAX_TOTAL_LEN];
int S_len = 0;

Operation history[MAX_OPS];
int history_top = -1;

char W[MAX_TOTAL_LEN];

int main() {
    int Q;
    scanf("%d", &Q);

    int i;
    for (i = 0; i < Q; i++) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            scanf("%s", W);
            int w_len = strlen(W);

            history_top++;
            history[history_top].type = APPEND_OP;
            history[history_top].data.length = w_len;

            memcpy(&S[S_len], W, w_len);
            S_len += w_len;
            S[S_len] = '\0'; 

        } else if (type == 2) {
            int k;
            scanf("%d", &k);
            history_top++;
            history[history_top].type = DELETE_OP;
            history[history_top].data.text = (char*)malloc(k + 1);
            memcpy(history[history_top].data.text, &S[S_len - k], k);
            history[history_top].data.text[k] = '\0';

            S_len -= k;
            S[S_len] = '\0';

        } else if (type == 3) {
            int k;
            scanf("%d", &k);
            printf("%c\n", S[k - 1]);
        
        } else { 
            Operation last_op = history[history_top--];

            if (last_op.type == APPEND_OP) {
                S_len -= last_op.data.length;
                S[S_len] = '\0';
            } else { 
                int text_len = strlen(last_op.data.text);
                memcpy(&S[S_len], last_op.data.text, text_len);
                S_len += text_len;
                S[S_len] = '\0';
                free(last_op.data.text);
            }
        }
    }

    for (i = 0; i <= history_top; ++i) {
        if (history[i].type == DELETE_OP) {
            free(history[i].data.text);
        }
    }

    return 0;
}
