---
title: Lista o ograniczonej pojemności
subtitle: Programowanie systemowe i współbieżne
author: Jagoda Wesołowska 159352 \ <<jagoda.wesolowska@student.put.poznan.pl>\>
date: v1.0, 2025-22-01
lang: pl-PL
---

Projekt dostępny w repozytorium pod adresem:
<https://github.com/Jagoda2385/ProjektPSW>


# Struktury danych

1. **Struktura `Node`** – definiuje węzeł listy:

   ```c
   struct Node {
       void *data;
       struct Node *next;
   };
   ```

2. **Struktura `TList`** – przechowuje listę i mechanizmy synchronizacji:

   ```c
   typedef struct {
       Node *head;
       Node *tail;
       int count;
       int maxSize;
       pthread_mutex_t lock;
       pthread_cond_t not_empty;
       pthread_cond_t not_full;
   } TList;
   ```

---

# Funkcje 

1. **Tworzenie listy**:
   ```c
   TList *createList(int size);
   ```
   - Tworzy nową listę FIFO o maksymalnej pojemności `size`.

2. **Dodawanie elementu**:
   ```c
   void putItem(TList* list, void *el);
   ```
   - Dodaje nowy element na koniec listy.
   - Jeśli lista jest pełna, **czeka na zwolnienie miejsca**.

3. **Pobieranie pierwszego elementu**:
   ```c
   void* getItem(TList* list);
   ```
   - Usuwa i zwraca pierwszy (najstarszy) element z listy.
   - Jeśli lista jest pusta, **czeka na nowy element**.

4. **Usuwanie konkretnego elementu**:
   ```c
   int removeItem(TList* list, void *el);
   ```
   - Usuwa z listy element wskazywany przez `el`.

5. **Zmiana maksymalnego rozmiaru listy**:
   ```c
   void setMaxSize(TList* list, int n);
   ```
   - Ustawia nowy maksymalny rozmiar listy FIFO.

6. **Łączenie dwóch list**:
   ```c
   void appendItems(TList* list, TList* list2);
   ```
   - Przenosi wszystkie elementy z `list2` do `list`.

7. **Usunięcie listy**:
   ```c
   void destroyList(TList* list);
   ```
   - Zwalnia pamięć listy i jej elementów.

8. **Wyświetlenie listy**:
   ```c
   void showList(TList* list);
   ```
   - Wypisuje zawartość listy.

---

# Algorytm / dodatkowy opis

1. **FIFO (First-In, First-Out)** – elementy są pobierane w kolejności dodania.
2. **Synchronizacja wątków** – mechanizmy:
   - **Mutex (`pthread_mutex_t`)** – chroni dostęp do listy.
   - **Zmienne warunkowe (`pthread_cond_t`)**:
     - `not_empty` – wątki **czekają**, jeśli lista jest pusta.
     - `not_full` – wątki **czekają**, jeśli lista jest pełna.
3. **Obsługa zakleszczeń i głodzenia** – `pthread_cond_signal` powiadamia oczekujące wątki, co pozwala na kontynuację działania, **o ile istnieje aktywny wątek, który usuwa elementy (`getItem`)**. Jeśli żaden wątek nie pobiera elementów z listy, `putItem` **może zablokować się na zawsze**, czekając na zwolnienie miejsca.

# Przykład użycia

**Kod testowy:**
```c
#include <stdio.h>
#include <string.h>
#include "list.h"

int main() {
    TList *list = createList(3);
    char *str1 = strdup("Hello");
    char *str2 = strdup("World");
    char *str3 = strdup("!");
    
    putItem(list, str1);
    putItem(list, str2);
    putItem(list, str3);
    showList(list);
    
    char *item = (char *)getItem(list);
    printf("Usunięto: %s\n", item);
    free(item);
    
    destroyList(list);
    return 0;
}
```

**Kompilacja i uruchomienie:**
```sh
gcc main.c list.c -o program -lpthread
./program
```

**Oczekiwany wynik:**
```
List contents: "Hello" "World" "!"
Usunięto: Hello
```

---

