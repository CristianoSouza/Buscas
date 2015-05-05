#include "Dfs.h"

Dfs::Dfs( Grafo *grafo, int indice, QObject *parent ) : QThread(parent) {
    this->grafo = grafo;
    this->indice = indice;
}

Dfs::~Dfs () {
    delete grafo;
}

void Dfs::run () {
    metodoDFS();
}

void Dfs:: metodoDFS() {
    Vertice **ListaVertice = grafo->getVertice();
    int quantidade = grafo->getQuantidadeVertice();
    for(int i = this->indice; i < quantidade; i++) {
        ListaVertice[i]->setPai(NULL);
        ListaVertice[i]->setTempoEntrada(INFINITO);
        ListaVertice[i]->setTempoSaida(INFINITO);
        ListaVertice[i]->setCor(Qt::white);
    }
    tempo = 0;
    for(int i = 0; i < quantidade; i++) {
        if(ListaVertice[i]->getCor() == Qt::white) {
            visit(ListaVertice[i]);
        }
    }
}

void Dfs::visit(Vertice *vertice) {
    Aresta *aresta; Vertice *verticeAtual;
    vertice->setCor(Qt::gray);
    emit update(grafo);
    sleep(1);
    vertice->setTempoEntrada(tempo++);
    for(aresta = vertice->getArestas(); aresta; aresta = aresta->getProximo()) {
        verticeAtual = grafo->getVertice()[aresta->getIndiceAdj()];
        if(verticeAtual->getCor() == Qt::white) {
            verticeAtual->setPai(vertice);
            visit(verticeAtual);
        }
    }
    vertice->setTempoSaida(tempo++);
    vertice->setCor(Qt::black);
    emit update(grafo);
    sleep(1);
}
