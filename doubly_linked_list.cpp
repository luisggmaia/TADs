#include <iostream>

using std::cout;
using std::endl;

struct elem {
    int name;
};

typedef struct doubly_node doubly_node;

struct doubly_node {
    elem e;
    doubly_node *prev, *next;
};

class DoublyLinkedList {
    public:
        DoublyLinkedList ( );
        void insert (elem &e);
        void insert_at (elem &e, int position);
        void remove ( );
        void remove_at (int position);
        void finalize ( );
    private:
        int n;
        doubly_node *list;
};

DoublyLinkedList::DoublyLinkedList ( ) {
    n = 0;
    list = NULL;
}

void DoublyLinkedList::insert (elem &e) {
    doubly_node *p = (doubly_node *) malloc (sizeof (doubly_node));
    if (p == NULL) {
        cout << "Error: out of memory!" << endl;
        return;
    }
    p->e = e;
    if (list == NULL)
        list->prev = list = p;
    else {
        p->prev = list->prev;
        p->next = list;
        list->prev = list->prev->next = p;
    }
}

void DoublyLinkedList::insert_at (elem &e, int position) {
    if (position < 1 || position > n + 1) {
        cout << "Error: invalid position!" << endl;
        return;
    }
    else {
        doubly_node *p = (doubly_node *) malloc (sizeof (doubly_node));
        if (p == NULL) {
            cout << "Error: out of memory!" << endl;
            return;
        }
        p->e = e;
        if (position == 1) {
            p->next = list;
            list = p;
            list->prev = list->next->prev;
        }
        else {
            p->next = list;
            for (int i = 1; i < position; i++)
                p->next = p->next->next;
            p->next->prev->next = p->next->prev = p;
        }
        if (list->prev->next != list)
            list->prev->next = list;
        n++;
    }
}

void DoublyLinkedList::remove ( ) {
    if (list == NULL) {
        cout  << "Error: empty list" << endl;
        return;
    }
    else {
        if (list->next == NULL) {
            free (list);
            list = NULL;
            n = 0;
        }
        else {
            list->prev = list->prev->prev;
            free (list->prev->next);
            list->prev->next = list;
            n--;
        }
    }
}

void DoublyLinkedList::remove_at (int position) {
    if (position < 1 || position > n + 1) {
        cout << "Error: invalid position!" << endl;
        return;
    }
    else if (list == NULL) {
        cout  << "Error: empty list" << endl;
        return;
    }
    else {
        if (position == 1) {
            list = list->next;
            free (list->next);
            n--;
        }
        else {
            doubly_node *aux = list;
            for (int i = 1; i < position; i++)
                aux = aux->next;
            aux->prev->next = aux->next;
            aux->next->prev = aux->prev;
            free (aux);
            n--;
        }
    }
}

void DoublyLinkedList::finalize ( ) {
    if (list == NULL) {
        cout  << "Error: empty list" << endl;
        return;
    }
    else {
        do {
            list = list->next;
            free (list->prev);
        } while (list->next != NULL);
        free (list);
        list = NULL;
        n = 0;
    }
}

