#include "Aresta.h"

Aresta::Aresta ( QString verticeOrigem, QString verticeDestino, int peso, QColor cor, QObject *pai ) : QObject(pai) {
    this->verticeOrigem    = verticeOrigem;    // source of edges
    this->verticeDestino = verticeDestino; // adjacent of edges
    this->peso     = peso;

    this->proximo = NULL;
    this->cor = cor;
}

void Aresta::setCor ( QColor valor ) {
    this->cor = valor;
}

void Aresta::pintar(QPoint ponto1, QPoint ponto2, QPainter &pintor ) {
    //qDebug() << "Aresta: " << ponto1 <<"-"<< ponto2 << " -- Cor : " << cor;
    pintor.setPen( cor );
    pintor.drawLine ( ponto1, ponto2 );

    int x = (ponto1.x()+ponto2.x())/2;
    int y = (ponto1.y()+ponto2.y())/2;
    QRect rect ( x-4,  y, x,  y );
    pintor.drawText ( rect, QString::number(peso) );
}

int Aresta::getPeso()  {
    return this->peso;
}

QString Aresta::getverticeOrigem() {
    return this->verticeOrigem;
}

QString Aresta::getverticeDestino() {
    return this->verticeDestino;
}

QColor Aresta::getCor () {
    return this->cor;
}

Aresta *Aresta::getProximo() {
    return this->proximo;
}

void Aresta::acrescentar( Aresta **aresta, QString verticeOrigem, QString verticeDestino, int peso, QColor cor ) {
    if (*aresta==NULL)
        *aresta = new Aresta ( verticeOrigem, verticeDestino, peso, cor );
    else
        acrescentar( &(*aresta)->proximo, verticeOrigem, verticeDestino, peso, cor );
}

Aresta* Aresta::removeMenor( Aresta **arestas, Aresta *aresta ) {
    if (*arestas) {
        if (!aresta) aresta=*arestas;

        if ((*arestas)->getPeso() < aresta->getPeso())
            aresta = removeMenor( &(*arestas)->proximo,*arestas);
        else
            aresta = removeMenor( &(*arestas)->proximo,aresta);

        if (aresta==*arestas) {
            *arestas = aresta->getProximo();
            aresta->proximo = NULL;
        }
    }
    return aresta;
}

Aresta* Aresta::clonar ( Aresta *aresta ) {
    if (aresta) {
        Aresta *arestaClone = new Aresta(aresta->getverticeOrigem(), aresta->getverticeDestino(),aresta->getPeso(), aresta->getCor() );
        arestaClone->proximo = clonar(aresta->proximo);
        return arestaClone;
    }
    return NULL;
}

Aresta::~Aresta() {
    qDebug() << "Excluindo aresta (" << verticeOrigem <<","<<verticeDestino<<"," << peso << ")";
    if (this->proximo!=NULL)
        delete this->proximo;
}

