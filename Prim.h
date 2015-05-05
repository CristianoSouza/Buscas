#ifndef PRIM_H
#define PRIM_H

#include <QThread>
#include <QDebug>
#include <QString>
#include <QColor>
#include <QMainWindow>

#include "graph.h"


#define INF  100000

class Prim : public QThread {
    Q_OBJECT

public:
    Prim (Graph *g, int index, QMainWindow *main,QObject *parent=0 );

    Graph *getGraph();
    Vertex * popMenor();
    void pintar(Vertex **);
    ~Prim () ;

protected:
    void run();

signals:
    void update ( Graph * );

private:
    int index;
    Graph *grafo,*f;
    QList<Vertex *> lista;
    void prim ();
};

#endif // PRIM_H
