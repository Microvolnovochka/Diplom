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

namespace Ui {
 class Animation;
 class PlaneController;
}

class Plane : public QGraphicsPixmapItem
{
public:
    Plane(int thisX,int thisY);
    void setVSpeed (double vSpeed);
    void setHSpeed (double hSpeed);
    void setAngle (double angle);
    double getVSpeed();
    double getHSpeed();
    double getAngle();
    // QGraphicsItem interface
    virtual void advance(int phase);
private:
    double vSpeed,hSpeed,angle;

    // QGraphicsItem interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

class PlaneController : public QWidget
{
    Q_OBJECT

public:
    PlaneController(Plane &airplane,QTimer &animationtimer,QGraphicsScene &scene,QWidget *parent = nullptr);
    ~PlaneController();
private slots:
    void onChangesAccepted();
    void onAngleChanged();
private:
    Ui::PlaneController *ui;
    QSlider *angleController;
    QSlider *hSpeedController;
    QSpinBox *angleValue;
    QLabel *hSpeedValue;
    QPushButton *leftTurn;
    QPushButton *rightTurn;
    QPushButton *accept;
    QGraphicsScene *scenePL;
    Plane *airplanePL;
    QTimer *animationPLTimer;


    // QWidget interface
protected:
   virtual void closeEvent(QCloseEvent *event);
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
    PlaneController *planeController;

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event);

    // QWidget interface
};



