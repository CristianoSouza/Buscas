#include "FordFulkerson.h"

FordFulkerson::FordFulkerson( Graph *g, int index, int final, QObject *parent ) : QThread(parent) {
    this->g = g;
    this->index = index;
    this->final = final;
}

FordFulkerson::~FordFulkerson () {
    delete g;
}

void Dfs::run () {
    metodoDFS();
}

void Dfs:: metodoDFS() {
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

void Dfs::visit(Vertex *v) {
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
    emit update(g);
    sleep(1);
}
