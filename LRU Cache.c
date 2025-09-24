//LRU Cache
//https://www.geeksforgeeks.org/problems/lru-cache/1



#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key, value;
    struct Node *prev, *next;
    struct Node *hnext;
} Node;

typedef struct {
    int capacity;
    int size;
    Node *head, *tail;
    Node **hash; 
    int hashSize;
} LRUCache;

int hashFunc(int key, int hashSize) {
    return key % hashSize;
}

Node* createNode(int key, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->prev = node->next = node->hnext = NULL;
    return node;
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* obj = (LRUCache*)malloc(sizeof(LRUCache));
    obj->capacity = capacity;
    obj->size = 0;
    obj->hashSize = capacity * 10;
    obj->hash = (Node**)calloc(obj->hashSize, sizeof(Node*));

    obj->head = createNode(0, 0);
    obj->tail = createNode(0, 0);
    obj->head->next = obj->tail;
    obj->tail->prev = obj->head;

    return obj;
}

void removeNode(Node* node) {
    Node* prev = node->prev;
    Node* next = node->next;
    prev->next = next;
    next->prev = prev;
}

void addNode(LRUCache* obj, Node* node) {
    Node* prev = obj->tail->prev;
    prev->next = node;
    node->prev = prev;
    node->next = obj->tail;
    obj->tail->prev = node;
}

Node* hashSearch(LRUCache* obj, int key) {
    int idx = hashFunc(key, obj->hashSize);
    Node* cur = obj->hash[idx];
    while (cur) {
        if (cur->key == key) return cur;
        cur = cur->hnext;
    }
    return NULL;
}

void hashInsert(LRUCache* obj, Node* node) {
    int idx = hashFunc(node->key, obj->hashSize);
    node->hnext = obj->hash[idx];
    obj->hash[idx] = node;
}

void hashRemove(LRUCache* obj, Node* node) {
    int idx = hashFunc(node->key, obj->hashSize);
    Node* cur = obj->hash[idx];
    Node* prev = NULL;

    while (cur) {
        if (cur == node) {
            if (prev) prev->hnext = cur->hnext;
            else obj->hash[idx] = cur->hnext;
            return;
        }
        prev = cur;
        cur = cur->hnext;
    }
}

int lRUCacheGet(LRUCache* obj, int key) {
    Node* node = hashSearch(obj, key);
    if (!node) return -1;
    removeNode(node);
    addNode(obj, node);
    return node->value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    Node* node = hashSearch(obj, key);

    if (node) {
        node->value = value;
        removeNode(node);
        addNode(obj, node);
    } else {
        if (obj->size == obj->capacity) {
            Node* lru = obj->head->next;
            removeNode(lru);
            hashRemove(obj, lru);
            free(lru);
            obj->size--;
        }
        Node* newNode = createNode(key, value);
        addNode(obj, newNode);
        hashInsert(obj, newNode);
        obj->size++;
    }
}

void lRUCacheFree(LRUCache* obj) {
    Node* cur = obj->head;
    while (cur) {
        Node* next = cur->next;
        free(cur);
        cur = next;
    }
    free(obj->hash);
    free(obj);
}

void processQueries(int cap, int Q, char queries[][10], int args[][2]) {
    LRUCache* cache = lRUCacheCreate(cap);
    int i;
    for (i = 0; i < Q; i++) {
        if (queries[i][0] == 'P') { /* PUT */
            lRUCachePut(cache, args[i][0], args[i][1]);
        } else { /* GET */
            int res = lRUCacheGet(cache, args[i][0]);
            printf("%d ", res);
        }
    }
    printf("\n");
    lRUCacheFree(cache);
}

int main() {
    int cap = 2, Q = 8;
    char queries[8][10] = {"PUT","PUT","PUT","PUT","PUT","GET","PUT","GET"};
    int args[8][2] = {
        {1,2},{2,3},{1,5},{4,5},{6,7},{4,0},{1,2},{3,0}
    };

    processQueries(cap, Q, queries, args); 
    return 0;
}

