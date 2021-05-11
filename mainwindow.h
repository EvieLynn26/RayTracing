#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include"ZM.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//size_t cnt;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ZM ll;

    /*void drawGraph(bool notEmpty = 0);
    void recountPixels();
    void getData();
    double f(double x);
    double f1(double x);
    double f2(double x);
    double f3(double x);

    void paintEvent(QPaintEvent * );
    void drawBase(QPainter &paint);
    void drawHours(QPainter &paint, double alpha);
    void drawMinutes(QPainter &paint, double alpha);
    void drawSeconds(QPainter &paint, double alpha);
    void drawCenter(QPainter &paint);
    void clear(QPainter &paint);
    void timerEvent(QTimerEvent *);
    void initTime();
    void recountTime();
    QPair<double, double> getPoint(double nowX, double nowY, double alpha);
*/
private slots:
    void on_pushButton_clicked();

    void on_exitButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_doubleSpinBox_3_valueChanged(double arg1);

private:
    Ui::MainWindow *ui; // форма

    double leftX,rightX;
    double leftY,rightY;
    int pictWidth,pictHeight;
    double step;
    double onePixelX,onePixelY;
    double Ox,Oy;
};


#endif // MAINWINDOW_H
