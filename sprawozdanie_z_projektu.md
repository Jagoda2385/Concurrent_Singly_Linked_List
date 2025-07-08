---
title:    Implementacja współbieżnej listy jednokierunkowej w języku C
subtitle: Programowanie systemowe i współbieżne
author:   Jagoda Wesołowska| Jagoda2385
date:     v1.1, 2025-01-27
lang:     pl-PL
---

Projekt jest dostępny w repozytorium pod adresem:  
<https://github.com/Jagoda2385/ProjektPSW>.

# Struktury danych

W implementacji zastosowano dynamiczną współbieżną listę jednokierunkową zarządzaną za pomocą mutexów oraz zmiennych warunkowych. Struktury danych użyte w implementacji to:

1. Struktura `Node` reprezentująca pojedynczy element listy:
   
   ```C
   typedef struct Node {
       void *data;
       struct Node *next;
   } Node;
   ```
   
2. Struktura `TList` opisująca całą listę oraz mechanizmy synchronizacji:
   
   ```C
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
   ```
   
3. Lista umożliwia dynamiczne dodawanie, pobieranie i usuwanie elementów oraz zmianę jej maksymalnego rozmiaru.

# Funkcje

Poniżej przedstawiono opis kluczowych funkcji dostępnych w implementacji:

1. `TList* createList(int ListSize)` – Tworzy nową listę o maksymalnym rozmiarze `ListSize`, inicjalizuje zmienne synchronizacyjne.

2. `void destroyList(TList* list)` – Niszczy listę, zwalniając zasoby oraz zapewniając synchronizację wątków.

3. `void putItem(TList* list, void *el)` – Dodaje nowy element `el` do listy, blokując operację w przypadku przepełnienia.

4. `void* getItem(TList* list)` – Pobiera pierwszy element listy, blokując wątek, jeśli lista jest pusta.

5. `void* popItem(TList* list)` – Pobiera ostatni element listy, zapewniając synchronizację.

6. `int removeItem(TList* list, void *el)` – Usuwa element `el` z listy, jeśli istnieje.

7. `int getCount(TList* list)` – Zwraca aktualną liczbę elementów w liście.

8. `void setMaxSize(TList* list, int n)` – Ustawia maksymalny rozmiar listy `n`.

9. `void appendItems(TList* list, TList* list2)` – Kopiuje elementy z listy `list2` do `list`, jeśli ilość elementów mieści się w limicie.

10. `void showList(TList* list)` – Wypisuje zawartość listy na standardowe wyjście.

# Mechanizmy synchronizacji

Lista współbieżna wykorzystuje następujące mechanizmy synchronizacji:

- **Mutexy (`pthread_mutex_t`)** – Zapewniają wzajemne wykluczanie operacji na liście.
- **Zmienne warunkowe (`pthread_cond_t`)** – Synchronizują operacje dodawania i pobierania elementów, umożliwiając blokowanie wątków w przypadku pustej lub pełnej listy.

# Obsługa sytuacji skrajnych

Lista obsługuje następujące sytuacje skrajne:

- **Pusta lista** – Wątki pobierające elementy są blokowane do momentu pojawienia się nowego elementu.
- **Pełna lista** – Wątki dodające nowe elementy czekają, aż zwolni się miejsce.
- **Usuwanie elementów** – Operacje na liście są zabezpieczone przed usunięciem elementów podczas ich przetwarzania.

# Przykładowe użycie

Przykład inicjalizacji listy i operacji na niej:

```C
TList *list = createList(5);
char *data1 = strdup("Element 1");
putItem(list, data1);
showList(list);
char *retrieved = (char*)getItem(list);
printf("Pobrano: %s\n", retrieved);
free(retrieved);
destroyList(list);
```

# Podsumowanie

Zaimplementowana struktura współbieżnej listy jednokierunkowej wykorzystuje mechanizmy synchronizacji w języku C. Kod obsługuje sytuacje skrajne oraz pozwala na dynamiczne zarządzanie pamięcią i synchronizację wątków.

