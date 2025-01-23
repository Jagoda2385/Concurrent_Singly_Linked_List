#ifndef LIST_H
#define LIST_H

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
    Node *head;
    Node *tail;
    int count;
    int maxSize;
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} TList;

TList *createList(int s);

void destroyList(TList *lst);

void putItem(TList *lst, void *itm);

void *getItem(TList *lst);

int removeItem(TList *lst, void *itm);

int getCount(TList *lst);

void setMaxSize(TList *lst, int s);

void appendItems(TList *lst, TList *lst2);

void showList(TList *lst);

#endif // LIST_H
