#ifndef ORDENACAOTOPOLOGICA_H
#define ORDENACAOTOPOLOGICA_H

#define INFINITO 1000000
#include <QThread>
#include <QDebug>
#include <QString>
#include <QColor>
#include <QMainWindow>
#include "graph.h"


#define INF  100000

class OrdenacaoTopologica : public QThread {
    Q_OBJECT

public:
    OrdenacaoTopologica (Graph *g, int index, QObject *parent=0 );

    Graph *getGraph();
    QList <Vertex *> getList(){return lista;}
    ~OrdenacaoTopologica () ;

protected:
    void run();

signals:
    void update ( Graph * );

private:
    Graph *g;
    int tempo;
    int index;
    QList <Vertex*> lista;
    void ordenacaoTopologica ();

    void visit (Vertex *);
};
#endif // ORDENACAOTOPOLOGICA_H
