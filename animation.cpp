#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include "animation.h"
#include "ui_Animation.h"
#include "ui_PlaneController.h"

Animation::Animation(QWidget *parent):QWidget(parent),
    ui(new Ui::Animation)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(scene->itemsBoundingRect());
    ui->view->setScene(scene);

    animationTimer = new QTimer(this);
    connect(animationTimer,SIGNAL(timeout()),
            scene,SLOT(advance()));

    animationTimer->start(1000/60);
}

Plane::Plane(int thisX,int thisY) : QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/source/airplane-black.png").scaled(30,40));
    setPos(thisX,thisY);
    this->angle = 0.0;
    this->hSpeed = 0.0;
    this->vSpeed = 0.0;
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
    QVBoxLayout *vbox_hSpeed = new QVBoxLayout();
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

    hSpeedController = new QSlider (Qt::Vertical, this);
    hSpeedController->setMaximum(500);
    vbox_hSpeed->addWidget(hSpeedController);

    hSpeedValue = new QLabel ("0", this);
    vbox_hSpeed->addWidget(hSpeedValue);

    hbox->addLayout(vbox_hSpeed);
    vbox->addLayout(hbox);
    vbox->addLayout(hbox_buttons);


    connect(angleController, &QSlider::valueChanged,
            angleValue,static_cast<void (QLabel::*)(int)>(&QLabel::setNum));

    connect(hSpeedController, &QSlider::valueChanged,
            hSpeedValue,static_cast<void (QLabel::*)(int)>(&QLabel::setNum));

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
    double vMovement,hMovement;

    vMovement = (sin(qDegreesToRadians(this->getAngle())))*this->getHSpeed()/100;
    hMovement = -(cos(qDegreesToRadians(this->getAngle())))*this->getHSpeed()/100;
    if (phase)
    {
        moveBy(vMovement,hMovement);
    }

}

void PlaneController::onChangesAccepted()
{
    this->airplanePL->setAngle(this->angleValue->text().toDouble());
    this->airplanePL->setHSpeed(this->hSpeedValue->text().toDouble());
    this->animationPLTimer->start(1000/60);
    this->~PlaneController();
}

void PlaneController::onAngleChanged()
{
    accept->setEnabled(true);
}
void Plane::setAngle(double angle)
{
    this->angle = angle;
}

void Plane::setHSpeed(double hSpeed)
{
    this->hSpeed = hSpeed;
}

void Plane::setVSpeed(double vSpeed)
{
    this->vSpeed = vSpeed;
}

double Plane::getAngle()
{
    return this->angle;
}

double Plane::getHSpeed()
{
    return this->hSpeed;
}

double Plane::getVSpeed()
{
    return this->vSpeed;
}

void Animation::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        Plane *airplane = new Plane(event->x(),event->y());
        scene->addItem(airplane);
        planeController = new PlaneController(*airplane,*animationTimer,nullptr);
        planeController->show();
    }

}



void Plane::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //PlaneController *planeController = new PlaneController(*this,this->parentObject());
    //planeController->show();
}
