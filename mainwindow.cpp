#include <QtWidgets/QHBoxLayout>

#include "mainwindow.h"
#include "ui_mainwindow.h"

mainWindow::mainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    QHBoxLayout *hboxMW = new QHBoxLayout (this);

    graphicScene = new QPushButton ("GraphicScene",this);
    hboxMW->addWidget(graphicScene,1,Qt::AlignLeft);

    graphicSceneMulti = new QPushButton ("GraphicSceneMultiThread",this);
    hboxMW->addWidget(graphicSceneMulti,1,Qt::AlignCenter);

    openGl = new QPushButton ("openGl",this);
    hboxMW->addWidget(openGl,1,Qt::AlignRight);

    connect(graphicScene,SIGNAL(clicked()),
            this,SLOT(onGraphicScene()));

}

void mainWindow::onGraphicScene()
{
    animation = new Animation();
    animation->show();
}

mainWindow::~mainWindow()
{
    delete ui;
}
