#include <iostream>

using std::cout;
using std::endl;

struct elem {
    int name;
};

class ContiguousDeque {
    public:
        ContiguousDeque ( );
        void initialize ( );
        void finalize ( );
        void insert_front(elem &e);
        void insert_back(elem &e);
        void remove_front ( );
        void remove_back ( );
    private:
        int front, back, size, capacity;
        elem *deque;
};

ContiguousDeque::ContiguousDeque ( ) {
    front = 1;
    size = capacity = 0;
    deque = NULL;
}

void ContiguousDeque::initialize ( ) {
    if (capacity <= 0) {
        cout << "Error: invalid capacity!" << endl;
        return;
    }
    else {
        deque = (elem *) malloc((capacity + 1) * sizeof(elem));
        if (deque == NULL) {
            cout << "Error: out of memory!" << endl;
            return;
        }
        this->capacity = capacity;
    }
}

void ContiguousDeque::finalize ( ) {
    if (deque != NULL) {
        free(deque);
        deque = NULL;
        front = size = capacity = 0;
    }
    else {
        cout << "Error: deque is already cleared!" << endl;
        return;
    }
}

void ContiguousDeque::insert_front(elem &e) {
    if (size == capacity) {
        cout << "Error: deque is full!" << endl;
        return;
    }
    else {
        front--;
        if (front == 0)
            front = capacity;
        deque[front] = e;
        size++;
    }
}

void ContiguousDeque::insert_back(elem &e) {
    if (size == capacity) {
        cout << "Error: deque is full!" << endl;
        return;
    }
    else {
        deque[(front + size - 1) % capacity + 1] = e;
        size++;
    }
}

void ContiguousDeque::remove_front ( ) {
    if (deque == NULL) {
        cout << "Error: deque is cleared!" << endl;
        return;
    }
    else if (size == 0) {
        cout << "Error: deque is empty!" << endl;
        return;
    }
    else {
        front = front % capacity + 1;
        size--;
    }
}

void ContiguousDeque::remove_back ( ) {
    if (deque == NULL) {
        cout << "Error: deque is cleared!" << endl;
        return;
    }
    else if (size == 0) {
        cout << "Error: deque is empty!" << endl;
        return;
    }
    else
        size--;
}

