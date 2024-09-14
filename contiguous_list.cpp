#include <iostream>

using std::cout;
using std::endl;

struct elem {
    int name;
};

class ContiguousList {
    public:
        ContiguousList ( );
        void initialize (int size);
        void finalize ( );
        void insert (elem &e);
        void insert_at (elem &e, int position);
        void remove ( );
        void remove_at (int position);
        void print ( );
        int binary_position (elem &e);
    private: 
        int n, size;
        elem *list;
        int binary_search (elem &e);
        int linear_search (elem &e);
};

ContiguousList::ContiguousList ( ) {
    n = size = 0;
    list = NULL;
}

void ContiguousList::print ( ) {
    for (int i = 1; i <= n; i++)
        cout << list[i].name << endl;
}

void ContiguousList::initialize (int size) {
    if (size <= 0) {
        cout << "Error: invalid size!" << endl;
        return;
    }
    else {
        list = (elem *) malloc ((size + 1) * sizeof(elem));
        if (list == NULL) {
            cout << "Error: out of memory!" << endl;
            return;
        }
        this->size = size;
    }
}

void ContiguousList::finalize ( ) {
    if (list == NULL) {
        cout << "Error: list already emptied" << endl;
        return;
    }
    else {
        free(list);
        list = NULL;
        n = size = 0;
    }
}

void ContiguousList::insert (elem &e) {
    if (n == size) {
        cout << "Error: list is full!" << endl;
        return;
    }
    else
        list[++n] = e;
}

void ContiguousList::insert_at (elem &e, int position) {
    if (position <= 0 || position > n + 1) {
        cout << "Error: invalid position!" << endl;
        return;
    }
    else if (n == size) {
        cout << "Error: list is full!" << endl;
        return;
    }
    else {
        for (int i = n++; i >= position; i--)
            list[i + 1] = list[i];
        list[position] = e;
    }
}

void ContiguousList::remove ( ) {
    if (list == NULL) {
        cout << "Error: list emptied" << endl;
        return;
    }
    else if (n == 0) {
        cout << "Error: list is empty!" << endl;
        return;
    }
    else
        n--;
}

void ContiguousList::remove_at (int position) {
    if (position <= 0 || position > size) {
        cout << "Error: invalid position!" << endl;
        return;
    }
    else if (n == 0) {
        cout << "Error: list is empty!" << endl;
        return;
    }
    else {
        for (int i = position; i < n; i++)
            list[i] = list[i + 1];
        n--;
    }
}

int ContiguousList::binary_search (elem &e) {
    bool status = false;
    int i = 1, f = n, m;
    do {
        m = (i + f) / 2;
        if (list[m].name < e.name)
            i = m + 1;
        else if (list[m].name > e.name)
            f = m - 1;
        else
            status = true;
    } while (!status && i <= f);
    if (status == false) {
        std::cout << "Element not found!" << endl;
        return 0;
    }
    else
        return m;
}

int ContiguousList::binary_position (elem &e) {
    int i = 1, f = n, m = (i + f) / 2;
    if (e.name < list[1].name)
        return 1;
    else if (e.name >= list[n].name)
        return n + 1;
    else {
        do {
            if (e.name < list[m].name)
                f = m;
            else
                i = m + 1;
            m = (i + f) / 2;
        } while (i < f);
        return m;
    }
}

int ContiguousList::linear_search (elem &e) {
    int i;
    for (i = 1; i <= n && e.name != list[i].name; i++);
    if (i <= n)
        return i;
    else {
        std::cout << "Element not found!" << endl;
        return 0;
    }
}

