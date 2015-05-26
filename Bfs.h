#ifndef BFS_H
#define BFS_H


#include <QThread>
#include <QDebug>
#include <QString>
#include <QColor>
#include <QMainWindow>

#include "Grafo.h"

#define INFINITO 1000000

class Bfs : public QThread {
    Q_OBJECT

public:
    Bfs ( Grafo *grafo, QString verticeFinal, QString nomeArquivo, QObject *parent=0 );
    QString getCaminhoArestas( QString );
    ~Bfs () ;

protected:
    void run();

signals:
    void update ( Grafo * );

private:
    Grafo *grafo;
    QString verticeFinal;
    QString nomeArquivo;
    bool achou;
    bool metodoBFS ();

};

#endif // BFS_H
