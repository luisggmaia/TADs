/*TADs*/

#include <iostream>
#include <string>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::string;

struct elem {
    int nome;
};

//Lista contígua

class Lista_contigua {
    public:
        Lista_contigua ( );
        void inicializar (int tamanho);
        void finalizar ( );
        void inserir (elem &e);
        void inserir_p (elem &e, int posicao);
        void remover ( );
        void remover_p (int posicao);
        void printar ( );
        int posicao_binaria (elem &e);
    private: 
        int n, tamanho;
        elem *lista;
        int busca_binaria (elem &e);
        int busca_linear (elem &e);
};

Lista_contigua::Lista_contigua ( ) {
    n = tamanho = 0;
    lista = NULL;
}

void Lista_contigua::printar ( ) {
    for (int i = 1; i <= n; i++)
        cout << lista[i].nome << endl;
}

void Lista_contigua::inicializar (int tamanho) {
    if (tamanho <= 0) {
        cout << "Erro: tamanho invalido!" << endl;
        return;
    }
    else {
        lista = (elem *) malloc ((tamanho + 1)*sizeof (elem));
        if (lista == NULL) {
            cout << "Erro: memoria cheia!" << endl;
            return;
        }
        this->tamanho = tamanho;
    }
}

void Lista_contigua::finalizar ( ) {
    if (lista == NULL) {
        cout << "Erro: lista ja esvaziada" << endl;
        return;
    }
    else {
        free (lista);
        lista = NULL;
        n = tamanho = 0;
    }
}

void Lista_contigua::inserir (elem &e) {
    if (n == tamanho) {
        cout << "Erro: lista cheia!" << endl;
        return;
    }
    else
        lista[++n] = e;
}

void Lista_contigua::inserir_p (elem &e, int posicao) {
    if (posicao <= 0 || posicao > n + 1) {
        cout << "Erro: posicao invalida!" << endl;
        return;
    }
    else if (n == tamanho) {
        cout << "Erro: lista cheia" << endl;
        return;
    }
    else {
        for (int i = n++; i >= posicao; i--)
            lista[i + 1] = lista[i];
        lista[posicao] = e;
    }
}

void Lista_contigua::remover ( ) {
    if (lista == NULL) {
        cout << "Erro: lista esvaziada" << endl;
        return;
    }
    else if (n == 0) {
        cout << "Erro: lista vazia!" << endl;
        return;
    }
    else
        n--;
}

void Lista_contigua::remover_p (int posicao) {
    if (posicao <= 0 || posicao > tamanho) {
        cout << "Erro: posicao invalida!" << endl;
        return;
    }
    else if (n == 0) {
        cout << "Erro: lista vazia" << endl;
        return;
    }
    else {
        for (int i = posicao; i < n; i++)
            lista[i] = lista[i + 1];
        n--;
    }
}

int Lista_contigua::busca_binaria (elem &e) {
    bool status = false;
    int i = 1, f = n, m;
    do {
        m = (i + f)/2;
        if (lista[m].nome < e.nome)
            i = m + 1;
        else if (lista[m].nome > e.nome)
            f = m - 1;
        else
            status = true;
    } while (!status && i <= f);
    if (status == false) {
        std::cout << "Elemento nao encontrado!" << endl;
        return 0;
    }
    else
        return m;
}

int Lista_contigua::posicao_binaria (elem &e) {
    int i = 1, f = n, m = (i + f)/2;
    if (e.nome < lista[1].nome)
        return 1;
    else if (e.nome >= lista[n].nome)
        return n + 1;
    else {
        do {
            if (e.nome < lista[m].nome)
                f = m;
            else
                i = m + 1;
            m = (i + f)/2;
        } while (i < f);
        return m;
    }
}

int Lista_contigua::busca_linear (elem &e) {
    int i;
    for (i = 1; i <= n && e.nome != lista[i].nome; i++);
    if (i <= n)
        return i;
    else {
        std::cout << "Elemento nao encontrado!" << endl;
        return 0;
    }
}

//Lista encadeada

struct no {
    elem e;
    no *p;
};

class Lista_encadeada {
    public:
        Lista_encadeada ( );
        void inserir (elem &e);
        void inserir_p (elem &e, int posicao);
        void remover ( );
        void remover_p (int posicao);
        void finalizar ( );
        void printar ( );
    private:
        int n;
        no *lista_i, *lista_f;
};

