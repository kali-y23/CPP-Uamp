#include "qsuperbutton.h"

#include <iostream>

QSuperButton::QSuperButton(ButtonType type, QWidget *parent) {
    index = 0;
    // setMinimumSize(100, 100);
    connect(this, SIGNAL(clicked()), this, SLOT(click()));

    if (type == ButtonType::Loop) {
        //
    }
    else if (type == ButtonType::Play) {
        createPlayList();
        setIcon(list[index]);
        // setFixedSize(200, 200);
    }

}

QSuperButton::~QSuperButton() {
    //
}

void QSuperButton::createPlayList(void) {
    QIcon ic1(":/play.png");
    QIcon ic2(":/pause.png");

    list.push_back(ic2);
    list.push_back(ic1);
}

void QSuperButton::click() {
    // QPushButton::click();
    if (index < list.size() - 1) {
        ++index;
    }
    else
        index = 0;

    setIcon(list[index]);
}
