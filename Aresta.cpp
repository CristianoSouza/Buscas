#include "Aresta.h"

Aresta::Aresta ( int indice, int indiceAdj, int peso, QColor cor, QObject *pai ) : QObject(pai) {
    this->indice    = indice;    // source of edges
    this->indiceAdj = indiceAdj; // adjacent of edges
    this->peso     = peso;

    this->proximo = NULL;
    this->cor = cor;
}

void Aresta::setCor ( QColor valor ) {
    this->cor = valor;
}

void Aresta::pintar(QPoint ponto1, QPoint ponto2, QPainter &pintor ) {
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

int Aresta::getIndice() {
    return this->indice;
}

int Aresta::getIndiceAdj() {
    return this->indiceAdj;
}

QColor Aresta::getCor () {
    return this->cor;
}

Aresta *Aresta::getProximo() {
    return this->proximo;
}

void Aresta::acrescentar( Aresta **aresta, int indice, int indiceAdj, int peso, QColor cor ) {
    if (*aresta==NULL)
        *aresta = new Aresta ( indice, indiceAdj, peso, cor );
    else
        acrescentar( &(*aresta)->proximo, indice, indiceAdj, peso, cor );
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
        Aresta *arestaClone = new Aresta(aresta->getIndice(), aresta->getIndiceAdj(),aresta->getPeso(), aresta->getCor() );
        arestaClone->proximo = clonar(aresta->proximo);
        return arestaClone;
    }
    return NULL;
}

Aresta::~Aresta() {
    qDebug() << "Excluindo aresta (" << indice <<","<<indiceAdj<<"," << peso << ")";
    if (this->proximo!=NULL)
        delete this->proximo;
}

