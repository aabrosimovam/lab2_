#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include "matrix.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    //точка зрения
    float x0 = 10;
    float y0 = 7;
    float z0 = 5;
    //координаты центра поля и полуосей поля
    int xc = 435;
    int yc = 275;
    int xe = 200;
    int ye = 200;
    //матрицы, нужные чтоб перейти от одной системы координат к другой
    Matrix T;
    Matrix S;
    Matrix Rx90;
    Matrix Ry;
    Matrix Rx;
    Matrix V;
    //координаты вершин
    float Ver[12][3] = {{0,0,0},{5,0,0},{0,5,0},{0,0,5},{1,-1,-1},{1,1,-1},{-1,1,-1},{-1,-1,-1},{1,-1,1},{1,1,1},{-1,1,1},{-1,-1,1}};
    //копия координат вершин (чтобы действия производились с изначальными вершинами, а не с поменяными)
    float NewVer[12][3] = {{0,0,0},{5,0,0},{0,5,0},{0,0,5},{1,-1,-1},{1,1,-1},{-1,1,-1},{-1,-1,-1},{1,-1,1},{1,1,1},{-1,1,1},{-1,-1,1}};
    //массив ребер
    int Reb[15][2] = {{0,1},{0,2},{0,3},{4,5},{4,7},{4,8},{5,6},{5,9},{6,7},{6,10},{7,11},{8,9},{8,11},{9,10},{10,11}};
    //массивы вершин для картинной и экранной систем координат
    float VerKa[12][2];
    float VerEk[12][2];

    int P = 4;

public:
    Widget(QWidget *parent = nullptr);
    void SKM_SKN();//переход от мировой системы к системе координат наблюдателя
    void SKN_SKK();//от наблюдателя к картинной
    void SKK_SKEi();//от картинной к экранной
    void print_scene();//рисуем куб
    void updateMatr();//обновляем матрицы
    ~Widget();//деструктор

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QTimer *timer;

public slots:
    void Draw();//это вызывается по таймеру, все рисуется и вращается
};
#endif // WIDGET_H
