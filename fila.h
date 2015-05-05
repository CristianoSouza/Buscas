#ifndef LISTA_H
#define LISTA_H

/*#include "Aresta.h"
#include "vertice.h"

class Elemento {
protected:
    void *elemento;
    Elemento *next;
public:
    Elemento ( void *e ) {
        this->elemento = e;
    }

    void setNext ( Elemento *n ) { this->next = n;        }
    Elemento *getNext ()         { return this->next;     }
    void *getElemento ()         { return this->elemento; }

    ~Elemento  () {
        if (next!=NULL)
            delete next;
    }
};

class Lista : public QObject {
    Q_OBJECT

public:
    Lista ( ) {
       first = NULL;
       last  = NULL;
    }

    void append  ( void *v ) {
        Elemento *e = new Elemento(v);
        if (first==NULL)
            last=e;
        else
            e->setNext (first);

        first = e;
    }

    void * removeInicio  ( ) {
        void *e = NULL;
        Elemento *tmp;
        if (first!=NULL) {
            e = first->getElemento();
            tmp = first;
            first=first->getNext();
            delete tmp;
        };
        return e;
    }

    ~Lista () {
        if (first!=NULL) delete first;
    }


private:
    Elemento *first;
    Elemento *last;
};*/


#endif // LISTA_H
