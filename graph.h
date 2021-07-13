#ifndef GRAPH_H
#define GRAPH_H

#include <QMainWindow>
#include "node.h"
#include "edge.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Graph; }
QT_END_NAMESPACE

class Graph : public QMainWindow
{
    Q_OBJECT

public:
    Graph(QWidget *parent = nullptr);
    ~Graph();

    bool xmlParser(const QString& filename);
    void PaintTree(Node *node);

private slots:
    void on_OpenFile_clicked();

private:
    Ui::Graph *ui;
    Node* _node;
    QGraphicsScene* _scene;
    int _rightOffset = 0;
    
    void treeMaker(const QDomElement& docElem, Node* node);
    void wheelEvent(QWheelEvent*) override;
    bool eventFilter(QObject* object, QEvent* event) override;

};
#endif // GRAPH_H