Lista_encadeada::Lista_encadeada ( ) {
    n = 0;
    lista_f = lista_i = NULL;
}

void Lista_encadeada::printar ( ) {
    no *auxiliar = lista_i;
    while (auxiliar != NULL) {
        cout << auxiliar->e.nome << endl;
        auxiliar = auxiliar->p;
    }
}

void Lista_encadeada::inserir (elem &e) {
    no *p = (no *) malloc (sizeof (no));
    if (p == NULL) {
        cout << "Erro: memoria cheia!" << endl;
        return;
    }
    p->e = e;
    p->p = NULL;
    if (lista_f == NULL)
        lista_f = lista_i = p;
    else
        lista_f = lista_f->p = p;
    n++;
}

void Lista_encadeada::inserir_p (elem &e, int posicao) {
    if (posicao < 1 || posicao > n + 1) {
        cout << "Erro: posicao invalida!" << endl;
        return;
    }
    else {
        no *p = (no *) malloc (sizeof (no));
        if (p == NULL) {
            cout << "Erro: memoria cheia!" << endl;
            return;
        }
        p->e = e;
        if (posicao == 1) {
            p->p = lista_i;
            lista_i = p;
            if (lista_f == NULL)
                lista_f = p;
        }
        else {
            no *auxiliar = lista_i;
            for (int i = 1; i < posicao - 1; i++)
                auxiliar = auxiliar->p;
            p->p = auxiliar->p;
            auxiliar->p = p;
        }
        if (lista_f->p != NULL)
            lista_f = lista_f->p;
        n++;
    }
}

void Lista_encadeada::remover ( ) {
    if (lista_i == NULL) {
        cout  << "Erro: lista vazia" << endl;
        return;
    }
    else {
        if (lista_i->p == NULL) {
            free (lista_i);
            lista_i = lista_f = NULL;
            n = 0;
        }
        else {
            no *auxiliar = lista_i;
            while (auxiliar->p->p != NULL)
                auxiliar = auxiliar->p;
            free (auxiliar->p);
            auxiliar->p = NULL;
            n--;
        }
    }
}

void Lista_encadeada::remover_p (int posicao) {
    if (posicao < 1 || posicao > n + 1) {
        cout << "Erro: posicao invalida!" << endl;
        return;
    }
    else if (lista_i == NULL) {
        cout  << "Erro: lista vazia" << endl;
        return;
    }
    else {
        no *auxiliara = lista_i;
        if (posicao == 1) {
            lista_i = lista_i->p;
            free (auxiliara);
            if (lista_i == NULL)
                lista_f = NULL;
            n--;
        }
        else {
            no *auxiliarb;
            for (int i = 1; i < posicao - 1; i++)
                auxiliara = auxiliara->p;
            auxiliarb = auxiliara->p;
            if (auxiliarb == lista_f)
                lista_f = auxiliara;
            auxiliara->p = auxiliara->p->p;
            free (auxiliarb);
            n--;
        }
    }
}

void Lista_encadeada::finalizar ( ) {
    if (lista_i == NULL) {
        cout  << "Erro: lista vazia" << endl;
        return;
    }
    else {
        no *auxiliar;
        do {
            auxiliar = auxiliar->p;
            free (lista_i);
            lista_i = auxiliar;
        } while (lista_i != NULL);
        lista_f = NULL;
        n = 0;
    }
}

//Lista duplamente encadeada

typedef struct no_duplo no_duplo;

struct no_duplo {
    elem e;
    no_duplo *a, *p;
};

class Lista_duplamente_encadeada {
    public:
        Lista_duplamente_encadeada ( );
        void inserir (elem &e);
        void inserir_p (elem &e, int posicao);
        void remover ( );
        void remover_p (int posicao);
        void finalizar ( );
    private:
        int n;
        no_duplo *lista;
};

Lista_duplamente_encadeada::Lista_duplamente_encadeada ( ) {
    n = 0;
    lista = NULL;
}

void Lista_duplamente_encadeada::inserir (elem &e) {
    no_duplo *p = (no_duplo *) malloc (sizeof (no_duplo));
    if (p == NULL) {
        cout << "Erro: memoria cheia!" << endl;
        return;
    }
    p->e = e;
    if (lista == NULL)
        lista->a = lista = p;
    else {
        p->a = lista->a;
        p->p = lista;
        lista->a = lista->a->p = p;
    }
}

