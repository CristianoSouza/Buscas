#include "Dfs.h"

Dfs::Dfs( Grafo *grafo, QString verticeFinal, QString nomeArquivo, QObject *parent ) : QThread(parent) {
    this->grafo = grafo;
    this->verticeFinal = verticeFinal;
    this->nomeArquivo = nomeArquivo;
    this->achou = false;
}

Dfs::~Dfs () {
    delete grafo;
}

void Dfs::run () {
    metodoDFS();
}

bool Dfs:: metodoDFS() {
    qDebug() << "mETODO DFS";
    grafo->BuscaVerticeRaiz(nomeArquivo);
    QHash <QString,Vertice*> ListaVertices = grafo->getVertice();

    tempo = 0;

    ListaVertices.value(ListaVertices.begin().key())->setPeso(0);
    ListaVertices.value(ListaVertices.begin().key())->setPai(NULL);
    ListaVertices.value(ListaVertices.begin().key())->setCor(Qt::blue);

    QHashIterator<QString, Vertice*> i(ListaVertices);
    while (i.hasNext()) {
        Vertice * vertice = i.next().value();
        qDebug() << "Vertice" << vertice->getNome();
        qDebug() << "Vertice FInal " << verticeFinal;
        if ( vertice->getCor() == Qt::blue ){

            if (visit(vertice)) { qDebug() << "VAI BRECKA"; break;  }
        }
    }
    getCaminhoArestas(verticeFinal);

    return true;
}

bool Dfs::visit(Vertice *vertice) {
    Aresta *aresta; Vertice *verticeAtual;

    vertice->setCor(Qt::gray);

    emit update(grafo);
    sleep(1);

    if ( vertice->getNome().toLower() == verticeFinal.toLower()) {
        vertice->setCor(Qt::green);
        qDebug() << "SACHOU SAPOHA dentro VISIT";
        emit update(grafo);
        sleep(1);
        return true;
    }

    vertice->setTempoEntrada(tempo++);

    grafo->BuscaArrestasDeDeterminadoVertice( nomeArquivo, vertice );

    emit update(grafo);
    sleep(1);

    for(aresta = vertice->getArestas(); aresta; aresta = aresta->getProximo()) {
        verticeAtual= grafo->getVertice(aresta->getverticeDestino());
        if(verticeAtual->getCor() == Qt::blue) {
            verticeAtual->setPai(vertice);
            if ( verticeAtual->getNome().toLower() == verticeFinal.toLower()) {
                verticeAtual->setCor(Qt::green);
                qDebug() << " ACHOUUUU UUUUUUUUU U UUUUU SACHOU SAPOHA dentro VISIT VERTICE ATUAL";
                emit update(grafo);
                sleep(1);
                this->achou = true;
                break;
            }
            qDebug() << "NAO SAIUU";
            if (visit(verticeAtual)) { this->achou = true; break; };
        }
    }
    vertice->setTempoSaida(tempo++);
    vertice->setCor(Qt::black);
    emit update(grafo);
    sleep(1);
    if( this->achou ) {
        return true;
    }
}


QString Dfs::getCaminhoArestas( QString nome  ) {
    qDebug() << "GetCaminhoArestas";
    QHash <QString,Vertice*> ListaVertices = grafo->getVertice();
    QString s = "";

    Vertice *vertice = ListaVertices.value(nome.toLower());
    qDebug() << vertice;
    qDebug() << ListaVertices.count();
    while (vertice->getPai()!=NULL) {
        s += vertice->getNome()+ ",";
        vertice->getPai()->setCor(Qt::green);
        vertice = vertice->getPai();
    }
    qDebug() << "Saiu get caminho arestas";
    return s;
}

