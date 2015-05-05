#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <QThread>
#include <QDebug>
#include <QString>
#include <QColor>
#include <QMainWindow>

#include "graph.h"


#define INF  100000

class kruskal : public QThread {
    Q_OBJECT

public:
    kruskal ( Graph *g, QMainWindow *main, QObject *parent=0 );

    Graph *getGraph();

    ~kruskal () ;

protected:
    void run();

signals:
    void update ( Graph * );

private:
    Graph *f, *g;

    // KRUSKAL
    void KRUSKAl ();

    void MAKE_SET ( );
    QString FIND_SET( Vertex * );
    void UNION (  Vertex *, Vertex *, int  ) ;

    //void createNewGraph ( int );
};

#endif // KRUSKAL_H
