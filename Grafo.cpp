#include "Grafo.h"

#include <QFile>

Grafo::Grafo ( int n, QMainWindow *main, QWidget *pai ) : QWidget (pai)  {
    this->main    = main;
    this->arestas   = NULL;
    this->vertice  = NULL;
    this->max     = n;
    this->quantidadeVertices   = 0;

    resize(n);
}

void Grafo::pintar () {

    QPainter pintor(main);

    // Pintar primeiramente as arestas
    for (Aresta *aresta=arestas; aresta; aresta= aresta->getProximo() ) {
        aresta->pintar( getVerticeAt(aresta->getIndice())->getPonto(),
                 getVerticeAt(aresta->getIndiceAdj())->getPonto(),
                 pintor );
    }

    for (int i=0; i<quantidadeVertices; i++) {
        getVerticeAt(i)->pintar(pintor);
    }
}

void Grafo::resize ( int n ) {
    dispose();
    this->max    = n;
    this->quantidadeVertices  = 0;
    this->vertice = new Vertice*[max];
    for (int i=0; i<max; i++) {
        vertice[i] = NULL;
    }
}

int Grafo::getVerticeIndice ( QString nome ) {
    for (int i=0; i<quantidadeVertices; i++)
        if ((vertice[i]!=NULL) && (vertice[i]->getNome()==nome.toUpper()))
            return i;
    return -1;
}

Vertice* Grafo::getVerticeAt ( int indice ) {
    return (indice<quantidadeVertices)? vertice[indice] : NULL;
}

void Grafo::adicionarVertice ( QString nome, QPoint ponto ) {
    if (quantidadeVertices<max) {
        qDebug() << "Adicionando vértice " << nome;
        vertice[quantidadeVertices] = new Vertice(quantidadeVertices, nome.toUpper(), ponto );
        quantidadeVertices++;
    } else
        qDebug() << "Número de vértices maior que o informado!";
}

bool Grafo::adicionarAresta ( QString origem, QString destino, int peso, QColor cor ) {
    int verticeOrigem = getVerticeIndice(origem.toUpper());
    int verticeDestino = getVerticeIndice(destino.toUpper());
    if ((verticeOrigem==-1) || (verticeDestino==-1)) {
        qDebug() << "Vértice de [origem|destino] não encontrado: " << origem << ", " << destino;
        return false;
    }
    Aresta::acrescentar( &arestas, verticeOrigem, verticeDestino, peso, cor ); //adiciona a lista de arestas

    vertice[verticeOrigem]->acrescentar( verticeDestino, peso, cor );
    return true;
}

QString Grafo::getCaminho( QString nome ) {
    QString s = "";
    Vertice *vertice = this->vertice [ getVerticeIndice( nome ) ];
    while (vertice!=NULL) {
        s += vertice->getNome()+ ",";
        vertice = vertice->getPai();
    }
    return s;
}

Aresta *Grafo::getArestas() {
    return this->arestas;
}

Vertice **Grafo::getVertice ()    {
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
    resize(n);

    while(!in.atEnd() && !line.isEmpty()) {
        line = in.readLine();   // line = (1,2,5)
        line = line.mid(1, line.length() -2 );  // line = 1,2,5
        sl = line.split(",");
        if (sl.count()==3){
            if (sl[0] == vertice->getNome()) {
                adicionarAresta(sl[0], sl[1], sl[2].toInt() );
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

void Grafo::dispose () {
    for (int i=0; i<quantidadeVertices; i++)
        delete vertice[i];
    if (vertice)
        delete [] vertice;
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
    resize(n);
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

Grafo::~Grafo ( ) {
    qDebug() << "Eliminando o Graph";
    dispose();
}
