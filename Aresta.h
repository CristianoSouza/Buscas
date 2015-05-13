#ifndef ARESTA_H
#define ARESTA_H

#include <QDebug>
#include <QPainter>
#include <QColor>

class Aresta : public QObject {
    Q_OBJECT

public:
    Aresta ( QString , QString, int, QColor, QObject *pai=0 );
    ~Aresta();

    static Aresta* clonar ( Aresta * );
    static void  acrescentar ( Aresta **, QString, QString, int, QColor cor );
    static Aresta* removeMenor ( Aresta **, Aresta *m=0 );

    int    getPeso ();
    QString getverticeOrigem();
    QString getverticeDestino();
    QColor getCor();
    Aresta   *getProximo();


    void setCor ( QColor );
    void pintar( QPoint ponto1, QPoint ponto2, QPainter & );

private:    
    QString verticeOrigem;
    QString verticeDestino;
    int    peso;
    QColor cor;
    Aresta   *proximo;
};

#endif // EDGE_H
