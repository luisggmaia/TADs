#include <iostream>

using std::cout;
using std::endl;

struct elem {
    int name;
};

class ContiguousQueue {
    public:
        ContiguousQueue ( );
        void initialize (int size);
        void finalize ( );
        void enqueue (elem &e);
        void dequeue ( );
        void print ( );
    private:
        int i, n, size;
        elem *queue;
};

ContiguousQueue::ContiguousQueue ( ) {
    i = 1;
    n = size = 0;
    queue = NULL;
}

void ContiguousQueue::print ( ) {
    for (int j = i, k = i; j < n + i; j++) {
        cout << queue[k].name << endl;
        k = j % size + 1;
    }
}

void ContiguousQueue::initialize (int size) {
    if (size <= 0) {
        cout << "Error: invalid size!" << endl;
        return;
    }
    else {
        queue = (elem *) malloc ((size + 1) * sizeof (elem));
        if (queue == NULL) {
            cout << "Error: out of memory!" << endl;
            return;
        }
        this->size = size;
    }
}

void ContiguousQueue::enqueue (elem &e) {
    if (n == size) {
        cout << "Error: queue full!" << endl;
        return;
    }
    else {
        queue[(i + n - 1) % size + 1] = e;
        n++;
    }
}

void ContiguousQueue::dequeue ( ) {
    if (queue == NULL) {
        cout << "Error: queue is empty" << endl;
        return;
    }
    else if (n == 0) {
        cout << "Error: queue is empty!" << endl;
        return;
    }
    else {
        i = i % size + 1;
        n--;
    }
}

void ContiguousQueue::finalize ( ) {
    if (queue != NULL) {
        free(queue);
        queue = NULL;
        i = n = size = 0;
    }
    else {
        cout << "Error: queue already empty" << endl;
        return;
    }
}
