#pragma once

#include <QtWidgets>
#include "component.h"

class Component;
class Mediator;

class RegistrationScreen : public QWidget, public Component
{
    Q_OBJECT

private:
    QGridLayout *layoutOuter;
    QLineEdit *loginField;
    QLineEdit *passwordField;
    QLineEdit *passwordRepeatField;
    QPushButton *registrationButton;
    QPushButton *signInButton;

public:
    explicit RegistrationScreen(const Mediator *mediator_, QWidget *parent = nullptr);
    ~RegistrationScreen();

    Qstring getLogin();
    Qstring getPassword();
    Qstring getPasswordRepeat();

    void clearData();
};
