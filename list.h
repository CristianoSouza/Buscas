#ifndef LIST_H
#define LIST_H
/*
#include "vertex.h"

class List {
protected:
    Vertex *v;
    List *next;
public:
    List ( Vertex *v, List *next ) {
        this->v = v;
        this->next = next;
    }

    static void insertBefore( List **first, Vertex *v ) {
        List *n = new List ( v, *first );
        *first = n;
    }

    static void append ( List **e, Vertex *v ) {
        if (*e)
            append( &(*e)->next, v );
        else
            *e = new List ( v, NULL );
    }

    Vertex* removeFirst ( List **first ) {
        Vertex *v=NULL;
        if (*first) {
            List *e= *first;
            v = e->v;
            *first = e->next;

            e->next = NULL;
            delete e;
        }
        return v;
    }

    Vertex* removeLeast ( List **e, Vertex *m=NULL ) {
        if (*e) {
            if (!m) m = (*e)->v;

            if ((*e)->getD()<m->getD())
                m = removeLeast( &(*e)->next,*e);
            else
                m = removeLeast( &(*e)->next,m);

            if (m==*e) {
                *e = m->getNext();
                m->next = NULL;
            }
        }
        return m;
    }

    //void *getVertex ()       { return this->v;    }

    QString getList ( ) {
        QString s= v->getNome + ";";
        if (next)
            s += next->getList();

        return s;
    }

    ~List () {
        if (next) delete next;
    }
};
*/

#endif // LIST_H
