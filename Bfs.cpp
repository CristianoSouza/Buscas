#include "Bfs.h"

Bfs::Bfs( Grafo *grafo, QString verticeFinal, QString nomeArquivo, QObject *parent) : QThread(parent) {
    this->grafo = grafo;
    this->verticeFinal = verticeFinal;
    this->nomeArquivo = nomeArquivo;
    this->achou = false;
}

Bfs::~Bfs () {
    delete grafo;
}

void Bfs::run () {
    metodoBFS();
}

bool Bfs:: metodoBFS() {
    qDebug() << "Metodo BFS";

    QList<Vertice *> lista;
    Vertice *verticeAtual, *vertice;
    Aresta *aresta;
    grafo->BuscaVerticeRaiz(nomeArquivo);
    QHash <QString,Vertice*>ListaVertices = grafo->getVertice();

    ListaVertices.value(ListaVertices.begin().key())->setPeso(0);
    ListaVertices.value(ListaVertices.begin().key())->setCor(Qt::gray);
    emit update(grafo);
    sleep(1);

    lista.append(ListaVertices.value(ListaVertices.begin().key()));
    qDebug() << "aaaaaaaa";


    if ( ListaVertices.value(ListaVertices.begin().key())->getNome().toLower() == verticeFinal.toLower()) {
        ListaVertices.value(ListaVertices.begin().key())->setCor(Qt::green);
        qDebug() << "SACHOU SAPOHA ";
        emit update(grafo);
        sleep(1);
        return true;
    } else {

        while (!lista.empty()) {
            qDebug() << "Lista" << lista;
            vertice = lista.takeFirst();

            grafo->BuscaArrestasDeDeterminadoVertice( nomeArquivo, vertice );
            emit update(grafo);
            sleep(1);

            for ( aresta = vertice->getArestas(); aresta; aresta = aresta->getProximo() ) {
                qDebug()<<"for aresta";
                qDebug() << "vertice destino da aresta " << aresta->getverticeDestino();
                qDebug() << "Verttice destino " << aresta->getverticeDestino();
                verticeAtual= grafo->getVertice(aresta->getverticeDestino());
                qDebug()<<"Vertice Atual" << verticeAtual;
                //verticeAtual = ListaVertices[aresta->getIndiceAdj()];
                qDebug() << "IF";
                if ( verticeAtual->getCor() == Qt::blue ) {

                    verticeAtual->setPai(vertice);
                    verticeAtual->setPeso(vertice->getPeso() + 1 );

                    if ( verticeAtual->getNome().toLower() == verticeFinal.toLower()) {
                        verticeAtual->setCor(Qt::green);
                        emit update(grafo);
                        sleep(1);
                        qDebug() << "uPDATE GRAFO";
                        qDebug() << "SACHOU SAPOHA";
                        this->achou = true;
                        break;
                    }
                    qDebug() << "entrou IF";
                    verticeAtual->setCor(Qt::gray);

                    emit update(grafo);
                    sleep(1);
                    qDebug() << "uPDATE GRAFO";

                    verticeAtual->setPai(vertice);
                    verticeAtual->setPeso(vertice->getPeso() + 1 );

                    grafo->BuscaArrestasDeDeterminadoVertice( nomeArquivo, verticeAtual );
                    emit update(grafo);
                    sleep(1);

                    lista.append(verticeAtual);
                }
                qDebug() << "fim do ciclo";
            }
            vertice->setCor(Qt::black);
            emit update(grafo);
            sleep(1);
            qDebug() << "Emitiu sinal";
            if ( this->achou ) {
                qDebug("return true");
                return true;
            }

        }
    }
}


