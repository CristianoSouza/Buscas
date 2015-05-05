#ifndef ARESTA_H
#define ARESTA_H

#include <QDebug>
#include <QPainter>
#include <QColor>

class Aresta : public QObject {
    Q_OBJECT

public:
    Aresta ( int , int, int, QColor, QObject *pai=0 );
    ~Aresta();

    static Aresta* clonar ( Aresta * );
    static void  acrescentar ( Aresta **, int, int, int, QColor cor );
    static Aresta* removeMenor ( Aresta **, Aresta *m=0 );

    int    getPeso ();
    int    getIndice();
    int    getIndiceAdj();
    QColor getCor();
    Aresta   *getProximo();


    void setCor ( QColor );
    void pintar( QPoint ponto1, QPoint ponto2, QPainter & );

private:    
    int    indice;
    int    indiceAdj;
    int    peso;
    QColor cor;
    Aresta   *proximo;
};

#endif // EDGE_H
