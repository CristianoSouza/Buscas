#include "Vertice.h"


Vertice::Vertice ( int indiceVertice, QString nome, QPoint ponto, QObject *pai ) : QObject(pai) {
    this->indiceVertice = indiceVertice;
    this->nome   = nome;
    this->peso   = 0;

    this->tempoEntrada = 0;
    this->tempoSaida = 0;
    this->ponto = ponto;
    this->cor  = Qt::white;
    this->pai = NULL;
    this->arestas  = NULL;
    this->set    = QString::number(indiceVertice);
}

QString Vertice::getSET () {
    return this->set;
}

int Vertice::getIndiceVertice() {
    return this->indiceVertice;
}

QString Vertice::getNome() {
    return this->nome;
}

QColor Vertice::getCor() {
    return this->cor;
}

Aresta *Vertice::getArestas() {
    return this->arestas;
}

Vertice *Vertice::getPai() {
    return this->pai;
}

int Vertice::getPeso() {
    return this->peso;
}

int Vertice::getTempoEntrada() {
    return this->tempoEntrada;
}

int Vertice::getTempoSaida() {
    return this->tempoSaida;
}

QPoint Vertice::getPonto () {
    return this->ponto;
}

void Vertice::setSET ( QString newSet ) {
    this->set = newSet;
}

void Vertice::acrescentar( int indiceAdj, int peso, QColor cor )  {
    Aresta::acrescentar( &arestas, indiceVertice, indiceAdj, peso, cor );
}

void Vertice::setPai( Vertice *pai ) {
    this->pai = pai;
}

void Vertice::setPeso ( int peso) {
    this->peso = peso;
}

void Vertice::setTempoEntrada ( int tempoEntrada ) {
    this->tempoEntrada  = tempoEntrada;
}

void Vertice::setTempoSaida ( int tempoSaida ) {
    this->tempoSaida = tempoSaida;
}

void Vertice::setCor ( QColor cor ) {
    this->cor = cor;
}

Vertice *Vertice::clonar () {
    return new Vertice (indiceVertice, nome, ponto, this->parent() );
}

void Vertice::pintar ( QPainter &pintor ) {
    pintor.setBrush ( cor );
    pintor.setPen( (cor==Qt::white)? Qt::black : Qt::white );
    pintor.drawEllipse( ponto.x()-20,  ponto.y()-20, 40, 40 );

    QRect rect ( ponto.x()-4,  ponto.y()-8, ponto.x()+4,  ponto.y()+8 );
    pintor.drawText( rect, nome );


    // colocar peso?
    // setar o pai?
}

Vertice::~Vertice() {
    qDebug() << "Excluindo vertice " << nome;
    if (this->arestas!=NULL)
        delete this->arestas;
}

