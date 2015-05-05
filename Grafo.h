#ifndef GRAFO_H
#define GRAFO_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QString>
#include <QColor>
#include <QMessageBox>
#include <QMainWindow>

#include <QPainter>

#include "Vertice.h"
#include "Aresta.h"

#define INF  100000

class Grafo : public QWidget {
    Q_OBJECT

public:
    Grafo ( int n, QMainWindow *m, QWidget *pai=0 );


    void adicionarVertice ( QString, QPoint );
    bool adicionarAresta ( QString, QString, int, QColor cor=Qt::black );

    Aresta    *getArestas();
    Vertice  **getVertice () ;
    Vertice  *getVerticeAt ( int );
    int     getQuantidadeVertice();
    int     getVerticeIndice ( QString  );
    QString getCaminho ( QString );
    QString carregarDoArquivo( QString );
    QString BuscaVerticeRaiz( QString );
    QString BuscaArrestasDeDeterminadoVertice( QString,  Vertice* );
    void pintar ();

    void resize ( int );
    void dispose ();
    ~Grafo ( ) ;

signals:
    void update ( Grafo * );

private:
    QMainWindow *main;
    Vertice      **vertice;
    Aresta        *arestas;

    int max;
    int quantidadeVertices;
};



#endif // GRAFO_H
