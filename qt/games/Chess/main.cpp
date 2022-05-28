#include <QApplication>

#include <QIcon>

#include "MainWindow.h"

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/resource/icon"));

    MainWindow window;
    window.show();

    return app.exec();
}
