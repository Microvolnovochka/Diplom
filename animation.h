#pragma once

#include "PlaneController.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QInputEvent>

namespace Ui {
 class Animation;
}

class Plane : public QGraphicsEllipseItem
{
public:
    Plane();
    // QGraphicsItem interface
    virtual void advance(int phase);
private:
    int vSpeed,hSpeed,angle;
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
