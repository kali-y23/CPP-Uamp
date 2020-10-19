#include <iomanip>
#include <iostream>

#include <QApplication>
#include <mainwindow.h>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile File(":/qmain.qss");
    QString StyleSheet;
    MainWindow w;

    File.open(QFile::ReadOnly);
    StyleSheet = QLatin1String(File.readAll());
    app.setStyleSheet(StyleSheet);
    w.show();
    return app.exec();
}
