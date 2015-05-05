#include "kruskal.h"

kruskal::kruskal( Graph *g, QMainWindow *main, QObject *parent ) : QThread(parent) {
    this->g = g;
    this->f = new Graph (0, main);
}

Graph *kruskal::getGraph() {
    return this->f;
}

kruskal::~kruskal ( ) {
    delete f;
}

void kruskal::run () {
    KRUSKAl();
}

// Algoritmo para o método de Kruskal
void kruskal::MAKE_SET () {
   f->resize( g->getVertexCount() );
   for (int i=0; i<g->getVertexCount(); i++) {
       Vertex *v = g->getVertexAt(i);
       QPoint p = v->getPoint(); p.setY ( p.y()+300);
       f->addVertex( v->getName(), p );
   }
}

QString kruskal::FIND_SET ( Vertex *v ) {
    return v->getSET();
}

void kruskal::UNION ( Vertex *v1, Vertex *v2, int w ) {
    f->addEdge( v1->getName(), v2->getName(), w, Qt::red );

    QString newSet = v1->getSET() + ";" + v2->getSET();
    QStringList sl = newSet.split(";");

    for (int i=0; i<sl.size(); i++) {
        f->getVertexAt(sl.at(i).toInt())->setSET(newSet);
    }
}

void kruskal::KRUSKAl ( ) {
    Vertex *v1, *v2;

    MAKE_SET( );

    Edge *e, *h = Edge::clone( g->getEdges() );

    while (h!=NULL) {

        e = Edge::removeLeast( &h );

        v1 = f->getVertexAt(e->getId());
        v2 = f->getVertexAt(e->getIdAdj());

        if ( FIND_SET( v1 ) != FIND_SET( v2 ) )
            UNION( v1, v2, e->getW());

        emit update(f);
        sleep(1);

        delete e;
    }
}