void Lista_duplamente_encadeada::inserir_p (elem &e, int posicao) {
    if (posicao < 1 || posicao > n + 1) {
        cout << "Erro: posicao invalida!" << endl;
        return;
    }
    else {
        no_duplo *p = (no_duplo *) malloc (sizeof (no_duplo));
        if (p == NULL) {
            cout << "Erro: memoria cheia!" << endl;
            return;
        }
        p->e = e;
        if (posicao == 1) {
            p->p = lista;
            lista = p;
            lista->a = lista->p->a;
        }
        else {
            p->p = lista;
            for (int i = 1; i < posicao; i++)
                p->p = p->p->p;
            p->p->a->p = p->p->a = p;   
        }
        if (lista->a->p != lista)
            lista->a->p = lista;
        n++;
    }
}

void Lista_duplamente_encadeada::remover ( ) {
    if (lista == NULL) {
        cout  << "Erro: lista vazia" << endl;
        return;
    }
    else {
        if (lista->p == NULL) {
            free (lista);
            lista = NULL;
            n = 0;
        }
        else {
            lista->a = lista->a->a;
            free (lista->a->p);
            lista->a->p = lista;
            n--;
        }
    }
}

void Lista_duplamente_encadeada::remover_p (int posicao) {
    if (posicao < 1 || posicao > n + 1) {
        cout << "Erro: posicao invalida!" << endl;
        return;
    }
    else if (lista == NULL) {
        cout  << "Erro: lista vazia" << endl;
        return;
    }
    else {
        if (posicao == 1) {
            lista = lista->p;
            free (lista->p);
            n--;
        }
        else {
            no_duplo *auxiliar = lista;
            for (int i = 1; i < posicao; i++)
                auxiliar = auxiliar->p;
            auxiliar->a->p = auxiliar->p;
            auxiliar->p->a = auxiliar->a;
            free (auxiliar);
            n--;
        }
    }
}

void Lista_duplamente_encadeada::finalizar ( ) {
    if (lista == NULL) {
        cout  << "Erro: lista vazia" << endl;
        return;
    }
    else {
        do {
            lista = lista->p;
            free (lista->a);
        } while (lista->p != NULL);
            free (lista);
            lista = NULL;
        n = 0;
    }
}

//Fila contigua

class Fila_contigua {
    public:
        Fila_contigua ( );
        void inicializar (int tamanho);
        void finalizar ( );
        void inserir (elem &e);
        void remover ( );
        void printar ( );
    private:
        int i, n, tamanho;
        elem *fila;
};

Fila_contigua::Fila_contigua ( ) {
    i = 1;
    n = tamanho = 0;
    fila = NULL;
}

void Fila_contigua::printar ( ) {
    for (int j = i, k = i; j < n + i; j++) {
        cout << fila[k].nome << endl;
        k = j%tamanho + 1;
    }
}

void Fila_contigua::inicializar (int tamanho) {
    if (tamanho <= 0) {
        cout << "Erro: tamanho invalido!" << endl;
        return;
    }
    else {
        fila = (elem *) malloc ((tamanho + 1)*sizeof (elem));
        if (fila == NULL) {
            cout << "Erro: memoria cheia!" << endl;
            return;
        }
        this->tamanho = tamanho;
    }
}

void Fila_contigua::inserir (elem &e) {
    if (n == tamanho) {
        cout << "Erro: fila cheia!" << endl;
        return;
    }
    else {
        fila[(i + n - 1)%tamanho + 1] = e;
        n++;
    }
}

void Fila_contigua::remover ( ) {
    if (fila == NULL) {
        cout << "Erro: fila esvaziada" << endl;
        return;
    }
    else if (n == 0) {
        cout << "Erro: fila vazia!" << endl;
        return;
    }
    else {
        i = i%tamanho + 1;
        n--;
    }
}

void Fila_contigua::finalizar ( ) {
    if (fila != NULL) {
        free (fila);
        fila = NULL;
        i = n = tamanho = 0;
    }
    else {
        cout << "Erro: fila ja esvaziada" << endl;
        return;
    }
}

//Fila encadeada

