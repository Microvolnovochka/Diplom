#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include "PlaneController.h"
#include "ui_PlaneController.h"

PlaneController::PlaneController(QWidget *parent):QWidget(parent),
     ui(new Ui::PlaneController)
{
    ui->setupUi(this);
    QVBoxLayout *vbox = new QVBoxLayout (this);
    QHBoxLayout *hbox = new QHBoxLayout ();
    QHBoxLayout *hbox_buttons = new QHBoxLayout ();


    angleController = new QSlider (Qt::Horizontal, this);
    angleController->setMaximum(360);
    hbox->addWidget(angleController);

    angleValue = new QLabel ("0", this);
    hbox->addWidget(angleValue);

    leftTurn = new QPushButton ("L",this);
    hbox_buttons->addWidget(leftTurn,1,Qt::AlignLeft);

    rightTurn = new QPushButton ("R",this);
    hbox_buttons->addWidget(rightTurn,1,Qt::AlignCenter);

    accept = new QPushButton ("OK",this);
    accept->setEnabled(false);
    hbox_buttons->addWidget(accept,1,Qt::AlignRight);


    vbox->addLayout(hbox);
    vbox->addLayout(hbox_buttons);


    connect(angleController, &QSlider::valueChanged, angleValue,
    static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
}
