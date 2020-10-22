#include <iomanip>
#include <iostream>

#include "bass.h"

#include "mediator.h"
#include "myDb.h"

int main(int argc, char *argv[])
{
    // BASS_Init (-1, 44100, BASS_DEVICE_3D , 0, NULL);
    // HSTREAM stream;
    // stream = BASS_StreamCreateFile(FALSE, "/Users/mlibovych/Desktop/111.mp3", 0, 0, 0);
    // BASS_ChannelPlay(stream,TRUE);

    QApplication app(argc, argv);
    QFile File(":/qmain.qss");
    QString StyleSheet;
    Mediator *mediator = new Mediator;
    MyDb db;

    File.open(QFile::ReadOnly);
    StyleSheet = QLatin1String(File.readAll());
    app.setStyleSheet(StyleSheet);
    return app.exec();
}
