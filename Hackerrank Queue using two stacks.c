//Hackerrank: Queue using two stacks
//https://www.hackerrank.com/challenges/queue-using-two-stacks/problem



#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int top;
    unsigned int capacity;
    int* array;
} Stack;

Stack* createStack(unsigned int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) return NULL;
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int item) {
    stack->array[++stack->top] = item;
}

int pop(Stack* stack) {
    return stack->array[stack->top--];
}

int peek(Stack* stack) {
    return stack->array[stack->top];
}

void freeStack(Stack* stack) {
    free(stack->array);
    free(stack);
}

int main() {
    int q;
    scanf("%d", &q);

    Stack* stack_enqueue = createStack(q);
    Stack* stack_dequeue = createStack(q);

    int i; 

    for (i = 0; i < q; i++) { 
        int type;
        scanf("%d", &type);

        if (type == 1) {
            int value;
            scanf("%d", &value);
            push(stack_enqueue, value);
        } else {
            if (isEmpty(stack_dequeue)) {
                while (!isEmpty(stack_enqueue)) {
                    push(stack_dequeue, pop(stack_enqueue));
                }
            }
            
            if (type == 2) {
                pop(stack_dequeue);
            } else {
                printf("%d\n", peek(stack_dequeue));
            }
        }
    }

    freeStack(stack_enqueue);
    freeStack(stack_dequeue);

    return 0;
}
