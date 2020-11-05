#pragma once

#include "mainwindow.h"


enum class ButtonType {
    Play,
    Loop,
    Shuffle,
    Playlist
};

class QSuperButton : public QToolButton {
    Q_OBJECT

    QList<QIcon> list;
    int index;

public:
    QSuperButton(ButtonType type, QWidget *parent = nullptr);
    ~QSuperButton();

private:
    void createPlayList(void);
    void createLoopList(void);
    void createShuffleList(void);
    void createPlaylistList(void);

signals:
    void indexChanged(int index);

public slots:
    void click();
    void emitIndex();
};
