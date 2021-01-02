#include <QCoreApplication>
#include <QTimer>
#include "consoleui.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ConsoleUI *ui = new ConsoleUI(&a);
    QObject::connect(ui, SIGNAL(finished()), &a, SLOT(quit()));
    QTimer::singleShot(0, ui, SLOT(run()));

    return a.exec();
}
