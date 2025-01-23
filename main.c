#include <stdio.h>
#include "list.h"


int main() {
    printf("Tworzenie listy o rozmiarze (5)\n");
    TList *list = createList(5);
    
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    
    printf("Dodawanie elementow \n");
    putItem(list, &a);
    putItem(list, &b);
    putItem(list, &c);
    putItem(list, &d);
    putItem(list, &e);
    showList(list);
    printf("Aktualna liczba elementów: %d\n", getCount(list));
    

    printf("Usuwanie najstarszego elementu z listy\n");
    void *item = getItem(list);
    printf("Retrieved item: %d\n", *(int *)item);
    showList(list);
    printf("Aktualna liczba elementów: %d\n", getCount(list));
    
    printf("Usuwanie z listy elementu (3)\n");
    removeItem(list, &c);
    showList(list);
    printf("Aktualna liczba elementów: %d\n", getCount(list));
    
    printf("Ustalanie nowego maxymalnego rozmiaru listy (3)\n");
    setMaxSize(list, 3);
    
    printf("tworzenie list2 i przenoszenie wszytskich elementow list do list2\n");
    TList *list2 = createList(3);
    int g = 7, h = 8;
    putItem(list2, &g);
    putItem(list2, &h);
    appendItems(list, list2);
    showList(list);
    printf("Aktualna liczba elementów: %d\n", getCount(list));
     
    printf("Usuwanie list2\n");
    destroyList(list2);

    printf("Dodawanie kolejnego elementu do list, operacja blokująca \n");
    putItem(list, &f);
    showList(list);
    
    return 0;
}
