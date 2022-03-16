#include <QApplication>

#include "TetrixWindow.h"

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);

    TetrixWindow window;
    window->show();

    return app.exec();
}