class Fila_encadeada {
    public:
        Fila_encadeada ( );
        void inserir (elem &e);
        void remover ( );
        void finalizar ( );
        void printar ( );
    private:
        no *fila_i, *fila_f;
};

Fila_encadeada::Fila_encadeada ( ) {
    fila_f = fila_i = NULL;
}

void Fila_encadeada::printar ( ) {
    no *auxiliar = fila_i;
    while (auxiliar != NULL) {
        cout << auxiliar->e.nome << endl;
        auxiliar = auxiliar->p;
    }
}

void Fila_encadeada::inserir (elem &e) {
    no *p = (no *) malloc (sizeof (no));
    if (p == NULL) {
        cout << "Erro: memoria cheia!" << endl;
        return;
    }
    p->e = e;
    p->p = NULL;
    if (fila_f == NULL)
        fila_f = fila_i = p;
    else
        fila_f = fila_f->p = p;
}

void Fila_encadeada::remover ( ) {
    if (fila_i == NULL) {
        cout  << "Erro: lista vazia" << endl;
        return;
    }
    else {
        if (fila_i->p == NULL) {
            free (fila_i);
            fila_f = fila_i = NULL;
        }
        else {
            no *auxiliar = fila_i;
            fila_i = fila_i->p;
            free (auxiliar);
        }
    }
}

void Fila_encadeada::finalizar ( ) {
    if (fila_i == NULL) {
        cout  << "Erro: fila ja esvaziada" << endl;
        return;
    }
    else {
        no *auxiliar;
        do {
            auxiliar = auxiliar->p;
            free (fila_i);
            fila_i = auxiliar;
        } while (fila_i != NULL);
        fila_f = NULL;
    }
}

//Pilha contigua

class Pilha_contigua {
    public:
        Pilha_contigua ( );
        void inicializar (int tamanho);
        void empilhar (elem &e);
        void desempilhar ( );
        void esvaziar  ( );
        int busca_binaria (elem &e);
        int busca_linear (elem &e);
    private:
        int tamanho, n;
        elem *pilha;
};

Pilha_contigua::Pilha_contigua ( ) {
    n = tamanho = 0;
    pilha = NULL;
}

void Pilha_contigua::inicializar (int tamanho) {
    if (tamanho <= 0) {
        cout << "Erro: tamanho invalido!" << endl;
        return;
    }
    else {
        pilha = (elem *) malloc ((tamanho + 1)*sizeof (elem));
        if (pilha == NULL) {
            cout << "Erro: memoria cheia!" << endl;
            return;
        }
        this->tamanho = tamanho;
    }
}

void Pilha_contigua::esvaziar ( ) {
    if (pilha == NULL) {
        cout << "Erro: pilha ja esvaziada" << endl;
        return;
    }
    else {
        free (pilha);
        pilha = NULL;
        n = tamanho = 0;
    }
}

void Pilha_contigua::empilhar (elem &e) {
    if (n == tamanho) {
        cout << "Erro: pilha cheia!" << endl;
        return;
    }
    else
        pilha[++n] = e;
}

void Pilha_contigua::desempilhar ( ) {
    if (pilha == NULL) {
        cout << "Erro: pilha esvaziada" << endl;
        return;
    }
    else if (n == 0) {
        cout  << "Erro: lista vazia" << endl;
        return;
    }
    else
        n--;
}

int Pilha_contigua::busca_binaria (elem &e) {
    bool status = false;
    int i = 1, f = n, m;
    do {
        m = (i + f)/2;
        if (pilha[m].nome < e.nome)
            f = m - 1;
        else if (pilha[m].nome > e.nome)
            i = m + 1;
        else
            status = true;
    } while (!status && i <= f);
    if (status == false) {
        std::cout << "Elemento nao encontrado!" << endl;
        return 0;
    }
    else
        return m;
}

int Pilha_contigua::busca_linear (elem &e) {
    int i;
    for (i = 1; i <= n && e.nome != pilha[i].nome; i++);
    if (i <= n)
        return i;
    else
        return 0;
}

//Pilha encadeada

class Pilha_encadeada {
    public:
        Pilha_encadeada ( );
        void empilhar (elem e);
        void desempilhar ( );
        void esvaziar  ( );
    private:
        no *pilha;
};

