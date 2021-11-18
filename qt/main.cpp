#include <QApplication>

#include "forms/widget.h"

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);

    Widget widget;
    widget.show();

    return app.exec();
}
