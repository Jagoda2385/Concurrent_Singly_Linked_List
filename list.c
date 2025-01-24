#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int count;
    int maxSize;
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} TList;

TList* createList(int size) {
    TList *list = (TList*)malloc(sizeof(TList));
    if (!list) return NULL;
    list->head = list->tail = NULL;
    list->count = 0;
    list->maxSize = size;
    pthread_mutex_init(&list->lock, NULL);
    pthread_cond_init(&list->not_empty, NULL);
    pthread_cond_init(&list->not_full, NULL);
    return list;
}

void putItem(TList* list, void *el) {
    pthread_mutex_lock(&list->lock);
    while (list->count >= list->maxSize) {
        pthread_cond_wait(&list->not_full, &list->lock);
    }
    
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        pthread_mutex_unlock(&list->lock);
        return;
    }
    newNode->data = el;
    newNode->next = NULL;
    
    if (list->tail) {
        list->tail->next = newNode;
    } else {
        list->head = newNode;
    }
    list->tail = newNode;
    list->count++;
    
    pthread_cond_signal(&list->not_empty);
    pthread_mutex_unlock(&list->lock);
}

void* getItem(TList* list) {
    pthread_mutex_lock(&list->lock);
    while (list->count == 0) {
        pthread_cond_wait(&list->not_empty, &list->lock);
    }
    
    Node *oldNode = list->head;
    void *data = oldNode->data;
    list->head = oldNode->next;
    if (!list->head) {
        list->tail = NULL;
    }
    free(oldNode);
    list->count--;
    
    pthread_cond_signal(&list->not_full);
    pthread_mutex_unlock(&list->lock);
    return data;
}

int removeItem(TList* list, void *el) {
    pthread_mutex_lock(&list->lock);
    Node *current = list->head, *prev = NULL;
    while (current) {
        if (current->data == el) {
            if (prev) {
                prev->next = current->next;
            } else {
                list->head = current->next;
            }
            if (!current->next) {
                list->tail = prev;
            }
            free(current->data); 
            free(current);
            list->count--;
            pthread_cond_signal(&list->not_full);
            pthread_mutex_unlock(&list->lock);
            return 1;
        }
        prev = current;
        current = current->next;
    }
    pthread_mutex_unlock(&list->lock);
    return 0;
}

int getCount(TList* list) {
    pthread_mutex_lock(&list->lock);
    int count = list->count;
    pthread_mutex_unlock(&list->lock);
    return count;
}

void setMaxSize(TList* list, int n) {
    pthread_mutex_lock(&list->lock);
    list->maxSize = n;
    pthread_cond_broadcast(&list->not_full);
    pthread_mutex_unlock(&list->lock);
}

void appendItems(TList* list, TList* list2) {
    pthread_mutex_lock(&list->lock);
    pthread_mutex_lock(&list2->lock);
    if (list2->head) {
        if (list->tail) {
            list->tail->next = list2->head;
        } else {
            list->head = list2->head;
        }
        list->tail = list2->tail;
        list->count += list2->count;
        list2->head = list2->tail = NULL;
        list2->count = 0;
    }
    pthread_cond_broadcast(&list->not_empty); 
    pthread_mutex_unlock(&list2->lock);
    pthread_mutex_unlock(&list->lock);
}

void destroyList(TList* list) {
    pthread_mutex_lock(&list->lock);
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    pthread_mutex_destroy(&list->lock);
    pthread_cond_destroy(&list->not_empty);
    pthread_cond_destroy(&list->not_full);
    free(list);
}

void showList(TList* list) {
    pthread_mutex_lock(&list->lock);
    Node *current = list->head;
    printf("List contents: ");
    while (current) {
        if (current->data) {
            printf("\"%s\" ", (char*)current->data);
        } else {
            printf("NULL ");
        }
        current = current->next;
    }
    printf("\n");
    pthread_mutex_unlock(&list->lock);
}

