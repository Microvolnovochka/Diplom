#pragma once

#include <QDebug>
#include <QtMath>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QInputEvent>
#include <QtWidgets/QWidget>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

namespace Ui {
 class Animation;
 class Plane;
 class PlaneController;
}

class PlaneCircle : public QGraphicsEllipseItem
{
public:
    PlaneCircle(int thisX,int thisY);
    void setVSpeed (double vSpeed);
    void setHSpeed (double hSpeed);
    void setAngle (double angle);
    void setSelAngle (double selAngle);
    double getVSpeed();
    double getHSpeed();
    double getAngle();
    double getSelectedAngle();
    // QGraphicsItem interface
    virtual void advance(int phase);
private:
    double vSpeed,hSpeed,angle,selectedAngle;

    // QGraphicsItem interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
};



class PlaneController : public QWidget
{
    Q_OBJECT

public:
    PlaneController(PlaneCircle &airplane,QWidget *parent = nullptr);
    ~PlaneController();
private slots:
    void onChangesAccepted();
    void onHSpeedChanged();
private:
    Ui::PlaneController *ui;
    QSlider *angleController;
    QSlider *hSpeedController;
    QSpinBox *angleValue;
    QLabel *hSpeedValue;
    QPushButton *leftTurn;
    QPushButton *rightTurn;
    QPushButton *accept;
    PlaneCircle *airplanePL;


    // QWidget interface
protected:
};

class Plane : public QWidget
{
    Q_OBJECT

public:
    Plane(QVBoxLayout &vbox, QGraphicsScene &scene,bool nplanes);
private slots:
    void onPlaneInfo();
private:
    QPushButton *planeInfo;
    PlaneCircle *airplane;
    PlaneController *planecontroller;
};

class Animation : public QWidget
{
    Q_OBJECT

public:
    Animation(QWidget *parent = 0);
private:
    Ui::Animation *ui;
    QGraphicsScene *scene;
    QTimer *animationTimer;
    QPushButton *addNPlanes;
    QPushButton * addPlane;
    QVBoxLayout *vbox_animation;
    Plane *plane;
private slots:
    void onAddPlane();
    void onAddNPlanes();
    // QWidget interface
protected:

    // QWidget interface
};



