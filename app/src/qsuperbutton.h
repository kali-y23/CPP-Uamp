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

public:
    QList<QIcon> list;
    int index;

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
    virtual void click();
    void emitIndex();
};

class QPlayButton : public QSuperButton {
    Q_OBJECT

    QList<void (QPlayButton::*)(void)> signalsList;
    void createPlaySignalList(void);

public:
    QPlayButton(ButtonType type, QWidget *parent = nullptr);
    ~QPlayButton();

public slots:
    void click() override;

signals:
    void play();
    void stop();
};