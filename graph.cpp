#include "graph.h"
#include "ui_graph.h"

#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QScrollBar>

Graph::Graph(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Graph)
{
    ui->setupUi(this);

    ui->field->setRenderHint(QPainter::Antialiasing);
    ui->field->verticalScrollBar()->installEventFilter(this);
    ui->field->horizontalScrollBar()->installEventFilter(this);

    _scene = new QGraphicsScene(this);
    ui->field->setScene(_scene);
}

Graph::~Graph()
{
    _scene->clear();
    delete ui;
}

bool Graph::xmlParser(const QString& filename)
{
    QDomDocument doc;
       QFile file(filename);
       if (!doc.setContent(&file)){
             QMessageBox::warning(nullptr, "Warning!","Bad xml format"); return false;
       }

      _node = new Node();
      QDomElement docElem = doc.documentElement();
      _node->setText(docElem.tagName());

      treeMaker(docElem, _node);

      return true;
}

void Graph::treeMaker(const QDomElement& docElem, Node* node)
{
    if(docElem.isNull())
        return;

    if(docElem.childNodes().isEmpty())
        return;

    for(int i = 0; i < docElem.childNodes().size(); i++){
        if(docElem.childNodes().item(i).toElement().tagName() == NULL)
            continue;

        Node* temp = new Node();
        temp->setText(docElem.childNodes().item(i).toElement().tagName());
        node->addChild(temp);
        treeMaker(docElem.childNodes().item(i).toElement(), temp);
    }
}

void Graph::PaintTree(Node *node)
{
    if(node == nullptr)
        return;

    if(node->getChildrien().isEmpty()){
        node->setShape(QRect (_rightOffset + 20, node->getY_coord(), 80, 60) );
        _rightOffset = node->getShape().right();
        _scene->addItem(node);
        return;
    }

    for(int i = 0; i < node->getChildrien().count(); i++)
    {
        PaintTree(node->getChildrien()[i]);
    }

    double x_coord = 0;

    x_coord += node->getChildrien().first()->getShape().x();
    x_coord += node->getChildrien().last()->getShape().x();

    x_coord /= 2;

    if(node->getChildrien().count() > 4 ){
        node->setOffset(node->getChildrien().count() * 10);
        node->setY_coord(node->getY_coord() - node->getOffset());
    }

    int mostOffset = 0;

    for(int i = 0; i < node->getChildrien().count(); i++){
        if(node->getChildrien()[i]->getOffset() > mostOffset)
            mostOffset = node->getChildrien()[i]->getOffset();
    }
    node->setY_coord(node->getY_coord() - mostOffset);
    node->setOffset(node->getOffset() + mostOffset);

    node->setShape(QRectF (x_coord, node->getY_coord(), 80, 60) );

    _scene->addItem(node);

    for(int i = 0; i < node->getChildrien().count(); i++){
        _scene->addItem(new Edge(node, node->getChildrien()[i]));
    }

}

void Graph::on_OpenFile_clicked()
{
    QString FilePath = QFileDialog::getOpenFileName(this, ("Open File"),
                                                        "/file", ("xml File(*.xml)"));
    if(FilePath.isEmpty()){
        QMessageBox::warning(nullptr, "Warning!","File was not opened"); return;
    }

    _scene->clear();
    _rightOffset = 0;

    if(xmlParser(FilePath)){
        PaintTree(_node);
    }
}

void Graph::wheelEvent(QWheelEvent* event)
{

    if(event->angleDelta().y() > 0)
        ui->field->scale(1.25, 1.25);
    else
        ui->field->scale(0.8, 0.8);
}

bool Graph::eventFilter(QObject *object, QEvent *event)
{
        if (object == ui->field->verticalScrollBar() && event->type() == QEvent::Wheel)  {
            return true;
        }
        if (object == ui->field->horizontalScrollBar() && event->type() == QEvent::Wheel)  {
            return true;
        }

        return false;
}
