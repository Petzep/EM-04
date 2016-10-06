#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TUIcomotive.h"

class TUIcomotive : public QMainWindow
{
    Q_OBJECT

public:
    TUIcomotive(QWidget *parent = Q_NULLPTR);

private:
    Ui::TUIcomotiveClass ui;
};
