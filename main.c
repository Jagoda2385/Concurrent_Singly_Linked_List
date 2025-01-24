#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "list.h"

int main() {

    TList* list = createList(5);
    if (!list) {
        printf("Nie udało się utworzyć listy.\n");
        return 1;
    }


    char *items[] = {"A", "B", "C", "D", "E"};
    for (int i = 0; i < 5; i++) {
        char *item = strdup(items[i]);
        if (!item) {
            printf("Błąd alokacji pamięci\n");
            return 1;
        }
        putItem(list, item);
        printf("Dodano: %s\n", item);
    }
    showList(list);


    for (int i = 0; i < 2; i++) {
        char *string = (char*)getItem(list);
        if (string) {
            printf("Pobrano: %s\n", string);
            free(string);
        }
    }
    showList(list);

    char toRemove[] = "D";
    Node *current = list->head;
    while (current) {
        if (strcmp((char*)current->data, toRemove) == 0) {
            printf("Usuwanie elementu: %d\n", removeItem(list, current->data));
            break;
        }
        current = current->next;
    }
    showList(list);


    printf("Aktualna liczba elementów: %d\n", getCount(list));

    setMaxSize(list, 10);
    printf("Nowy maksymalny rozmiar listy ustawiony.\n");

    TList* list2 = createList(5);
    if (!list2) {
        printf("Nie udało się utworzyć drugiej listy.\n");
        return 1;
    }
    char *itemX = strdup("X");
    char *itemY = strdup("Y");
    if (!itemX || !itemY) {
        printf("Błąd alokacji pamięci\n");
        return 1;
    }
    putItem(list2, itemX);
    putItem(list2, itemY);
    printf("Lista 2 przed przeniesieniem:\n");
    showList(list2);

    appendItems(list, list2);
    printf("Lista po dodaniu elementów z listy2:\n");
    showList(list);

  
    destroyList(list);
    destroyList(list2);
    printf("Listy zostały usunięte.\n");

    return 0;
}
