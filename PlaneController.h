#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

namespace Ui {
 class PlaneController;
}


class PlaneController : public QWidget
{
    Q_OBJECT

public:
    PlaneController(QWidget *parent = nullptr);

private:
    Ui::PlaneController *ui;
    QSlider *angleController;
    QLabel *angleValue;
    QPushButton *leftTurn;
    QPushButton *rightTurn;
    QPushButton *accept;

};
