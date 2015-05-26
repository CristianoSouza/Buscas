#include "Grafo.h"

#include <QFile>

Grafo::Grafo ( int n, QMainWindow *main, QWidget *pai ) : QWidget (pai)  {
    this->main    = main;
    this->arestas   = NULL;
    this->vertice.clear();
    this->max     = n;
    this->quantidadeVertices   = 0;


}

void Grafo::pintar () {

    QPainter pintor(main);

    // Pintar primeiramente as arestas
    for (Aresta *aresta=arestas; aresta; aresta= aresta->getProximo() ) {
        pintor.setPen( Qt::black);
        aresta->pintar( getVertice(aresta->getverticeOrigem())->getPonto(), getVertice(aresta->getverticeDestino())->getPonto(), pintor );
    }
    QHashIterator<QString, Vertice*> i(vertice);
    while (i.hasNext()) {
        getVertice(i.next().key())->pintar(pintor);
    }
}


Vertice* Grafo::getVertice ( QString indiceVertice ) {
    return vertice.value(indiceVertice);
}

void Grafo::adicionarVertice ( QString nome, QPoint ponto ) {
    //if (quantidadeVertices<max) {
        qDebug() << "Adicionando vértice " << nome;

        vertice.insert(nome,new Vertice( 1, nome.toUpper(), ponto ));
        //quantidadeVertices++;
    //} else
        //qDebug() << "Número de vértices maior que o informado!";
}

bool Grafo::adicionarAresta ( QString verticeOrigem, QString verticeDestino, int peso, QColor cor ) {
    qDebug() << "Adicionando Aresta " << verticeOrigem << " - " << verticeDestino;
    if ((verticeOrigem.isEmpty()) || (verticeDestino.isEmpty())) {
        qDebug() << "Vértice de [origem|destino] não encontrado: " << verticeOrigem << ", " << verticeDestino;
        return false;
    }
    Aresta::acrescentar( &arestas, verticeOrigem, verticeDestino, peso, cor ); //adiciona a lista de arestas

    //vertice[getVerticeIndice(verticeOrigem)]->acrescentar( verticeDestino, peso, cor );
    Vertice *aux = vertice.find(verticeOrigem).value();
    aux->acrescentar( verticeDestino, peso, cor );
    return true;
}

QString Grafo::getCaminho( QString nome ) {
    QString s = "", nomeVertice= "";
    Aresta *arestaPai, *aresta;
    Vertice *vertice = this->vertice.find(nome).value();
    while (vertice!=NULL) {
        s += vertice->getNome()+ ",";
        nomeVertice = vertice->getNome();
        arestaPai = vertice->getArestaPai();
        for(aresta = vertice->getArestas(); aresta; aresta = aresta->getProximo()) {
            qDebug() << "Aresta: " << aresta->getverticeOrigem() << " -- "<< aresta->getverticeDestino() <<"";
            qDebug() << "Aresta Pai: " << arestaPai->getverticeOrigem() << " -- "<< arestaPai->getverticeDestino() <<"";
            if ( aresta->getverticeDestino() == arestaPai->getverticeDestino()) {
                aresta->setCor(Qt::red);
                break;
            }
        }
        vertice = vertice->getPai();

    }

    return s;
}

Aresta *Grafo::getArestas() {
    return arestas;
}

QHash<QString, Vertice*> Grafo::getVertice ()    {
    return this->vertice;
}

QHash<QString, Aresta*> Grafo::getCaminhoArestas()    {
    return this->caminhoArestas;
}

int Grafo::getQuantidadeVertice()  {
    return this->quantidadeVertices;
}

QString Grafo::carregarDoArquivo( QString nomeArquivo ) {
    QString v="", c="";

    QFile arquivo( nomeArquivo );
    if(!arquivo.open(QIODevice::ReadOnly)) {
        qDebug() << "error " << arquivo.errorString();
        QMessageBox::critical(this, "Lendo arquivo", "Erro na leitura do arquivo selecionado");
        return "";
    }
    QTextStream in(&arquivo);

    QString linhaLida;
    QStringList split;
    QStringList nomeVertice;
    QStringList cordX;
    QStringList cordY;
    QStringList origem;
    QStringList destino;
    QStringList peso;
    int n = in.readLine().toInt();
    while(!in.atEnd() && n) {
        linhaLida = in.readLine();
        //line = 1,100,100 ==> nome vértice, coordenada x, coordenada y
        split = linhaLida.split(",");
        if (split.count()==3) {
            nomeVertice= split[0].split("(");

            cordX= split[1].split("=");
            cordY= split[2].split("=");

            cordY = cordY[1].split(")");

            adicionarVertice ( nomeVertice[1], QPoint(cordX[1].toInt(), cordY[0].toInt()));
            v  += c + split[0];  c   = ";";
        } else {
            QMessageBox::critical(this,"Carregar vértices", "Erro na estrutura do arquivo - nós [node, coord. x, coord. y]!");
            return "";
        }
        n--;
    }
    while(!in.atEnd() && !linhaLida.isEmpty()) {
        linhaLida = in.readLine();   // line = (1,2,5)
        linhaLida = linhaLida.mid(1, linhaLida.length() -2 );  // line = 1,2,5
        split = linhaLida.split(",");

        if (split.count()==3){
            origem = split[0].split("=");

            destino= split[1].split("=");
            peso= split[2].split("=");

            peso = peso[1].split(")");

            adicionarAresta(origem[1], destino[1], peso[0].toInt() );
        }else {
            QMessageBox::critical(this,"Carregar arestas", "Erro na estrutura do arquivo - nós [node, coord. x, coord. y]!");
            return "";
        }
    }

    qDebug() << "Carregado com sucesso!";
    arquivo.close();

    return v;
}