Pilha_encadeada::Pilha_encadeada ( ) {
    pilha = NULL;
}

void Pilha_encadeada::empilhar (elem e) {
    no *p = (no *) malloc (sizeof (no));
    if (p == NULL) {
        cout << "Erro: memoria cheia!" << endl;
        return;
    }
    else {
        p->e = e;
        p->p = pilha;
        pilha = p;
    }
}

void Pilha_encadeada::desempilhar ( ) {
    if (pilha == NULL) {
        cout  << "Erro: lista vazia" << endl;
        return;
    }
    else {
        no *auxiliar = pilha;
        pilha = pilha->p;
        free (auxiliar);
    }
}

void Pilha_encadeada::esvaziar ( ) {
    if (pilha == NULL) {
        cout  << "Erro: lista vazia" << endl;
        return;
    }
    else {
        no *auxiliar;
        do {
            auxiliar = auxiliar->p;
            free (pilha);
            pilha = auxiliar;
        } while (auxiliar != NULL);
    }
}

//Deque

class Deque_contiguo {
    public:
        Deque_contiguo ( );
        void inicializar ( );
        void finalizar ( );
        void inserir_inicio (elem &e);
        void inserir_final (elem &e);
        void remover_inicio ( );
        void remover_final ( );
    private:
        int i, f, n, tamanho;
        elem *deque;
};

Deque_contiguo::Deque_contiguo ( ) {
    i = 1;
    n = tamanho = 0;
    deque = NULL;
}

void Deque_contiguo::inicializar ( ) {
    if (tamanho <= 0) {
        cout << "Erro: tamanho invalido!" << endl;
        return;
    }
    else {
        deque = (elem *) malloc ((tamanho + 1)*sizeof (elem));
        if (deque == NULL) {
            cout << "Erro: memoria cheia!" << endl;
            return;
        }
        this->tamanho = tamanho;
    }
}

void Deque_contiguo::finalizar ( ) {
    if (deque != NULL) {
        free (deque);
        deque = NULL;
        i = n = tamanho = 0;
    }
    else {
        cout << "Erro: deque ja esvaziada" << endl;
        return;
    }
}

void Deque_contiguo::inserir_inicio (elem &e) {
    if (n == tamanho) {
        cout << "Erro: deque cheio!" << endl;
        return;
    }
    else {
        i--;
        if (i == 0)
            i = tamanho;
        deque[i] = e;
        n++;
    }
}

void Deque_contiguo::inserir_final (elem &e) {
    if (n == tamanho) {
        cout << "Erro: deque cheio!" << endl;
        return;
    }
    else {
        deque[(i + n - 1)%tamanho + 1] = e;
        n++;
    }
}

void Deque_contiguo::remover_inicio ( ) {
    if (deque == NULL) {
        cout << "Erro: deque esvaziada" << endl;
        return;
    }
    else if (n == 0) {
        cout << "Erro: deque vazia!" << endl;
        return;
    }
    else {
        i = i%tamanho + 1;
        n--;
    }
}

void Deque_contiguo::remover_final ( ) {
    if (deque == NULL) {
        cout << "Erro: deque esvaziada" << endl;
        return;
    }
    else if (n == 0) {
        cout << "Erro: deque vazia!" << endl;
        return;
    }
    else
        n--;
}

//Main

int main ( ) {
    elem e1, e2, e3, e4, e5, e6, e7, e8;
    e1.nome = 1; e2.nome = 3; e3.nome = 8, e4.nome = 15, e5.nome = 18, e6.nome = 32, e7.nome = 73;
    e8.nome = 71;

    /*Fila_encadeada fila;
    // fila.inicializar (3);
    fila.inserir (e1); fila.inserir (e2); fila.inserir (e3); fila.inserir (e4);
    // fila.remover ( ); fila.remover ( ); fila.remover ( ); fila.remover ( );
    fila.inserir (e3);
    fila.remover ( );

    fila.printar ( );

    fila.finalizar ( );*/

    /*Lista_contigua lista;
    lista.inicializar (7);
    lista.inserir (e1); lista.inserir (e2); lista.inserir (e3); lista.inserir (e4); lista.inserir (e5); lista.inserir (e6); lista.inserir (e7);
    cout << lista.posicao_binaria (e8) << endl;
    lista.finalizar ( );*/

    cout << (-1)%5;
}