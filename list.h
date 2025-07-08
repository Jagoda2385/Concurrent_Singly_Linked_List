#ifndef LCL_LIST_H
#define LCL_LIST_H

// ==============================================
//
//  Concurrent Singly Linked List (Thread-Safe)
//
//  Version 1.0
//  Date: 2025-01-15
//
//  Author: Jagoda2385
//
//  Description:
//  This header defines the interface for a thread-safe
//  singly linked list implementation using pthreads.
//
// ==============================================

#include <pthread.h>

// Definition of a singly linked list node
typedef struct Node {
    void *data;           // Pointer to data
    struct Node *next;    // Pointer to the next node
} Node;

// Definition of the concurrent singly linked list
typedef struct TList {
    Node *first_element;  // Pointer to the first node
    Node *last_element;   // Pointer to the last node
    int num_of_elements;  // Current number of elements
    int maxSize;          // Maximum allowed size
    int destroy;          // Flag indicating if list is being destroyed
    int active_threads;   // Number of active threads using the list
    pthread_mutex_t lock; // Mutex for thread safety
    pthread_cond_t not_empty;           // Condition variable for non-empty
    pthread_cond_t not_full;            // Condition variable for non-full
    pthread_cond_t no_active_threads;   // Condition variable for destruction
} TList;

// Creates a new list with a given maximum size
TList* createList(int size);

// Frees all resources and destroys the list
void destroyList(TList* list);

// Adds a new item to the list (blocks if full)
void putItem(TList* list, void* item);

// Retrieves and removes the first item from the list (blocks if empty)
void* getItem(TList* list);

// Retrieves and removes the last item from the list (blocks if empty)
void* popItem(TList* list);

// Removes a specific item from the list
int removeItem(TList* list, void* item);

// Returns the current number of elements in the list
int getCount(TList* list);

// Sets a new maximum size for the list
void setMaxSize(TList* list, int size);

// Appends all items from list2 to list1
void appendItems(TList* list, TList* list2);

// Prints the contents of the list
void showList(TList* list);

#endif // LCL_LIST_H
