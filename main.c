#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "list.h"

int main() {
    // Tworzenie listy o maksymalnym rozmiarze 5
    TList* list = createList(5);
    if (!list) {
        printf("Nie udało się utworzyć listy.\n");
        return 1;
    }

    // Dodawanie elementów do listy
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

    // Pobieranie elementów z listy
    for (int i = 0; i < 2; i++) {
        char *retrieved = (char*)getItem(list);
        if (retrieved) {
            printf("Pobrano: %s\n", retrieved);
            free(retrieved);
        }
    }
    showList(list);

    // Usuwanie elementu z listy
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

    // Sprawdzanie liczby elementów na liście
    printf("Aktualna liczba elementów: %d\n", getCount(list));

    // Zmiana maksymalnego rozmiaru listy
    setMaxSize(list, 10);
    printf("Nowy maksymalny rozmiar listy ustawiony.\n");

    // Tworzenie drugiej listy i dodawanie elementów
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

    // Przenoszenie elementów z listy2 do listy
    appendItems(list, list2);
    printf("Lista po dodaniu elementów z listy2:\n");
    showList(list);

    // Usuwanie listy
    destroyList(list);
    destroyList(list2);
    printf("Listy zostały usunięte.\n");

    return 0;
}
