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

Plane::Plane(int thisX,int thisY) : QGraphicsEllipseItem()
{
    setRect(0,0,20,20);
    setPos(thisX,thisY);
    this->angle = 0.0;
    this->hSpeed = 0.0;
    this->vSpeed = 0.0;
}

PlaneController::PlaneController(Plane &airplane,QTimer &animationTimer,QGraphicsScene &scene,QWidget *parent):QWidget(parent)
     ,ui(new Ui::PlaneController)
{
    scenePL = &scene;
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

    angleValue = new QSpinBox (this);
    angleValue->setMaximum(360);
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


    connect(angleController, SIGNAL(valueChanged(int)),
            angleValue,SLOT(setValue(int)));

    connect(angleValue, SIGNAL(valueChanged(int)),
            angleController,SLOT(setValue(int)));

    connect(hSpeedController, &QSlider::valueChanged,
            hSpeedValue,static_cast<void (QLabel::*)(int)>(&QLabel::setNum));

    connect(hSpeedController, SIGNAL(sliderPressed()),
            this,SLOT(onHSpeedChanged()));

    connect(accept,SIGNAL(clicked()),
            this,SLOT(onChangesAccepted()));
}

PlaneController::~PlaneController()
{
    qDebug() <<"DestructorPL";
    this->animationPLTimer->start(1000/60);
    this->close();
}

void Plane::advance(int phase)
{
    double vMovement,hMovement;

    if (phase)
    {
        if (abs(this->getAngle()-this->getSelectedAngle())>=0.99)
        {
            if (((this->getAngle()+180)>=this->getSelectedAngle()&&this->getSelectedAngle()>this->getAngle())||(((this->getAngle()-180)>=getSelectedAngle()&&getSelectedAngle()>(this->getAngle()-360))))
            {
                this->setAngle(this->getAngle()+(3/60));
            }
            else
            {
                this->setAngle(this->getAngle()-(3/60));
            }
        }
        else
        {
            this->setAngle(this->getSelectedAngle());
        }
        vMovement = (sin(qDegreesToRadians(this->getAngle())))*this->getHSpeed()/100;
        hMovement = -(cos(qDegreesToRadians(this->getAngle())))*this->getHSpeed()/100;
        moveBy(vMovement,hMovement);
    }

}

void PlaneController::onChangesAccepted()
{
    this->airplanePL->setSelAngle(this->angleValue->value());
    this->airplanePL->setHSpeed(this->hSpeedValue->text().toDouble());
    scenePL->addItem(airplanePL);
    this->~PlaneController();
}

void PlaneController::onHSpeedChanged()
{
    accept->setEnabled(true);
}

void Plane::setAngle(double angle)
{
    this->angle = angle;
}

void Plane::setSelAngle(double selAngle)
{
    this->selectedAngle = selAngle;
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

double Plane::getSelectedAngle()
{
    return this->selectedAngle;
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
        //scene->addItem(airplane);
        planeController = new PlaneController(*airplane,*animationTimer,*scene,nullptr);
        planeController->show();
    }

}



void Plane::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //PlaneController *planeController = new PlaneController(*this,this->parentObject());
    //planeController->show();
}


void PlaneController::closeEvent(QCloseEvent *event)
{
    qDebug() <<"window_closes";
    if (this->animationPLTimer->isActive())
    {
        return;
    }
    else
    {
       this->~PlaneController();
    }
}
