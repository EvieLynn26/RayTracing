#include "mainwindow.h"
#include "ZM.h"

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QWidget window;

    //window.resize(250, 150); // изменяем размер виджета в пикселях
    //window.setWindowTitle("Simple example"); // устанавливаем заголовок для главного окна
    //window.show(); // выводим виджет на экран

    //MainWindow w;
    //w.show();

    /*Lines window;

      window.resize(280, 270);
      window.setWindowTitle("Lines");
      window.show();
    */

    MainWindow form;
    form.show();

    return a.exec();
}
