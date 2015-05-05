#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <QThread>
#include <QDebug>
#include <QString>
#include <QColor>
#include <QMainWindow>

#include "graph.h"


#define INF  100000

class Dijkstra : public QThread {
    Q_OBJECT

public:
    Dijkstra (Graph *g, int index , QMainWindow *qMain, QObject *parent=0 );

    Graph *getGraph();
    Vertex * popMenor();
    void pintar(Vertex **);
    ~Dijkstra () ;

protected:
    void run();

signals:
    void update ( Graph * );

private:
    int index;
    Graph *grafo,*f;
    QList <Vertex*> lista;
    void dijkstra ();
};
/*
#include <QThread>
#include <QList>
#include "grafo.h"
#include "vertice.h"



class Dijkstra : public QThread
{
    Q_OBJECT
    public:
        void setParameters(Grafo * g, int initial, int final) {
            this->grafo = g;
            this->VerticeInitial = initial;
            this->VerticeFinal = final;
        }

        void run() {
            metodoDijkstra(VerticeInitial);
        }
    private:
        int tempo;
        int VerticeInitial;
        int VerticeFinal;
        Grafo *grafo;
        QList<Vertice *> lista;
    signals:
        void sinalDijkstra();

    public:
        void metodoDijkstra( int indexVerticeInicial ) {
            qDebug() << "chegou metodoDijkstra";
            Vertice *verticeAtual, *vertice;
            Aresta *aresta;
            Vertice **V = grafo->getVertice();

            for ( int i = 0; i < grafo->getVerticeCount(); i++ ) {
                V[i]->setCor(Qt::white);
                V[i]->setPai(NULL);
                V[i]->setDistancia(INFINITO);
                qDebug() << "dentro do for";
            }

            V[indexVerticeInicial]->setCor(Qt::gray);
            emit sinalDijkstra();
            sleep(1);
            qDebug() << "Pintou cinza";
            V[indexVerticeInicial]->setDistancia(0);
            qDebug() << "Vai inserir Lista";
            lista.append(V[indexVerticeInicial]);
            while (!lista.empty()) {
                vertice = popMenor();
                vertice->setCor(Qt::black);
                emit sinalDijkstra();
                sleep(1);
                qDebug() << "Pintou Preto";
                for ( aresta = vertice->getAresta(); aresta != NULL; aresta = aresta->getNext() ) {
                    verticeAtual = V[aresta->getIdV2()];
                    if ( ( vertice->getDistancia() + aresta->getW()) < ( verticeAtual->getDistancia() ) ) {
                        verticeAtual->setDistancia( vertice->getDistancia() + aresta->getW() );
                        verticeAtual->setPai(vertice);
                    }
                    if ( verticeAtual->getCor() == Qt::white ) {
                        verticeAtual->setCor(Qt::gray);
                        emit sinalDijkstra();
                        sleep(2);
                        qDebug() << "Pintou Cinza";
                        lista.append(verticeAtual);
                    }
                }
            }
        }

        Vertice* popMenor(){
            int menor = 0;
            for (int i= 0; i < lista.size(); i++ ) {
                if ( lista.at(i)->getDistancia() < lista.at(menor)->getDistancia() ) {
                    menor = i;
                }
            }
            qDebug() << "Menor: " << lista.at(menor)->getNome();
            return lista.takeAt(menor);
        }


};*/

#endif // DIJKSTRA_H
