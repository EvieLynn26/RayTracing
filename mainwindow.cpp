#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ZM.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ll.show();
    return;
}

void MainWindow::on_exitButton_clicked()
{
    this->close();
    return;
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
     ll.cnt = arg1;

     return;
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    ll.param_n1 = arg1;

    return;
}

void MainWindow::on_doubleSpinBox_3_valueChanged(double arg1)
{
    ll.param_n2 = arg1;

    return;

}


/*
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QDebug>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pictHeight = 370;
    pictWidth = 540;
    step = 0.1;
    leftX = -100; rightX = 100;
    leftY = -100; rightY = 100;
    drawGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::f(double x)
{
    return log(x)*(-1);
}

double MainWindow::f1(double x)
{
    return sin(x)*(-1);
}

double MainWindow::f2(double x)
{
    return cos(x)*(-1);
}

double MainWindow::f3(double x)
{
    return sin(1.0/x)*(-1);
}

void MainWindow::recountPixels()
{
    onePixelX = 540.0/(rightX-leftX);
    onePixelY = 370.0/(rightY-leftY);
    Ox = fabs(leftX); Oy = rightY;
}

void MainWindow::getData()
{
    leftX = ui->inputLeftX->text().toDouble();
    rightX = ui->inputRightX->text().toDouble();
    leftY = ui->inputLeftY->text().toDouble();
    rightY = ui->inputRightY->text().toDouble();
    step = 1.0/ui->inputAccuracy->text().toDouble();
}

void MainWindow::drawGraph(bool notEmpty)
{
    QPixmap graph(540,370);
    QPainter paint;
    paint.begin(&graph);
    paint.eraseRect(0,0,540,370);
    paint.drawLine(Ox*onePixelX,0,Ox*onePixelX,pictHeight);
    paint.drawLine(0,Oy*onePixelY,pictWidth,Oy*onePixelY);

    paint.setPen(QPen(Qt::black,3));
    for(double i = leftX;i<=rightX;i+=10.0)
        paint.drawPoint((i+Ox)*onePixelX,Oy*onePixelY);
    for(double i = leftY;i<=rightY;i+=10.0)
        paint.drawPoint(Ox*onePixelX,(i+Oy)*onePixelY);

    if(!notEmpty) {
        paint.end();
        ui->outputGraph->setPixmap(graph);
        return;
    }

    paint.setPen(QPen(Qt::green,1,Qt::SolidLine));
    paint.setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path,p[3];
    bool first[4] = {1,1,1,1};

    for(double i = (double)leftX+step;i<=(double)rightX;i+=step) {
        if(!isnan(f(i))) {
            if(first[0]) {
                path.moveTo((i+Ox)*onePixelX,(f(i)+Oy)*onePixelY);
                first[0] = false;
            }
            else
                path.lineTo((i+Ox)*onePixelX,(f(i)+Oy)*onePixelY);
        }
        if(!isnan(f1(i))) {
            if(first[1]) {
                p[0].moveTo((i+Ox)*onePixelX,(f1(i)+Oy)*onePixelY);
                first[1] = false;
            }
            else
                p[0].lineTo((i+Ox)*onePixelX,(f1(i)+Oy)*onePixelY);
        }
        if(!isnan(f2(i))) {
            if(first[2]) {
                p[1].moveTo((i+Ox)*onePixelX,(f2(i)+Oy)*onePixelY);
                first[2] = false;
            }
            else
                p[1].lineTo((i+Ox)*onePixelX,(f2(i)+Oy)*onePixelY);
        }
        if(!isnan(f3(i))) {
            if(first[3]) {
                p[2].moveTo((i+Ox)*onePixelX,(f3(i)+Oy)*onePixelY);
                first[3] = false;
            }
            else
                p[2].lineTo((i+Ox)*onePixelX,(f3(i)+Oy)*onePixelY);
        }
    }

    if(ui->main->isChecked()) {
        paint.setPen(QPen(Qt::blue,1,Qt::SolidLine));
        paint.drawPath(path);
    }
    if(ui->sin->isChecked()) {
        paint.setPen(QPen(Qt::green,1,Qt::SolidLine));
        paint.drawPath(p[0]);
    }
    if(ui->cos->isChecked()) {
        paint.setPen(QPen(Qt::red,1,Qt::SolidLine));
        paint.drawPath(p[1]);
    }
    if(ui->tg->isChecked()) {
        paint.setPen(QPen(Qt::darkMagenta,1,Qt::SolidLine));
        paint.drawPath(p[2]);
    }
    paint.end(); // заканчиваем рисование
    ui->outputGraph->setPixmap(graph); // и помещаем рисунок на форму
    return;
}


void MainWindow::on_clear_clicked()
{
    recountPixels();
    drawGraph();
}

void MainWindow::on_draw_clicked()
{
    getData();
    recountPixels();
    drawGraph(1);
}

void MainWindow::on_save_clicked()
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    QString name;
   if(date.day()<10)
        name += "0";
    name += QString::number(date.day())+".";
    if(date.month()<10)
        name += "0";
    name += QString::number(date.month())+".";
    name += QString::number(date.year())+"_";
    if(time.hour()<10)
        name += "0";
    name += QString::number(time.hour())+"-";
    if(time.minute()<10)
        name += "0";
    name += QString::number(time.minute())+"-";
    if(time.second()<10)
        name += "0";
    name += QString::number(time.second());
    QFile file(name+".png");
    qDebug() << name;
    file.open(QIODevice::WriteOnly);
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok);
    if(ui->outputGraph->pixmap()->save(&file,"PNG")) {
        msgBox.setText("Saved to program folder with name: "+name+".png");
        msgBox.setWindowTitle("Saved!");
    }
    else {
        msgBox.setText("Error saving.");
        msgBox.setWindowTitle("Error!");
    }
    msgBox.exec();
}


#include "clock.h"
#include <QPair>

Clock::Clock(QWidget *parent)
    : QWidget(parent)
{
    resize(300,300);
    Ox=150; Oy=150;
    upX=150; upY=5;
    first=true;
    initTime();
    startTimer(1000);
}

void Clock::timerEvent(QTimerEvent *)
{
    update();
    recountTime();
}

Clock::~Clock()
{

}

void Clock::initTime()
{
    QTime time=QTime::currentTime();
    seconds=time.second();
    minutes=time.minute();
    hours=time.hour();
    alphaSec=6.0*seconds;
    alphaMin=6.0*minutes;
    alphaHours=30.0*hours+minutes*0.5+0.025*seconds/3;
}

void Clock::recountTime()
{
    seconds++;
    minutes += (seconds/60);
    seconds %= 60;
    hours += (minutes/60);
    minutes %= 60;

    alphaSec += 6.0;
    if(alphaSec == 360.0)
        alphaSec = 0.0;

    if(first!=true){
        if(seconds%60 == 0) {
            alphaMin += 6.0;
            alphaHours += 0.5;
        }
        if(alphaMin == 360.0)
            alphaMin = 0.0;
        if(alphaHours == 360.0)
            alphaHours = 0.0;
    }
    else
        first = false;
}

QPair<double,double> Clock::getPoint(double nowX, double nowY, double alpha)
{
    double retX=(nowX-Ox)*cos(alpha*M_PI/180.0)-(nowY-Oy)*sin(alpha*M_PI/180.0)+Ox;
    double retY=(nowY-Oy)*cos(alpha*M_PI/180.0)+(nowX-Ox)*sin(alpha*M_PI/180.0)+Oy;
    if(abs(retX)<1e-9)
        retX=0;
    if(abs(retY)<1e-9)
        retY=0;
    if(retX<0)
        retX=300+retX;
    if(retY<0)
        retY=300+retY;
    return QPair<double,double>(retX,retY);
}

void Clock::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    clear(paint);
    drawBase(paint);
    drawHours(paint,alphaHours);
    drawMinutes(paint,alphaMin);
    drawSeconds(paint,alphaSec);
    drawCenter(paint);
}

void Clock::drawBase(QPainter &paint)
{
    paint.setPen(QPen(Qt::black,3,Qt::SolidLine));
    paint.setRenderHint(QPainter::Antialiasing, true);
    paint.drawEllipse(5,5,290,290);

    paint.setPen(QPen(Qt::black,3,Qt::SolidLine,Qt::RoundCap));
    double nowUpX=295,nowUpY=150,nowDownX=280,nowDownY=150;
    paint.drawLine(nowUpX,nowUpY,nowDownX,nowDownY);

    nowUpX=150; nowUpY=295; nowDownX=150; nowDownY=280;
    paint.drawLine(nowUpX,nowUpY,nowDownX,nowDownY);

    nowUpX=5; nowUpY=150; nowDownX=20; nowDownY=150;
    paint.drawLine(nowUpX,nowUpY,nowDownX,nowDownY);

    nowUpX=150; nowUpY=5; nowDownX=150; nowDownY=20;
    paint.drawLine(nowUpX,nowUpY,nowDownX,nowDownY);

    nowDownY=12;
    for(int i=1;i<=12;++i){
        QPair<double,double> tmp=getPoint(nowUpX,nowUpY,30.0);
        nowUpX=tmp.first; nowUpY=tmp.second;

        tmp=getPoint(nowDownX,nowDownY,30.0);
        nowDownX=tmp.first; nowDownY=tmp.second;

        if(i==12)
            continue;
        paint.drawLine(nowUpX,nowUpY,nowDownX,nowDownY);
    }

    nowDownY=7;
    for(int i=1;i<=60;++i){
        QPair<double,double> tmp = getPoint(nowUpX,nowUpY,6.0);
        nowUpX = tmp.first; nowUpY = tmp.second;

        tmp = getPoint(nowDownX,nowDownY,6.0);
        nowDownX = tmp.first; nowDownY = tmp.second;

        paint.drawLine(nowUpX,nowUpY,nowDownX,nowDownY);
    }
}


void Clock::drawSeconds(QPainter &paint, double alpha)
{
    QPair<double,double> tmp=getPoint(upX,upY+15,alpha);
    paint.setPen(QPen(Qt::darkBlue,1,Qt::SolidLine)); // рисуем синим цветом
    paint.setRenderHint(QPainter::Antialiasing, true);
    paint.drawLine(Ox,Oy,tmp.first,tmp.second);
    tmp=getPoint(upX,100+20,alpha+180.0);
    paint.drawLine(Ox,Oy,tmp.first,tmp.second);
}

void Clock::drawMinutes(QPainter &paint, double alpha)
{
    // всё так же, как и в отрисовке секундной стрелки
    QPair<double,double> tmp=getPoint(upX,upY+15,alpha);
    paint.setPen(QPen(Qt::cyan,2,Qt::SolidLine));
    paint.setRenderHint(QPainter::Antialiasing, true);
    paint.drawLine(Ox,Oy,tmp.first,tmp.second);
}

void Clock::drawHours(QPainter &paint, double alpha)
{
    QPair<double,double> tmp = getPoint(upX,upY+50,alpha);
    paint.setPen(QPen(Qt::blue,2,Qt::SolidLine));
    paint.setRenderHint(QPainter::Antialiasing, true);
    paint.drawLine(Ox,Oy,tmp.first,tmp.second);
}

void Clock::drawCenter(QPainter &paint)
{
    paint.setPen(QPen(Qt::black,6,Qt::SolidLine,Qt::RoundCap));
    paint.setRenderHint(QPainter::Antialiasing, true);
    paint.drawPoint(150,150);
}

void Clock::clear(QPainter &paint)
{
    paint.eraseRect(0,0,300,300);
}
*/

