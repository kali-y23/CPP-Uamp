#pragma once

#include "mainwindow.h"


enum class ButtonType {
    Play,
    Loop
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

public slots:
    void click();
};
