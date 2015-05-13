#include "Grafo.h"

#include <QFile>

Grafo::Grafo ( int n, QMainWindow *main, QWidget *pai ) : QWidget (pai)  {
    this->main    = main;
    this->arestas   = NULL;
    this->vertice.clear();
    this->max     = n;
    this->quantidadeVertices   = 0;

    resize(n);
}

void Grafo::pintar () {

    QPainter pintor(main);

    // Pintar primeiramente as arestas
    for (Aresta *aresta=arestas; aresta; aresta= aresta->getProximo() ) {
        aresta->pintar( getVertice(aresta->getverticeOrigem())->getPonto(),
                 getVertice(aresta->getverticeDestino())->getPonto(),
                 pintor );
    }
    qDebug() << "Pintando Vertices";
    QHashIterator<QString, Vertice*> i(vertice);
    while (i.hasNext()) {
        getVertice(i.next().key())->pintar(pintor);
    }
}

void Grafo::resize ( int n ) {
    /*dispose();
    this->max    = n;
    this->quantidadeVertices  = 0;
    for (int i=0; i<max; i++) {
        vertice[i] = NULL;
    }*/
}

int Grafo::getVerticeIndice ( QString nome ) {
    //for (int i=0; i<quantidadeVertices; i++)
    /*int i = 0;
    while (vertice[i] != NULL) {
        if ((vertice[i]!=NULL) && (vertice[i]->getNome()==nome.toUpper()))
            return i;
        i++;
    }
    return -1;*/
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
    QString s = "";
    Vertice *vertice = this->vertice.find(nome).value();
    while (vertice!=NULL) {
        s += vertice->getNome()+ ",";
        vertice = vertice->getPai();
    }
    return s;
}

Aresta *Grafo::getArestas() {
    return this->arestas;
}

QHash<QString, Vertice*> Grafo::getVertice ()    {
    return this->vertice;
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

    QString line;
    QStringList sl;

    int n = in.readLine().toInt();
    resize(n);
    while(!in.atEnd() && n) {
        line = in.readLine();
        //line = 1,100,100 ==> nome vértice, coordenada x, coordenada y
        sl = line.split(",");
        if (sl.count()==3) {
            adicionarVertice ( sl[0], QPoint(sl[1].toInt(), sl[2].toInt()));
            v  += c + sl[0];  c   = ";";
        } else {
            QMessageBox::critical(this,"Carregar vértices", "Erro na estrutura do arquivo - nós [node, coord. x, coord. y]!");
            return "";
        }
        n--;
    }
    while(!in.atEnd() && !line.isEmpty()) {
        line = in.readLine();   // line = (1,2,5)
        line = line.mid(1, line.length() -2 );  // line = 1,2,5
        sl = line.split(",");
        if (sl.count()==3)
            adicionarAresta(sl[0], sl[1], sl[2].toInt() );
        else {
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

    QString line;
    QStringList sl;

    int n = in.readLine().toInt();
    while(!in.atEnd() && n) {
        line = in.readLine();
        n--;
    }

    qDebug() << "Lendo Arestas!";
    while(!in.atEnd() && !line.isEmpty()) {
        qDebug() << "while leitura de arrestas";
        line = in.readLine();   // line = (1,2,5)
        line = line.mid(1, line.length() -2 );  // line = 1,2,5
        sl = line.split(",");
        if (sl.count()==3){
            qDebug() << "NOME VERTICE:" << vertice->getNome();
            qDebug() << "SL[0]:" << sl[0].toUpper();
            if (sl[0].toUpper() == vertice->getNome()) {
                adicionarAresta(sl[0], sl[1], sl[2].toInt() );
                qDebug() << "Carregando arresta: " << sl[0] << " - "<< sl[1] << " - "<< sl[2].toInt();
                qDebug() << "Buscando Vertice: " << sl[1];
                BuscaVerticesAdj(nomeArquivo,sl[1]);
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

    QString line;
    QStringList sl;

    int n = in.readLine().toInt();
    line = in.readLine();
        //line = 1,100,100 ==> nome vértice, coordenada x, coordenada y
    sl = line.split(",");
    if (sl.count()==3) {
        adicionarVertice ( sl[0], QPoint(sl[1].toInt(), sl[2].toInt()));
        v  += c + sl[0];  c   = ";";
    } else {
        QMessageBox::critical(this,"Carregar vértices", "Erro na estrutura do arquivo - nós [node, coord. x, coord. y]!");
        return "";
    }

    qDebug() << "Carregado com sucesso!";
    arquivo.close();

    return v;
}

QString Grafo::BuscaVerticesAdj( QString nomeArquivo, QString nomeVertice ) {
    QString v="", c="";

    QFile arquivo( nomeArquivo );
    if(!arquivo.open(QIODevice::ReadOnly)) {
        qDebug() << "error " << arquivo.errorString();
        QMessageBox::critical(this, "Lendo arquivo", "Erro na leitura do arquivo selecionado");
        return "";
    }
    QTextStream in(&arquivo);

    QString line;
    QStringList sl;

    int n = in.readLine().toInt();

    while(!in.atEnd() && n) {
        line = in.readLine();
        //line = 1,100,100 ==> nome vértice, coordenada x, coordenada y
        sl = line.split(",");
        if (sl.count()==3) {
            if (sl[0] == nomeVertice) {
                adicionarVertice ( sl[0], QPoint(sl[1].toInt(), sl[2].toInt()));
                v  += c + sl[0];  c   = ";";
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
