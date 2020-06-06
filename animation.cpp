#include <QtWidgets/QHBoxLayout>


#include "animation.h"
#include "ui_Animation.h"
#include "ui_PlaneController.h"

Animation::Animation(QWidget *parent):QWidget(parent),
    ui(new Ui::Animation)
{
    ui->setupUi(this);

    QHBoxLayout *hbox_animation = new QHBoxLayout (this);
    vbox_animation = new QVBoxLayout();

    addNPlanes = new QPushButton("Add_N_Plane",this);
    vbox_animation->addWidget(addNPlanes);

    addPlane = new QPushButton("Add_Plane",this);
    vbox_animation->addWidget(addPlane);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(scene->itemsBoundingRect());
    ui->view->setScene(scene);

    hbox_animation->addLayout(vbox_animation);
    hbox_animation->addWidget(ui->view);

    animationTimer = new QTimer(this);

    connect(addNPlanes,SIGNAL(clicked()),
            this,SLOT(onAddNPlanes()));

    connect(addPlane,SIGNAL(clicked()),
            this,SLOT(onAddPlane()));

    connect(animationTimer,SIGNAL(timeout()),
            scene,SLOT(advance()));

    animationTimer->start(1000/60);
}

void Animation::onAddPlane()
{
    plane = new Plane(*(this->vbox_animation),*scene,false);
}

void Animation::onAddNPlanes()
{
    for (int i =0; i<1000; i++)
    {
       plane = new Plane(*(this->vbox_animation),*scene,true);
    }
}
Plane::Plane(QVBoxLayout &vbox, QGraphicsScene &scene,bool nplanes)
{
        airplane = new PlaneCircle (10,10);
        planeInfo = new QPushButton("Plane",this);
        scene.addItem(airplane);
        vbox.addWidget(planeInfo);
        if (!nplanes)
        {
            planecontroller = new PlaneController(*airplane,nullptr);
            planecontroller->show();
        }
        else
        {
            airplane->setAngle(45.0);
            airplane->setHSpeed(1.0);
        }
        connect(planeInfo,SIGNAL(clicked()),
                this,SLOT(onPlaneInfo()));
}

void Plane::onPlaneInfo()
{
    planecontroller = new PlaneController(*airplane,nullptr);
    planecontroller->show();
}

PlaneCircle::PlaneCircle(int thisX,int thisY) : QGraphicsEllipseItem()
{
    setRect(0,0,20,20);
    setPos(thisX,thisY);
    this->angle = 0.0;
    this->hSpeed = 0.0;
    this->vSpeed = 0.0;
}

PlaneController::PlaneController(PlaneCircle &airplane,QWidget *parent):QWidget(parent)
     ,ui(new Ui::PlaneController)
{
    airplanePL = &airplane;
    ui->setupUi(this);
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
    this->close();
}

void PlaneCircle::advance(int phase)
{
    double vMovement,hMovement;

    if (phase)
    {
        if (abs(this->getAngle()-this->getSelectedAngle())>=0.99)
        {
            if (((this->getAngle()+180)>=this->getSelectedAngle()&&this->getSelectedAngle()>this->getAngle())||(((this->getAngle()-180)>=getSelectedAngle()&&getSelectedAngle()>(this->getAngle()-360))))
            {
                this->setAngle(this->getAngle()+(0.05));
            }
            else
            {
                this->setAngle(this->getAngle()-(0.05));
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
    this->~PlaneController();
}

void PlaneController::onHSpeedChanged()
{
    accept->setEnabled(true);
}

void PlaneCircle::setAngle(double angle)
{
    this->angle = angle;
}

void PlaneCircle::setSelAngle(double selAngle)
{
    this->selectedAngle = selAngle;
}

void PlaneCircle::setHSpeed(double hSpeed)
{
    this->hSpeed = hSpeed;
}

void PlaneCircle::setVSpeed(double vSpeed)
{
    this->vSpeed = vSpeed;
}

double PlaneCircle::getAngle()
{
    return this->angle;
}

double PlaneCircle::getSelectedAngle()
{
    return this->selectedAngle;
}

double PlaneCircle::getHSpeed()
{
    return this->hSpeed;
}

double PlaneCircle::getVSpeed()
{
    return this->vSpeed;
}

void PlaneCircle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //PlaneController *planeController = new PlaneController(*this,this->parentObject());
    //planeController->show();
}

