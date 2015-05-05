#include "OrdenacaoTopologica.h"

OrdenacaoTopologica::OrdenacaoTopologica( Graph *g, int index,QObject *parent ) : QThread(parent) {
    this->g = g;
    this->index = index;
}

OrdenacaoTopologica::~OrdenacaoTopologica () {
    delete g;
}

void OrdenacaoTopologica::run () {
    ordenacaoTopologica();
}

void OrdenacaoTopologica:: ordenacaoTopologica() {
    Vertex **V = g->getVertex();
    int n = g->getVertexCount();
    for(int i = this->index; i < n; i++) {
        V[i]->setFather(NULL);
        V[i]->setTi(INFINITO);
        V[i]->setTo(INFINITO);
        V[i]->setColor(Qt::white);
    }
    tempo = 0;
    for(int i = 0; i < n; i++) {
        if(V[i]->getColor() == Qt::white) {
            visit(V[i]);
        }
    }
}

void OrdenacaoTopologica::visit(Vertex *v) {
    Edge *a; Vertex *va;
    v->setColor(Qt::gray);
    emit update(g);
    sleep(1);
    v->setTi(tempo++);
    for(a = v->getEdges(); a ; a = a->getNext()) {
        va = g->getVertex()[a->getIdAdj()];
        if(va->getColor() == Qt::white) {
            va->setFather(v);
            visit(va);
        }
    }
    v->setTo(tempo++);
    v->setColor(Qt::black);
    lista.append(v);
    emit update(g);
    sleep(1);
}
