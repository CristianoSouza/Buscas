#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>

#include "Grafo.h"

#include "Dfs.h"
#include "Bfs.h"

#include <QPainter>
#include <QPaintEvent>

namespace Ui {
class Interface;
}

class Interface : public QMainWindow {
    Q_OBJECT

signals:
    void mostrar ( Grafo *);

public:
    explicit Interface(QWidget *parent = 0);
     void mostrarLista(QList<Vertice *> lista);
     void getCaminho (QString metodo);
     QString getNomeArquivo();
    ~Interface();

public slots:
    void mostrarGrafo ( Grafo * );


private slots:
    void on_actionLoad_triggered();
    void on_actionMostrarArvore_triggered();
    void on_start_clicked();
    void on_pushButton_clicked();

private:
    Ui::Interface *interface;
    Grafo *grafo, *tmp;
    QThread *algoritmo;
    int idmostrar;
    int metodo;
    QString nomeArquivo;
    void executarAlgoritmo ( int i );


protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // INTERFACE_H
