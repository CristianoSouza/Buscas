#include "Dijkstra.h"

Dijkstra::Dijkstra( Graph *g, int index, QMainWindow *main,QObject *parent ) : QThread(parent) {
    this->grafo = g;
    this->f = new Graph (0, main);
    this->index = index;
}

Graph *Dijkstra::getGraph() {
    return this->grafo;
}

Dijkstra::~Dijkstra ( ) {
    delete grafo;
    delete f;
}

void Dijkstra::run () {
    dijkstra();
}

void Dijkstra::dijkstra() {
    qDebug() << "chegou metodoDijkstra";
    Vertex *verticeAtual, *vertice;
    Edge *aresta;
    Vertex **V = grafo->getVertex();

    for ( int i = 0; i < grafo->getVertexCount(); i++ ) {
        V[i]->setColor(Qt::white);
        V[i]->setFather(NULL);
        V[i]->setD(INF);
        qDebug() << "dentro do for";
    }

    V[index]->setColor(Qt::gray);
    emit update(grafo);
    sleep(1);
    qDebug() << "Pintou cinza";
    V[index]->setD(0);
    qDebug() << "Vai inserir Lista";
    lista.append(V[index]);
    while (!lista.empty()) {
        vertice = popMenor();
        vertice->setColor(Qt::black);
        emit update(grafo);
        sleep(1);
        qDebug() << "Pintou Preto";
        for ( aresta = vertice->getEdges(); aresta; aresta = aresta->getNext() ) {
            verticeAtual = V[aresta->getIdAdj()];
            if ( ( vertice->getD() + aresta->getW()) < ( verticeAtual->getD() ) ) {
                verticeAtual->setD( vertice->getD() + aresta->getW() );
                verticeAtual->setFather(vertice);
            }
            if ( verticeAtual->getColor() == Qt::white ) {
                verticeAtual->setColor(Qt::gray);
                emit update(grafo);
                sleep(1);
                qDebug() << "Pintou Cinza";
                lista.append(verticeAtual);
            }
        }
    }
    pintar(V);
}

Vertex* Dijkstra::popMenor(){
    int menor = 0;
    for (int i= 1; i < lista.size(); i++ ) {
        if ( lista.at(i)->getD() < lista.at(menor)->getD() ) {
            menor = i;
        }
    }
   return lista.takeAt(menor);
}

void Dijkstra::pintar(Vertex ** v){
    f->resize( grafo->getVertexCount() );
    for (int i = 0; i < this->getGraph()->getVertexCount(); i++){
        QPoint p = v[i]->getPoint();
        p.setY ( p.y()+300);
        f->addVertex( v[i]->getName(), p );
        if (i > 0)qDebug()<<v[i]->getName() << " " << v[i]->getFather()->getName()<< " " <<v[i]->getEdges()->getW();
    }
    for (int i = 0; i < this->getGraph()->getVertexCount(); i++){
        if (v[i]->getFather()!= NULL){
            f->addEdge( v[i]->getName(), v[i]->getFather()->getName(), grafo->getVertexAt(v[i]->getId())->getEdges()->getW(), Qt::red );
        }
    }
    emit update(f);
    sleep(1);

}
