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

class LinkedQueue {
    public:
        LinkedQueue ( );
        void enqueue(elem &e);
        void dequeue ( );
        void finalize ( );
        void print ( );
    private:
        no *queue_start, *queue_end;
};

LinkedQueue::LinkedQueue ( ) {
    queue_end = queue_start = NULL;
}

void LinkedQueue::print ( ) {
    no *auxiliary = queue_start;
    while (auxiliary != NULL) {
        cout << auxiliary->e.name << endl;
        auxiliary = auxiliary->p;
    }
}

void LinkedQueue::enqueue(elem &e) {
    no *p = (no *) malloc(sizeof(no));
    if (p == NULL) {
        cout << "Error: out of memory!" << endl;
        return;
    }
    p->e = e;
    p->p = NULL;
    if (queue_end == NULL)
        queue_end = queue_start = p;
    else
        queue_end = queue_end->p = p;
}

void LinkedQueue::dequeue ( ) {
    if (queue_start == NULL) {
        cout << "Error: queue is empty" << endl;
        return;
    }
    else {
        if (queue_start->p == NULL) {
            free(queue_start);
            queue_end = queue_start = NULL;
        }
        else {
            no *auxiliary = queue_start;
            queue_start = queue_start->p;
            free(auxiliary);
        }
    }
}

void LinkedQueue::finalize ( ) {
    if (queue_start == NULL) {
        cout << "Error: queue is already empty" << endl;
        return;
    }
    else {
        no *auxiliary;
        do {
            auxiliary = auxiliary->p;
            free(queue_start);
            queue_start = auxiliary;
        } while (queue_start != NULL);
        queue_end = NULL;
    }
}

