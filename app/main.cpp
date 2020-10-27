#include <iomanip>
#include <iostream>

#include "bass.h"

#include "mediator.h"
#include "myDb.h"

int main(int argc, char *argv[])
{
    // BASS_Init (-1, 44100, BASS_DEVICE_3D , 0, NULL);
    // HSTREAM stream;
    // stream = BASS_StreamCreateFile(FALSE, "/Users/mlibovych/Desktop/P.I.M.P..mp3", 0, 0, 0);
    // // BASS_ChannelSetPosition(
    // //     stream,
    // //     BASS_ChannelSeconds2Bytes(stream, 15.20),
    // //     BASS_POS_BYTE
    // // );
    // // const TAG_ID3 *id3 = (const TAG_ID3*)BASS_ChannelGetTags(stream, BASS_TAG_ID3);
    // // if (id3)
    // //     std::cout << id3->title << std::endl;
    // BASS_ChannelPlay(stream,FALSE);

    QApplication app(argc, argv);
    QFile File(":/qmain.qss");
    QString StyleSheet;
    Mediator *mediator = new Mediator;
    MyDb db;
    int res = 0;

    File.open(QFile::ReadOnly);
    StyleSheet = QLatin1String(File.readAll());
    app.setStyleSheet(StyleSheet);
    res = app.exec();
    // BASS_Free();

    return res;
}
