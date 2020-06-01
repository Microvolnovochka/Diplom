#include "animation.h"
#include "ui_Animation.h"

Animation::Animation(QWidget *parent):QWidget(parent),
    ui(new Ui::Animation)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(0,0,800,600,this);
    scene->addRect(scene->sceneRect());
    ui->view->setScene(scene);

    animationTimer = new QTimer(this);
    connect(animationTimer,SIGNAL(timeout()),
            scene,SLOT(advance()));

    animationTimer->start(1000/60);
}

Plane::Plane() : QGraphicsEllipseItem()
{
    this->angle = 0;
    this->hSpeed = 0;
    this->vSpeed = 0;
}

void Plane::advance(int phase)
{
    if (phase)
    {
        moveBy(0,5);
    }

}

void Animation::mousePressEvent(QMouseEvent *event)
{
    Plane *airplane = new Plane();
    int pp;
    planeController = new PlaneController();
    planeController->show();
}

