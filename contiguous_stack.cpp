#include <iostream>

using std::cout;
using std::endl;

struct elem {
    int name;
};

class ContiguousStack {
    public:
        ContiguousStack ( );
        void initialize(int size);
        void push(elem &e);
        void pop ( );
        void clear ( );
        int binary_search(elem &e);
        int linear_search(elem &e);
    private:
        int size, n;
        elem *stack;
};

ContiguousStack::ContiguousStack ( ) {
    n = size = 0;
    stack = NULL;
}

void ContiguousStack::initialize(int size) {
    if (size <= 0) {
        cout << "Error: invalid size!" << endl;
        return;
    }
    else {
        stack = (elem *) malloc((size + 1) * sizeof(elem));
        if (stack == NULL) {
            cout << "Error: out of memory!" << endl;
            return;
        }
        this->size = size;
    }
}

void ContiguousStack::clear ( ) {
    if (stack == NULL) {
        cout << "Error: stack already cleared" << endl;
        return;
    }
    else {
        free(stack);
        stack = NULL;
        n = size = 0;
    }
}

void ContiguousStack::push(elem &e) {
    if (n == size) {
        cout << "Error: stack is full!" << endl;
        return;
    }
    else
        stack[++n] = e;
}

void ContiguousStack::pop ( ) {
    if (stack == NULL) {
        cout << "Error: stack is cleared" << endl;
        return;
    }
    else if (n == 0) {
        cout << "Error: stack is empty!" << endl;
        return;
    }
    else
        n--;
}

int ContiguousStack::binary_search(elem &e) {
    bool found = false;
    int i = 1, f = n, m;
    do {
        m = (i + f) / 2;
        if (stack[m].name < e.name)
            f = m - 1;
        else if (stack[m].name > e.name)
            i = m + 1;
        else
            found = true;
    } while (!found && i <= f);
    if (!found) {
        cout << "Element not found!" << endl;
        return 0;
    }
    else
        return m;
}

int ContiguousStack::linear_search(elem &e) {
    int i;
    for (i = 1; i <= n && e.name != stack[i].name; i++);
    if (i <= n)
        return i;
    else
        return 0;
}

