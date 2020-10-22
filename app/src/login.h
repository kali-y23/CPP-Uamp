#pragma once

#include <QtWidgets>
#include "component.h"

class Component;
class Mediator;

class LoginScreen : public QWidget, public Component
{
    Q_OBJECT

private:
    QVBoxLayout *layoutOuter;
    QLineEdit *loginField;
    QLineEdit *passwordField;
    QPushButton *signInButton;
    QPushButton *registrationButton;

public:
    explicit LoginScreen(const Mediator *mediator_, QWidget *parent = nullptr);
    ~LoginScreen();

};
