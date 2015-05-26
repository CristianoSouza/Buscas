#ifndef DFS_H
#define DFS_H

#define INFINITO 1000000
#include <QThread>
#include <QDebug>
#include <QString>
#include <QColor>
#include <QMainWindow>

#include "Grafo.h"


#define INF  100000

class Dfs : public QThread {
    Q_OBJECT

public:
    Dfs ( Grafo *grafo, QString verticeFinal, QString nomeArquivo, QObject *parent=0 );

    Grafo *getGrafo();
    QString getCaminhoArestas( QString );

    ~Dfs () ;

protected:
    void run();

signals:
    void update ( Grafo * );

private:
    Grafo *grafo;
    int tempo;
    QString verticeFinal;
    QString nomeArquivo;
    bool achou;
    bool metodoDFS ();

    bool visit (Vertice *);

    //void createNewGraph ( int );
};

#endif // DFS_H
