#include "Bfs.h"

Bfs::Bfs( Grafo *grafo, int verticeInicial, QString nomeArquivo, QObject *parent) : QThread(parent) {
    this->grafo = grafo;
    this->verticeInicial = verticeInicial;
    this->nomeArquivo = nomeArquivo;
}

Bfs::~Bfs () {
    delete grafo;
}

void Bfs::run () {
    metodoBFS();
}

void Bfs:: metodoBFS() {
    qDebug() << "Metodo BFS";

    QList<Vertice *> lista;
    Vertice *verticeAtual, *vertice;
    Aresta *aresta;
    grafo->BuscaVerticeRaiz(nomeArquivo);
    Vertice **ListaVertices = grafo->getVertice();
    /*int quantidade = grafo->getQuantidadeVertice();
    int i;
    for ( i = 0; i < quantidade; i++ ) {
        ListaVertices[i]->setPai(NULL);
        ListaVertices[i]->setCor(Qt::white);
        ListaVertices[i]->setPeso(INFINITO);
    }
    */
    ListaVertices[0]->setPeso(0);
    ListaVertices[0]->setCor(Qt::gray);
    emit update(grafo);
    sleep(1);

    lista.append(ListaVertices[0]);
    while (!lista.empty()) {
        vertice = lista.takeFirst();
        //for ( aresta = grafo->BuscaArrestasDeDeterminadoVertice(vertice); aresta; aresta = aresta->getProximo() ) {
            //getVerticeAdj();
            //verticeAtual = ListaVertices[aresta->getIndiceAdj()];
            if ( verticeAtual->getCor() == Qt::white ) {
                verticeAtual->setCor(Qt::gray);

                emit update(grafo);
                sleep(1);

                verticeAtual->setPai(vertice);
                verticeAtual->setPeso(vertice->getPeso() + 1 );
                lista.append(verticeAtual);
            }
        //}
        vertice->setCor(Qt::black);
        emit update(grafo);
        sleep(1);
        qDebug() << "Emitiu sinal";
    }
}


