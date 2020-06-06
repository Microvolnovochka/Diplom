#pragma once

#include "animation.h"

namespace Ui {
class mainWindow;
}

class mainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();
private slots:
    void onGraphicScene();
   // void onGraphicSceneMulti();
    //void onOpenGl();
private:
    Ui::mainWindow *ui;
    QPushButton *graphicScene;
    QPushButton *graphicSceneMulti;
    QPushButton *openGl;

    Animation *animation;

};


