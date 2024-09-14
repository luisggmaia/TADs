#include <iostream>

using std::cout;
using std::endl;

struct elem {
    int name;
};

struct no {
    elem e;
    no *p;
};

class LinkedStack {
    public:
        LinkedStack ( );
        void push(elem e);
        void pop ( );
        void clear ( );
    private:
        no *stack;
};

LinkedStack::LinkedStack ( ) {
    stack = NULL;
}

void LinkedStack::push(elem e) {
    no *p = (no *) malloc(sizeof(no));
    if (p == NULL) {
        cout << "Error: out of memory!" << endl;
        return;
    }
    else {
        p->e = e;
        p->p = stack;
        stack = p;
    }
}

void LinkedStack::pop ( ) {
    if (stack == NULL) {
        cout << "Error: stack is empty!" << endl;
        return;
    }
    else {
        no *aux = stack;
        stack = stack->p;
        free(aux);
    }
}

void LinkedStack::clear ( ) {
    if (stack == NULL) {
        cout << "Error: stack is already empty!" << endl;
        return;
    }
    else {
        no *aux;
        do {
            aux = stack->p;
            free(stack);
            stack = aux;
        } while (aux != NULL);
    }
}
