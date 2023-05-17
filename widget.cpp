#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);//устанавливаем сцену
    scene = new QGraphicsScene;

    ui->graphicsView->setScene(scene);

    timer = new QTimer(this);//таймер
    connect(timer,SIGNAL(timeout()),this,SLOT(Draw()));
    timer->start(500);
}

void Widget::updateMatr()//считаем матрицы
{
    float arrT[] = {1,0,0,0,
                    0,1,0,0,
                    0,0,1,0,
                   -x0,-y0,-z0,1};
    float arrS[] = {-1,0,0,0,
                    0,1,0,0,
                    0,0,1,0,
                    0,0,0,1};
    float arrRx90[] = {1,0,0,0,
                       0,0,-1,0,
                       0,1,0,0,
                       0,0,0,1};
    float d = sqrt(x0*x0+y0*y0);
    float arrRy[] = {y0/d,0,x0/d,0,
                       0,1,0,0,
                     -x0/d,0,y0/d,0,
                       0,0,0,1};
    float s = sqrt(x0*x0+y0*y0+z0*z0);
    float arrRx[] = {1,0,0,0,
                       0,d/s,-z0/s,0,
                       0,z0/s,d/s,0,
                       0,0,0,1};
    T = Matrix(4,4,arrT);
    S = Matrix(4,4,arrS);
    Rx90= Matrix(4,4,arrRx90);
    Ry = Matrix(4,4,arrRy);
    Rx = Matrix(4,4,arrRx);
    //сохраняем начальные вершины в NewVer

    for(int i=0;i<12;i++)
    {
        for(int j=0;j<3;j++)
        {
            NewVer[i][j] = Ver[i][j];
        }
    }
}

void Widget::SKM_SKN()
{
  Matrix M();
  V = T;
  V *= S;
  V *= Rx90;
  V *= Ry;
  V *= Rx;
  //Считам матрицу(Вот тут поменялись вершины Ver, для чего и создан был массив NewVer)
  for(int i=0;i<12;i++)
  {
    float M[] = {NewVer[i][0],NewVer[i][1],NewVer[i][2],1};//Тут все по формулам перемножаем
    Matrix Matr(1,4,M);
    Matr*=V;
    float** new_ver = Matr.GetArr();
    NewVer[i][0] = new_ver[0][0];//пересчитали вершины
    NewVer[i][1] = new_ver[0][1];
    NewVer[i][2] = new_ver[0][2];
  }
}

void Widget::SKN_SKK()
{
  //перешли к картинной системе(тут использовалась парралельная проекция)
    for(int i=0;i<12;i++)
    {
        VerKa[i][0] = NewVer[i][0];
        VerKa[i][1] = NewVer[i][1];
    }
}

void Widget::SKK_SKEi()
{
    for(int i =0;i<12;i++)
    {
        VerEk[i][0] = VerKa[i][0]/P*xe+xc;
        VerEk[i][1] = VerKa[i][1]/P*ye+yc;
    }
}

void Widget::print_scene()
{
    for(int i =0;i<15;i++)//рисуем все ребра
    {
        if (i!=7)
        {
            QLineF slide(QPointF(VerEk[Reb[i][0]][0],-VerEk[Reb[i][0]][1]),QPointF(VerEk[Reb[i][1]][0],-VerEk[Reb[i][1]][1]));
            scene->addLine(slide);
        }

    }
    QPen pen;
    pen.setWidth(2);//последнее ребро рисуем жирненьким
    QLineF slide(QPointF(VerEk[Reb[7][0]][0],-VerEk[Reb[7][0]][1]),QPointF(VerEk[Reb[7][1]][0],-VerEk[Reb[7][1]][1]));
    scene->addLine(slide,pen);
}


void Widget::Draw()
{
    scene->clear();//очищаем сцену

    updateMatr();//считаем марицы
    SKM_SKN();
    SKN_SKK();
    SKK_SKEi();//переходим к нужной системе
    print_scene();//рисуем
    if(x0>1)//меняем точку зрения
    {
           x0 -= 1;
           y0 -= 1;
    }

}

Widget::~Widget()
{
    delete ui;
}
