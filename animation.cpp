#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include "animation.h"
#include "ui_Animation.h"
#include "ui_PlaneController.h"

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

Plane::Plane(int thisX,int thisY) : QGraphicsEllipseItem()
{
    setRect(0,0,20,20);
    setPos(thisX,thisY);
    this->angle = 0;
    this->hSpeed = 0;
    this->vSpeed = 0;
}

PlaneController::PlaneController(Plane &airplane,QTimer &animationTimer,QWidget *parent):QWidget(parent)
     ,ui(new Ui::PlaneController)
{
    airplanePL = &airplane;
    animationPLTimer = &animationTimer;
    ui->setupUi(this);
    animationPLTimer->stop();
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


    connect(angleController, &QSlider::valueChanged,
            angleValue,static_cast<void (QLabel::*)(int)>(&QLabel::setNum));

    connect(angleController, SIGNAL(sliderPressed()),
            this,SLOT(onAngleChanged()));
    connect(accept,SIGNAL(clicked()),
            this,SLOT(onChangesAccepted()));
}

PlaneController::~PlaneController()
{
    this->close();
}

void Plane::advance(int phase)
{
    if (phase)
    {
        moveBy(0,5);
    }

}

void PlaneController::onChangesAccepted()
{
    this->airplanePL->setAngle(this->angleValue->text().toInt());
    this->animationPLTimer->start(1000/60);
    this->~PlaneController();
}

void PlaneController::onAngleChanged()
{
    accept->setEnabled(true);
}
void Plane::setAngle(int angle)
{
    this->angle = angle;
}

void Plane::setHSpeed(int hSpeed)
{
    this->hSpeed = hSpeed;
}

void Plane::setVSpeed(int vSpeed)
{
    this->vSpeed = vSpeed;
}

int Plane::getAngle()
{
    return this->angle;
}

int Plane::getHSpeed()
{
    return this->hSpeed;
}

int Plane::getVSpeed()
{
    return this->vSpeed;
}

void Animation::mousePressEvent(QMouseEvent *event)
{
    Plane *airplane = new Plane(event->x(),event->y());
    scene->addItem(airplane);
    planeController = new PlaneController(*airplane,*animationTimer,nullptr);
    planeController->show();
}

