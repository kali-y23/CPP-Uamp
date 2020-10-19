#include <iomanip>
#include <iostream>

#include "mainwindow.h"
#include "myDb.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    QFile File(":/qmain.qss");
    QString StyleSheet;
    MainWindow w;
    MyDb db;

    File.open(QFile::ReadOnly);
    StyleSheet = QLatin1String(File.readAll());
    app.setStyleSheet(StyleSheet);
    w.show();
    return app.exec();
}
