#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <ctype.h>

// Definition of a singly linked list node
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

// Definition of the concurrent singly linked list
typedef struct {
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

// Creates a new list with a given maximum size
TList* createList(int ListSize) {
    TList *list = (TList*)malloc(sizeof(TList));
    if (!list) return NULL;

    list->first_element = list->last_element = NULL;
    list->num_of_elements = 0;
    list->maxSize = ListSize;
    list->destroy = 0;
    list->active_threads = 0;

    pthread_mutex_init(&list->lock, NULL);
    pthread_cond_init(&list->not_empty, NULL);
    pthread_cond_init(&list->not_full, NULL);
    pthread_cond_init(&list->no_active_threads, NULL);

    return list;
}

// Frees all resources and destroys the list
void destroyList(TList* list) {
    pthread_mutex_lock(&list->lock);

    list->destroy = 1;
    pthread_cond_broadcast(&list->not_empty);
    pthread_cond_broadcast(&list->not_full);
    pthread_cond_broadcast(&list->no_active_threads);

    while (list->active_threads > 0) {
        pthread_cond_wait(&list->no_active_threads, &list->lock);
    }

    Node *current = list->first_element;
    while (current) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    list->first_element = list->last_element = NULL;
    list->num_of_elements = 0;

    pthread_mutex_unlock(&list->lock);

    pthread_mutex_destroy(&list->lock);
    pthread_cond_destroy(&list->not_empty);
    pthread_cond_destroy(&list->not_full);
    pthread_cond_destroy(&list->no_active_threads);

    free(list);
}

// Adds a new item to the list (blocks if list is full)
void putItem(TList* list, void *el) {
    pthread_mutex_lock(&list->lock);

    if (list->destroy) {
        pthread_mutex_unlock(&list->lock);
        return;
    }

    while (list->num_of_elements >= list->maxSize) {
        if (list->destroy) {
            pthread_mutex_unlock(&list->lock);
            return;
        }
        pthread_cond_wait(&list->not_full, &list->lock);
    }

    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        pthread_mutex_unlock(&list->lock);
        return;
    }

    newNode->data = el;
    newNode->next = NULL;

    if (list->last_element) {
        list->last_element->next = newNode;
    } else {
        list->first_element = newNode;
    }
    list->last_element = newNode;
    list->num_of_elements++;

    pthread_cond_signal(&list->not_empty);
    pthread_mutex_unlock(&list->lock);
}

// Retrieves and removes the first item from the list (blocks if empty)
void* getItem(TList* list) {
    pthread_mutex_lock(&list->lock);

    if (list->destroy) {
        pthread_mutex_unlock(&list->lock);
        return NULL;
    }

    while (list->num_of_elements == 0) {
        if (list->destroy) {
            pthread_mutex_unlock(&list->lock);
            return NULL;
        }
        pthread_cond_wait(&list->not_empty, &list->lock);
    }

    Node *oldNode = list->first_element;
    void *data = oldNode->data;
    list->first_element = oldNode->next;

    if (!list->first_element) {
        list->last_element = NULL;
    }

    free(oldNode);
    list->num_of_elements--;

    pthread_cond_signal(&list->not_full);
    pthread_mutex_unlock(&list->lock);
    return data;
}

// Retrieves and removes the last item from the list (blocks if empty)
void* popItem(TList* list) {
    pthread_mutex_lock(&list->lock);

    if (list->destroy) {
        pthread_mutex_unlock(&list->lock);
        return NULL;
    }

    while (list->num_of_elements == 0) {
        if (list->destroy) {
            pthread_mutex_unlock(&list->lock);
            return NULL;
        }
        pthread_cond_wait(&list->not_empty, &list->lock);
    }

    Node *prev = NULL, *current = list->first_element;
    while (current->next) {
        prev = current;
        current = current->next;
    }

    void *data = current->data;

    if (prev) {
        prev->next = NULL;
        list->last_element = prev;
    } else {
        list->first_element = list->last_element = NULL;
    }

    free(current);
    list->num_of_elements--;

    pthread_cond_signal(&list->not_full);
    pthread_mutex_unlock(&list->lock);
    return data;
}

// Removes a specific item from the list
int removeItem(TList* list, void *el) {
    pthread_mutex_lock(&list->lock);

    if (list->destroy) {
        pthread_mutex_unlock(&list->lock);
        return 0;
    }

    Node *current = list->first_element, *prev = NULL;
    while (current) {
        if (list->destroy) {
            pthread_mutex_unlock(&list->lock);
            return 0;
        }

        if (current->data == el) {
            if (prev) {
                prev->next = current->next;
            } else {
                list->first_element = current->next;
            }

            if (!current->next) {
                list->last_element = prev;
            }

            free(current->data);
            free(current);
            list->num_of_elements--;

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

// Returns the current number of elements in the list
int getCount(TList* list) {
    pthread_mutex_lock(&list->lock);

    if (list->destroy) {
        pthread_mutex_unlock(&list->lock);
        return 0;
    }

    int num_of_elements = list->num_of_elements;
    pthread_mutex_unlock(&list->lock);
    return num_of_elements;
}

// Sets a new maximum size for the list
void setMaxSize(TList* list, int n) {
    pthread_mutex_lock(&list->lock);

    if (list->destroy) {
        pthread_mutex_unlock(&list->lock);
        return;
    }

    list->maxSize = n;
    pthread_cond_broadcast(&list->not_full);

    pthread_mutex_unlock(&list->lock);
}

// Appends all items from list2 to list1
void appendItems(TList* list, TList* list2) {
    pthread_mutex_lock(&list->lock);
    pthread_mutex_lock(&list2->lock);

    if (list->destroy || list2->destroy) {
        pthread_mutex_unlock(&list2->lock);
        pthread_mutex_unlock(&list->lock);
        return;
    }

    if (list2->first_element) {
        if (list->last_element) {
            list->last_element->next = list2->first_element;
        } else {
            list->first_element = list2->first_element;
        }

        list->last_element = list2->last_element;
        list->num_of_elements += list2->num_of_elements;

        list2->first_element = list2->last_element = NULL;
        list2->num_of_elements = 0;

        pthread_cond_broadcast(&list->not_empty);
        pthread_cond_broadcast(&list2->not_full);
    }

    pthread_mutex_unlock(&list2->lock);
    pthread_mutex_unlock(&list->lock);
}

// Prints the contents of the list
void showList(TList* list) {
    pthread_mutex_lock(&list->lock);
    Node *current = list->first_element;
    printf("List: ");
    while (current) {
        printf("\"%s\" ", (char*)current->data);
        current = current->next;
    }
    printf("\n");
    pthread_mutex_unlock(&list->lock);
}
