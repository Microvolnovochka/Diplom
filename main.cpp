#include <QApplication>
#include "animation.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Animation window;

    window.show();
    return app.exec();
}
