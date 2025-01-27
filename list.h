#ifndef LCL_LIST_H
#define LCL_LIST_H

// ==============================================
//
//  Version 1.0, 2025-01-15
//
// ==============================================

#include <pthread.h>

struct Node {
    void *data;
    struct Node *next;
};

typedef struct Node Node;

typedef struct TList {
    Node *first_element;
    Node *last_element;
    int num_of_elements;
    int maxSize;
    int destroy;
    int active_threads;
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
    pthread_cond_t no_active_threads;
} TList;

TList* createList(int s);

void destroyList(TList* lst);

void putItem(TList* lst, void* itm);

void* getItem(TList* lst);

void* popItem(TList* lst);

int removeItem(TList* lst, void* itm);

int getCount(TList* lst);

void setMaxSize(TList* lst, int s);

void appendItems(TList* lst, TList* lst2);

void showList(TList* lst);

#endif //LCL_LIST_H