QString Grafo::BuscaArrestasDeDeterminadoVertice( QString nomeArquivo, Vertice * vertice ) {
    qDebug() << "BuscaArrestasDeDeterminadoVertice!";
    qDebug() << vertice;

    QString v="", c="";

    QFile arquivo( nomeArquivo );
    if(!arquivo.open(QIODevice::ReadOnly)) {
        qDebug() << "error " << arquivo.errorString();
        QMessageBox::critical(this, "Lendo arquivo", "Erro na leitura do arquivo selecionado");
        return "";
    }
    QTextStream in(&arquivo);

    QString linhaLida;
    QStringList split;
    QStringList origem;
    QStringList destino;
    QStringList peso;

    int n = in.readLine().toInt();
    while(!in.atEnd() && n) {
        linhaLida = in.readLine();
        n--;
    }

    qDebug() << "Lendo Arestas!";
    while(!in.atEnd() && !linhaLida.isEmpty()) {
        qDebug() << "while leitura de arrestas";
        linhaLida = in.readLine();   // line = (1,2,5)
        linhaLida = linhaLida.mid(1, linhaLida.length() -2 );  // line = 1,2,5
        split = linhaLida.split(",");
        if (split.count()==3){
            qDebug() << "NOME VERTICE:" << vertice->getNome();
            qDebug() << "split[0]:" << split[0].toUpper();
            origem = split[0].split("=");
            if (origem[1].toUpper() == vertice->getNome()) {

                destino= split[1].split("=");
                peso= split[2].split("=");

                peso = peso[1].split(")");

                adicionarAresta(origem[1], destino[1], peso[0].toInt(), Qt::black );

                qDebug() << "Carregando arresta: " << origem[1] << " -> "<< destino[1] << " - "<< peso[0].toInt();
                qDebug() << "Buscando Vertice: " << destino[1];
                BuscaVerticesAdj(nomeArquivo, destino[1]);
            }
        } else {
            QMessageBox::critical(this,"Carregar arestas", "Erro na estrutura do arquivo - nós [node, coord. x, coord. y]!");
            return "";
        }
    }

    qDebug() << "Carregado com sucesso!";
    arquivo.close();

    return v;
}

void Grafo::dispose ( ) {
    vertice.clear();
    arestas = NULL;
}

QString Grafo::BuscaVerticeRaiz( QString nomeArquivo ) {


    QString v="", c="";

    QFile arquivo( nomeArquivo );
    if(!arquivo.open(QIODevice::ReadOnly)) {
        qDebug() << "error " << arquivo.errorString();
        QMessageBox::critical(this, "Lendo arquivo", "Erro na leitura do arquivo selecionado");
        return "";
    }
    QTextStream in(&arquivo);

    QString linhaLida;
    QStringList split;
    QStringList nomeVertice;
    QStringList cordX;
    QStringList cordY;

    int n = in.readLine().toInt();
    linhaLida = in.readLine();
        //line = 1,100,100 ==> nome vértice, coordenada x, coordenada y
    split = linhaLida.split(",");
    if (split.count()==3) {
        nomeVertice= split[0].split("(");

        cordX= split[1].split("=");
        cordY= split[2].split("=");

        cordY = cordY[1].split(")");

        adicionarVertice ( nomeVertice[1], QPoint(cordX[1].toInt(), cordY[0].toInt()));

        v  += c + nomeVertice[1];  c   = ";";
    } else {
        QMessageBox::critical(this,"Carregar vértices", "Erro na estrutura do arquivo - nós [node, coord. x, coord. y]!");
        return "";
    }

    qDebug() << "Carregado com sucesso!";
    arquivo.close();

    return v;
}

QString Grafo::BuscaVerticesAdj( QString nomeArquivo, QString nomeVert ) {
    QString v="", c="";

    QFile arquivo( nomeArquivo );
    if(!arquivo.open(QIODevice::ReadOnly)) {
        qDebug() << "error " << arquivo.errorString();
        QMessageBox::critical(this, "Lendo arquivo", "Erro na leitura do arquivo selecionado");
        return "";
    }
    QTextStream in(&arquivo);

    QString linhaLida;
    QStringList split;
    QStringList nomeVertice;
    QStringList cordX;
    QStringList cordY;

    int n = in.readLine().toInt();

    while(!in.atEnd() && n) {
        linhaLida = in.readLine();
        //line = 1,100,100 ==> nome vértice, coordenada x, coordenada y
        split = linhaLida.split(",");
        if (split.count()==3) {
            nomeVertice= split[0].split("(");
            if (nomeVertice[1] == nomeVert) {
                nomeVertice= split[0].split("(");

                cordX= split[1].split("=");
                cordY= split[2].split("=");

                cordY = cordY[1].split(")");

                adicionarVertice ( nomeVertice[1], QPoint(cordX[1].toInt(), cordY[0].toInt()));
                v  += c + nomeVertice[1];  c   = ";";
            }
        } else {
            QMessageBox::critical(this,"Carregar vértices", "Erro na estrutura do arquivo - nós [node, coord. x, coord. y]!");
            return "";
        }
        n--;
    }

    qDebug() << "Carregado com sucesso!";
    arquivo.close();

    return v;
}


Grafo::~Grafo ( ) {
    qDebug() << "Eliminando o Graph";
    dispose();
}
