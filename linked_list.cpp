#include <iostream>

using std::cout;
using std::endl;

struct elem {
    int name;
};

struct node {
    elem e;
    node *p;
};

class LinkedList {
    public:
        LinkedList ( );
        void insert (elem &e);
        void insert_at (elem &e, int position);
        void remove ( );
        void remove_at (int position);
        void finalize ( );
        void print ( );
    private:
        int n;
        node *head, *tail;
};

LinkedList::LinkedList ( ) {
    n = 0;
    tail = head = NULL;
}

void LinkedList::print ( ) {
    node *aux = head;
    while (aux != NULL) {
        cout << aux->e.name << endl;
        aux = aux->p;
    }
}

void LinkedList::insert (elem &e) {
    node *p = (node *) malloc (sizeof (node));
    if (p == NULL) {
        cout << "Error: out of memory!" << endl;
        return;
    }
    p->e = e;
    p->p = NULL;
    if (tail == NULL)
        tail = head = p;
    else
        tail = tail->p = p;
    n++;
}

void LinkedList::insert_at (elem &e, int position) {
    if (position < 1 || position > n + 1) {
        cout << "Error: invalid position!" << endl;
        return;
    }
    else {
        node *p = (node *) malloc (sizeof (node));
        if (p == NULL) {
            cout << "Error: out of memory!" << endl;
            return;
        }
        p->e = e;
        if (position == 1) {
            p->p = head;
            head = p;
            if (tail == NULL)
                tail = p;
        }
        else {
            node *aux = head;
            for (int i = 1; i < position - 1; i++)
                aux = aux->p;
            p->p = aux->p;
            aux->p = p;
        }
        if (tail->p != NULL)
            tail = tail->p;
        n++;
    }
}

void LinkedList::remove ( ) {
    if (head == NULL) {
        cout  << "Error: empty list" << endl;
        return;
    }
    else {
        if (head->p == NULL) {
            free (head);
            head = tail = NULL;
            n = 0;
        }
        else {
            node *aux = head;
            while (aux->p->p != NULL)
                aux = aux->p;
            free (aux->p);
            aux->p = NULL;
            n--;
        }
    }
}

void LinkedList::remove_at (int position) {
    if (position < 1 || position > n + 1) {
        cout << "Error: invalid position!" << endl;
        return;
    }
    else if (head == NULL) {
        cout  << "Error: empty list" << endl;
        return;
    }
    else {
        node *auxA = head;
        if (position == 1) {
            head = head->p;
            free (auxA);
            if (head == NULL)
                tail = NULL;
            n--;
        }
        else {
            node *auxB;
            for (int i = 1; i < position - 1; i++)
                auxA = auxA->p;
            auxB = auxA->p;
            if (auxB == tail)
                tail = auxA;
            auxA->p = auxA->p->p;
            free (auxB);
            n--;
        }
    }
}

void LinkedList::finalize ( ) {
    if (head == NULL) {
        cout  << "Error: empty list" << endl;
        return;
    }
    else {
        node *aux;
        do {
            aux = head->p;
            free (head);
            head = aux;
        } while (head != NULL);
        tail = NULL;
        n = 0;
    }
}
