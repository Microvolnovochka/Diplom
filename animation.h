#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QInputEvent>
#include <QtWidgets/QWidget>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

namespace Ui {
 class Animation;
 class PlaneController;
}

class Plane : public QGraphicsEllipseItem
{
public:
    Plane(int thisX,int thisY);
    void setVSpeed (int vSpeed);
    void setHSpeed (int hSpeed);
    void setAngle (int angle);
    int getVSpeed();
    int getHSpeed();
    int getAngle();
    // QGraphicsItem interface
    virtual void advance(int phase);
private:
    int vSpeed,hSpeed,angle;
};

class PlaneController : public QWidget
{
    Q_OBJECT

public:
    PlaneController(Plane &airplane,QTimer &animationtimer,QWidget *parent = nullptr);
    ~PlaneController();
private slots:
    void onChangesAccepted();
    void onAngleChanged();
private:
    Ui::PlaneController *ui;
    QSlider *angleController;
    QLabel *angleValue;
    QPushButton *leftTurn;
    QPushButton *rightTurn;
    QPushButton *accept;
    Plane *airplanePL;
    QTimer *animationPLTimer;

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
};



