#ifndef VERTICE_H
#define VERTICE_H

#include <QObject>
#include <QDebug>
#include <QColor>
#include <QPainter>

#include "Aresta.h"

class Vertice : public QObject {
    Q_OBJECT

public:
    Vertice ( int, QString, QPoint, QObject *parent=0 );
     ~Vertice();

    QString getSET ();
    int getIndiceVertice();
    QString getNome ();
    QColor  getCor();
    Aresta   *getArestas ();
    Vertice  *getPai();
    Aresta * getArestaPai();
    int     getPeso ();
    int     getTempoEntrada ();
    int     getTempoSaida ();
    QPoint  getPonto ();
    //int     getY ();

    void setSET ( QString );
    void acrescentar ( QString, int, QColor color );
    void setAresta( Aresta *);
    void setPai ( Vertice * );
    void setArestaPai ( Aresta *);
    void setPeso ( int );
    void setTempoEntrada ( int  );
    void setTempoSaida ( int  );
    void setCor ( QColor  ) ;

    Vertice *clonar ();
    void pintar ( QPainter & );

protected:
    QString nome;
    int indiceVertice;         // Index do vértice no vetor
    int peso;          // tempo de entrada | distância | peso
    int tempoEntrada; // tempo de entrada
    int tempoSaida;          // tempo de saida
    Vertice *pai; // pai do vértice
    Aresta *arestaPai;
    QColor  cor;  // cor do vértice

    QString set;

    Aresta   *arestas;

    QPoint ponto;
    int cordenadaX;  // coordenada para desenho
    int cordenadaY;  // coordenada para desenho
};

#endif // VERTICE_H
