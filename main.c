#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "lcl_list.h"

int main() {
    // Create a new list with initial max size of 5
    TList* list = createList(5);
    if (!list) {
        printf("Failed to create the list.\n");
        return EXIT_FAILURE;
    }

    // Add initial items to the list
    char *items[] = {"A", "B", "C", "D", "E"};
    for (int i = 0; i < 5; i++) {
        char *item = strdup(items[i]);
        if (!item) {
            printf("Memory allocation error.\n");
            destroyList(list);
            return EXIT_FAILURE;
        }
        putItem(list, item);
        printf("Added: %s\n", item);
    }

    printf("\nCurrent list contents:\n");
    showList(list);

    // Get and remove two items from the list
    for (int i = 0; i < 2; i++) {
        char *string = (char*)getItem(list);
        if (string) {
            printf("Retrieved: %s\n", string);
            free(string);
        }
    }

    printf("\nList after retrieving two items:\n");
    showList(list);

    // Remove a specific item ("D") from the list
    const char *toRemove = "D";
    Node *current = list->first_element;
    int removed = 0;
    while (current) {
        if (strcmp((char*)current->data, toRemove) == 0) {
            removed = removeItem(list, current->data);
            break;
        }
        current = current->next;
    }

    if (removed) {
        printf("Element '%s' was removed.\n", toRemove);
    } else {
        printf("Element '%s' not found.\n", toRemove);
    }

    printf("\nList after removal:\n");
    showList(list);
    printf("Current number of elements: %d\n", getCount(list));

    // Change max size
    setMaxSize(list, 10);
    printf("New max size set to 10.\n");

    // Create a second list and add two items
    TList* list2 = createList(5);
    if (!list2) {
        printf("Failed to create the second list.\n");
        destroyList(list);
        return EXIT_FAILURE;
    }

    char *itemX = strdup("X");
    char *itemY = strdup("Y");
    if (!itemX || !itemY) {
        printf("Memory allocation error.\n");
        free(itemX);
        free(itemY);
        destroyList(list);
        destroyList(list2);
        return EXIT_FAILURE;
    }
    putItem(list2, itemX);
    putItem(list2, itemY);

    printf("\nSecond list before appending:\n");
    showList(list2);

    // Append items from list2 to list
    appendItems(list, list2);
    printf("\nList after appending items from list2:\n");
    showList(list);

    // Pop two items from the list
    for (int i = 0; i < 2; i++) {
        void *poppedItem = popItem(list);
        if (poppedItem) {
            printf("Popped last item: %s\n", (char*)poppedItem);
            free(poppedItem);
        }
        printf("\nList after popping:\n");
        showList(list);
    }

    // Clean up memory
    destroyList(list);
    destroyList(list2);
    printf("\nBoth lists have been deleted.\n");

    return EXIT_SUCCESS;
}
