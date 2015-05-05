#include "Prim.h"

Prim::Prim( Graph *g, int index, QMainWindow *main,QObject *parent ) : QThread(parent) {
    this->grafo = g;
    this->f = new Graph (0, main);
    this->index = index;
}

Graph *Prim::getGraph() {
    return this->grafo;
}

Prim::~Prim ( ) {
    delete grafo;
}

void Prim::run () {
    prim();
}

void Prim::prim() {
    int n = grafo->getVertexCount();
    Vertex **V = grafo->getVertex();
    Vertex *verticeAtual, *vertice;
    Edge *aresta;
    qDebug()<<"Prim";
    for( int i = 0; i < n; i++ ) {
        V[i]->setD(INF);
        V[i]->setFather(NULL);
        V[i]->setColor(Qt::white);
        lista.append(V[i]);
        qDebug()<<"Adicionando " << V[i]->getName();
    }
    V[index]->setD(0);
    while ( !lista.empty() ) {
        vertice = popMenor();
        vertice->setColor(Qt::gray);
        emit update(grafo);
        sleep(1);
        for ( aresta = vertice->getEdges(); aresta; aresta = aresta->getNext() ){
            verticeAtual = V[aresta->getIdAdj()];
            if ( (verticeAtual->getColor() != Qt::black ) && (verticeAtual->getD() > aresta->getW()) ) {
                verticeAtual->setFather(vertice);
                verticeAtual->setD( aresta->getW() );
            }
        }
        vertice->setColor(Qt::black);
        emit update(grafo);
        sleep(1);
    }
    pintar(V);
}

void Prim::pintar(Vertex ** v){
    f->resize( grafo->getVertexCount() );
    for (int i = 0; i < this->getGraph()->getVertexCount(); i++){
        QPoint p = v[i]->getPoint();
        p.setY ( p.y()+300);
        f->addVertex( v[i]->getName(), p );

    }
    for (int i = 0; i < this->getGraph()->getVertexCount(); i++){
        if (v[i]->getFather()!= NULL){
            f->addEdge( v[i]->getName(), v[i]->getFather()->getName(), v[i]->getEdges()->getW(), Qt::red );
        }
    }
    emit update(f);
    sleep(1);

}

Vertex* Prim::popMenor(){
    int menor = 0;
    for (int i= 1; i < lista.size(); i++ ) {
        if ( lista.at(i)->getD() < lista.at(menor)->getD() ) {
            menor = i;
        }
    }
   return lista.takeAt(menor);
}
